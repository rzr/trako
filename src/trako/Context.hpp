/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*-
 * #ident "$Id:$"
 * @author: Philippe Coval <rzr@users.sf.net> -- Rev: $Author: rzr $
 * Copyright: LGPL-3 (See README file that comes with this distribution)
 *****************************************************************************/
#ifndef Context_hpp_
#define Context_hpp_

#include <cstdio>
#include <iostream>

#include "Context.h"
#include "MetaClass.h"
#include "Duration.h"
#include "macros.h"

using namespace std;
using namespace trako;

template<typename T>
std::list<MetaClassInterface const *> Context<T>::mList;


template<typename T>
Context<T> Context<T>::mSelf;


template<typename T>
Context<T>::Context()
{
  print(TRAKO_TAG("start: "), true);
}


template<typename T>
Context<T>::~Context()
{
  print(TRAKO_TAG("stop: "), true);
}


template<typename T>
void Context<T>::print(char const * const context, bool force)
{
  list<MetaClassInterface const *>::const_iterator it;
  
  for( it = mList.begin();
       it != mList.end() ;
       ++it) {
    MetaClassInterface const * const p = *it;
    if ( p ) p->print(context, force);
  }
}

template<typename T>
void Context<T>::printDurationStats(char const * const prefix)
{
  Duration<>::printStats(prefix);
}


#endif

