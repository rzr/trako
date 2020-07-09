/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*-
 * #ident "$Id:$"
 * @author: Philippe Coval <rzr@users.sf.net> -- Rev: $Author: rzr $
 * Copyright: LGPL-3 (See README file that comes with this distribution)
 *****************************************************************************/

#ifndef Duration_hpp_
#define Duration_hpp_

#include "config.h"

#ifndef CONFIG_SUPPORT_API_C_STDIO_H_NO
# include <stdio.h>
#endif

#include <cassert>
#include <ctime>
#include <functional>
#include <iomanip>
#include <set>

#ifndef CONFIG_SUPPORT_API_SYS_TIME_NO
# include <sys/time.h>
#endif

#include <iostream>
#include <algorithm>
#include <map>

#include "UtilsOf.h"
#include "Duration.h"

#include "macros.h"

template <typename T>
unsigned long trako::Duration<T>::mElapsed{0};


#ifndef CONFIG_SUPPORT_API_SYS_TIME_NO
template <typename T>
timeval trako::Duration<T>::mEpocTime;
template <typename T>
timeval trako::Duration<T>::mNowTime;
#endif

template <typename T>
std::map<char const * const, trako::Duration<> > trako::Duration<T>::mCollection;

template <typename T>
trako::Duration<T>::Duration(char const * const prefix,
                             char const * const name,  bool verbose)
  : mPrefix{prefix}, mName{name}, mCount{}, mDepth{}, mProfile(true), mVerbose{verbose},
    mValue{}, mCumulated{}, mMaximum{}, mMinimum{}, mRatio{}
#ifndef CONFIG_SUPPORT_API_SYS_TIME_NO
  , mStartTime{}, mStopTime{}
#endif
{
  static int init=0; // could be relocated in get to have 100% for 1st caller
  if (!init++) {
    mEpocTime = getTime();
  }
  mStartTime.tv_sec = 0; mStartTime.tv_usec = 0;
  mStopTime.tv_sec = 0; mStopTime.tv_usec = 0;
}


template <typename T>
trako::Duration<>& trako::Duration<T>::get(char const * const id,
                                           char const * const name)
{
  Duration<T>& result = mCollection[id];
  result.mPrefix = id;
  result.mName = (name) ? name : id;
  return result;
}

template <typename T>
void trako::Duration<T>::print(bool verbose,
                               char const * const prefix,
                               char const * const suffix) const
{
  std::cout << ( (!prefix) ? mPrefix : prefix );
  int elapsed = mElapsed;
  if (!elapsed) { mElapsed = 1; }
  int count = mCount;
  if (!count) { count = 1; }
  if (!verbose) {
    return;
  }

  //assert(mCumulated<=mElapsed); //TODO
  if (!mCumulated) {
    std::cout << "???.??%";
  } else {
    std::cout << std::fixed << std::setprecision(2)
              << std::setfill('0') << std::setw(6)
              << mCumulated * 100.f / elapsed << "%";
  }
  std::cout << " <" << mName << "> [~"
            << mCumulated / count / 1000000L << "s="
            << mCumulated / count << "us"
            << "*" << count << "~=" << elapsed << "us" << "]"
            << suffix << std::endl;
}


#ifndef CONFIG_SUPPORT_API_SYS_TIME_NO

template <typename T>
unsigned long trako::Duration<T>::timeToDuration(timeval time)
{
  return 1000000L * time.tv_sec + time.tv_usec;
}

template <typename T>
timeval trako::Duration<T>::diffTime(timeval before, timeval after)
{
  timeval result;
  result.tv_sec = after.tv_sec - before.tv_sec;
  result.tv_usec = after.tv_usec - before.tv_usec;
  return result;
}

template <typename T>
unsigned long trako::Duration<T>::getDuration()
{
  unsigned long result=timeToDuration(diffTime(mEpocTime, getTime()));
  return result;
}

template <typename T>
timeval trako::Duration<T>::getTime()
{
  int failed = gettimeofday(&mNowTime,0);
  assert(!failed);
  if (!failed) {
    mNowTime.tv_sec -= mEpocTime.tv_sec;
    mNowTime.tv_usec -= mEpocTime.tv_usec;
  }
  mElapsed = (mNowTime.tv_sec * 1000000L +  mNowTime.tv_usec);
  return mNowTime;
}
#endif

template <typename T>
void trako::Duration<T>::start(bool verbose)
{
  if (verbose) {
    //print(mName);
  }
#ifndef CONFIG_SUPPORT_API_SYS_TIME_NO
  mValue=0;
  getTime();
  if (mDepth == 0) { // prevent reentrents functions
    //assert((mStartTime.tv_usec == 0) && (mStartTime.tv_usec ==0));
    mStartTime = mNowTime; //TODO check if copied
    mStopTime.tv_sec = mStopTime.tv_usec = 0;
  }
#else
# warning "TODO"
#endif
  mRatio = mCumulated / (float) mElapsed;
  if (verbose) {
    std::cout << " ["
              << std::fixed << std::setprecision(2)
              << std::setfill('0') << std::setw(6)
              << mRatio * 100.f<< "%" << "*"<<mDepth
              << "+?"<<((mCount)?mCumulated/mCount:0)<<"*"<<mCount
              << "/"<<mElapsed << "us"
              <<"]"
      ;
  }
  mDepth++;
  mCount++;
}

template <typename T>
void trako::Duration<T>::stop(bool verbose)
{
  if (verbose) {
    if (mName) {
      //print(mName);
    } else {
      //print(mPrefix);
    }
  }

#ifndef CONFIG_SUPPORT_API_SYS_TIME_NO
  mStopTime = getTime();

  mValue = timeToDuration(diffTime(mStartTime, mNowTime));
  if (mDepth==1) { // only add for first one before re-entrace
    mCumulated += mValue;
  }

  mRatio = mCumulated / (float) mElapsed;
  if (mValue > mMaximum) { mMaximum = mValue; }
  if (mValue < mMinimum) { mMinimum = mValue; }

  if (verbose) {
    std::cout<<" ["
             << std::fixed << std::setprecision(2)
             << std::setfill('0') << std::setw(6)
             << mRatio * 100.f << "% *" << mDepth
             << "+=" << mValue << "us=" << mCumulated << "us~/"
             << mCount  << "]"
      ;
  }
  mDepth--;
#endif

  if (verbose ) {
    printf("\n");
    //mTimeCounter.print(mName);
  }
}

template <typename T>
void trako::Duration<T>::printStats(bool verbose,
                                    char const * const prefix,
                                    char const * const suffix)
{
  if (!verbose) return;
#ifndef CONFIG_SUPPORT_API_SYS_TIME_NO
  getTime(); // to update probe since last time
#endif
  unsigned long probe = mElapsed;
  std::cout << std::endl << prefix
            << std::fixed << std::setprecision(2) << std::setfill('0') << std::setw(6)
            << 100.f * probe / mElapsed
            << "% <FUNCT/STATS> [+~" << probe / 1000000L
            << "s~=+" <<probe << "us=" << mElapsed
            <<"/" << mCollection.size()
            <<"*?]"
            << suffix
            <<std::endl;

  for_each(mCollection.begin(), mCollection.end(),
           [prefix](std::pair<char const * const, Duration<>> &item) {
             // item.second.print(); // TODO
             item.second.mRatio = (float) item.second.mCumulated / mElapsed;
           }
           );

  std::cout<<prefix
           <<"stats: sort: "<<mCollection.size() << std::endl << std::endl;

  typedef std::function<bool(std::pair<char const * const, Duration<> >,
                             std::pair<char const * const, Duration<> >)> Comparator;
  Comparator compFunctor
    = [](std::pair<char const * const, Duration<> > before,
         std::pair<char const * const, Duration<> > after) {
        return (before.second.mRatio < after.second.mRatio);
      };
  std::set<std::pair<char const * const, Duration<> >, Comparator> sortedCollectionSet
    (mCollection.begin(), mCollection.end(), compFunctor);
  for (std::pair<char const * const, Duration<> > item : sortedCollectionSet) {
    item.second.print(verbose, "trako: FUNCT/STATS: ");
  }

  std::cout
    << std::endl<<prefix
    << std::fixed << std::setprecision(2) << std::setfill('0') << std::setw(6)
    << 100.f
    << "% <FUNCT/STATS> [+~" << mElapsed / 1000000L
    << "s~=+" <<mElapsed << "us"
    << "/" << mCollection.size()
    << "]"
    <<std::endl;


  std::cout<<std::endl;
}

#endif // _h_
