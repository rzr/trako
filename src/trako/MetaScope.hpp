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

template <typename T>
CounterOf< trako::MetaScope<T> > trako::MetaScope<T>::mCounter;


template <typename T>
trako::MetaScope<T>::MetaScope
( char const * const name,
  char const * const prefix,
  bool verbose
  )
  : mName(name), mPrefix(prefix),
    mVerbose(verbose)
{
  if (mVerbose) {
    printf("%s{ %s @%d\n", mPrefix, mName, mCounter.getValue());
  }  
  mCounter.add();
}

template<typename T>
trako::MetaScope<T>::~MetaScope()
{
  mCounter.sub();
  if ( mVerbose ) {
    printf("%s} %s @%d\n", mPrefix, mName, mCounter.getValue());
  }
}

template<typename T>
void trako::MetaScope<T>::print(char const * const prefix)
{
  mCounter.print(prefix);
}

#endif // MetaScope_hpp_
