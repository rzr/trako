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

#include "UtilsOf.h"
#include "Duration.h"

#include "macros.h"

using namespace std;

template <typename T>
unsigned long Duration<T>::mElapsed{1};


#ifndef CONFIG_SUPPORT_API_SYS_TIME_NO
template <typename T>
timeval Duration<T>::mEpocTime;
template <typename T>
timeval Duration<T>::mNowTime;
#endif

template <typename T>
std::map<char const * const, Duration<T>> Duration<T>::mCollection;

template <typename T>
Duration<T>::Duration(bool verbose)
  : mName{}, mCount{}, mVerbose{verbose},
    mValue{}, mCumulated{} , mRatio{},
    mMaximum{}, mMinimum{}
#ifndef CONFIG_SUPPORT_API_SYS_TIME_NO
  , mStartTime{}, mStopTime{}
#endif
{
  static int init=0;
  if (!init++) { mEpocTime = getTime(); }
}


template <typename T>
Duration<T>& Duration<T>::get(char const * const name)
{
  Duration<T>& result = mCollection[name];
  result.mName=name;
  return result;
}

template <typename T>
void Duration<T>::print(char const * const prefix) const
{
  cout<<prefix;
  if (!mCumulated) {
    cout<<"???.??%";
  } else {
    cout << std::fixed << std::setprecision(2)
         << std::setfill('0') << std::setw(6)
         << mCumulated * 100.f / mElapsed << "%";
  }
  cout<<" <" << mName << "> [~"
      << mCumulated / mCount / 1000000L << "s="
      << mCumulated / mCount << "us"
      << "*" << mCount << "/" << mElapsed << "us" << "]" <<endl;
}


template <typename T>
timeval Duration<T>::getTime()
{
#ifndef CONFIG_SUPPORT_API_SYS_TIME_NO
  int failed = gettimeofday(&mNowTime,0);
  assert(!failed);
  if (!failed) {
    mNowTime.tv_sec -= mEpocTime.tv_sec;
    mNowTime.tv_usec -= mEpocTime.tv_usec;
  }
  mElapsed = (mNowTime.tv_sec * 1000000L +  mNowTime.tv_usec);
  return mNowTime;
#endif
}


template <typename T>
void Duration<T>::start(bool verbose)
{
  mValue=0;
  mRatio = mCumulated / (float) mElapsed;
#ifndef CONFIG_SUPPORT_API_SYS_TIME_NO
  mStartTime = getTime();
  mStopTime.tv_sec = mStopTime.tv_usec = 0;
  if (verbose) {
    cout << " ["
       << std::fixed << std::setprecision(2)
         << std::setfill('0') << std::setw(6)
         << mRatio * 100.f<< "%"
         << "+?"<<((mCount)?mCumulated/mCount:0)<<"*"<<mCount
         << "/"<<mElapsed << "us"
         <<"]"
      ;
  }
  mCount++;
      //printf(" [~%lds ~= %ldus]", mStartTime.tv_sec, mStartTime.tv_usec);
#endif
}

template <typename T>
void Duration<T>::stop(bool verbose)
{
  assert(!mValue);
#ifndef CONFIG_SUPPORT_API_SYS_TIME_NO
  assert(mStartTime.tv_sec | mStopTime.tv_usec == 0);
  mStopTime = getTime();
  mValue = (1000000L * (mStopTime.tv_sec - mStartTime.tv_sec)
               + (mStopTime.tv_usec - mStartTime.tv_usec) );
  mStartTime.tv_sec = mStartTime.tv_usec = 0;
  mCumulated += mValue;
  mRatio = mCumulated / (float) mElapsed;
  if (mValue > mMaximum) { mMaximum = mValue; }
  if (mValue < mMinimum) { mMinimum = mValue; }

  if (verbose) {
    cout<<" ["
      << std::fixed << std::setprecision(2)
      << std::setfill('0') << std::setw(6) 
        << mRatio * 100.f  << "%+="
        << mValue << "us=" << mCumulated << "us]"
      ;
  }
#endif

  if (verbose ) {
    printf("\n");
    //mTimeCounter.print(mName);
  }
}

template <typename T>
void Duration<T>::printStats(char const * const prefix)
{
  unsigned int total = 0;
  static unsigned long prevDuration = 0;

  for_each(mCollection.begin(), mCollection.end(),
           [prefix, &total](const std::pair<char const * const, Duration> &item) {
             total += item.second.mCumulated;
           });
#ifndef CONFIG_SUPPORT_API_SYS_TIME_NO
  getTime();
#endif
  unsigned long probe = (mElapsed - prevDuration);
  cout<<prefix
      << std::fixed << std::setprecision(2) << std::setfill('0') << std::setw(6)
      << 100.f * probe / mElapsed
      << "% <#stats> [+~" << probe / 1000000L
      << "s~=+" <<probe << "ms=" << mElapsed << "]"<<endl;
  prevDuration = mElapsed;
  for_each(mCollection.begin(), mCollection.end(),
           [prefix](std::pair<char const * const, Duration> &item) {
             item.second.print(prefix);
           });
}

#endif // _h_
