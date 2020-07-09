// -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*-
/* #ident "$Id:$"
 * @author: Philippe Coval <rzr@users.sf.net> -- Rev: $Author: rzr $
 * Copyright: LGPL-3 (See README file that comes with this distribution)
 *****************************************************************************/
#ifndef MetaClass_hpp_
#define MetaClass_hpp_

#include <list>

#include "MetaClass.h"
#include "Duration.h"
#include "Context.h"

template<typename T>
trako::MetaClass<T>* trako::MetaClass<T>::mShared = 0;

template<typename T>
CounterOf<T> trako::MetaClass<T>::mCounter;

template <typename T>
CounterOf< trako::MetaClass<T> > trako::MetaClass<T>::mDepthCounter;

template<typename T>
trako::MetaClass<T>::MetaClass(char const * const prefix,
                               char const * const name,
                               bool verbose, bool profile
  )
  : mPrefix(prefix), mName(name), mVerbose(verbose), mProfile(profile)
{
  Context<>::getInstance(); // Init
  if (!name) {
    mName=UtilsOf<T>::nametype();
  }
  mFunct = (mPrefix);
  if (!mFunct) {
    mVerbose = false;
    mPrefix = mName;
    mProfile = false;
    if (!mShared ) { //tricky part here
      mShared = this; //prevent loop
      mShared = new MetaClass<T>;
      Context<>::getInstance().mClassCollection.push_back( mShared );
    } else { //this part will be executed by new mShared on 1st
      mCounter.add();
    }
  } else {
    if (mVerbose) {
      printf("%s{ %s @%d", mPrefix, mName, mDepthCounter.getValue());
    }
    mDepthCounter.add();
    if (mProfile) {
      mDuration = &Duration<>::get(mPrefix, mName);
      mDuration->start(mVerbose);
      }
    if (mVerbose) {
      std::cout<<std::endl;
    }
  }
}


template<typename T>
trako::MetaClass<T>::~MetaClass()
{
  if (!mFunct && (mShared != this)) {
    mCounter.sub();
  }
  if (mFunct) {
    mDepthCounter.sub();
    if (mVerbose) {
      printf("%s} %s @%d", mPrefix, mName, mDepthCounter.getValue());
    }
    if (mProfile) {
      mDuration->stop(mVerbose);
    }
    if (mVerbose) {
      std::cout<<std::endl;
    }
  }
}


template<typename T>
int trako::MetaClass<T>::print( bool verbose,
                                char const * const prefix,
                                char const * const suffix) const
{
  int res = mCounter.print(verbose, prefix, suffix);
  return res;
}


template<typename T>
int trako::MetaClass<T>::printStats(bool verbose,
                                    char const * const prefix,
                                    char const * const suffix)
{
  trako::Context<>::getInstance();
  int res = mCounter.print(verbose, prefix, suffix);
  return res;
}

#endif
