// -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*-
/* #ident "$Id:$"
 * @author: Philippe Coval <rzr@users.sf.net> -- Rev: $Author: rzr $
 * Copyright: LGPL-3 (See README file that comes with this distribution)
 *****************************************************************************/
#ifndef MetaScope_hpp_
#define MetaScope_hpp_

#ifndef CONFIG_SUPPORT_API_C_STDIO_H_NO
# include <cstdio>
#endif

#include <cassert>
#include "MetaScope.h"
#include "Duration.h"
#include "macros.h"

template <typename T>
CounterOf< trako::MetaScope<T> > trako::MetaScope<T>::mCounter;


template <typename T>
trako::MetaScope<T>::MetaScope
( char const * const name,
  char const * const prefix,
  bool verbose, bool profile
  )
  : mName(name), mPrefix(prefix),
    mVerbose(verbose),
    mProfile(profile)
{
  if (mVerbose) {
    printf("%s{ %s @%d", mPrefix, mName, mCounter.getValue());
  }  
  mCounter.add();
  if (mProfile) {
    Duration<void>::get(mName).start(mVerbose);
  }
  if (mVerbose) {
    printf("\n");
  }  
}

template<typename T>
trako::MetaScope<T>::~MetaScope()
{
  mCounter.sub();
  if ( mVerbose ) {
    printf("%s} %s @%d", mPrefix, mName, mCounter.getValue());
  }
    
  if (mProfile) {
    Duration<void>::get(mName).stop(mVerbose);
  }
  if (mVerbose) {
    printf("\n");
  }

}

template<typename T>
void trako::MetaScope<T>::print(char const * const prefix)
{
  mCounter.print(prefix);
}

#endif // MetaScope_hpp_
