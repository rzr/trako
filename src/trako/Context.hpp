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
#include "Duration.h"
#include "MetaClass.h"

#include "macros.h"

template<typename T>
trako::Context<>& trako::Context<T>::getInstance()
{
  static Context<T> mSelf;
  return mSelf;
}

template<typename T>
trako::Context<T>::Context()
{
  std::cout<<TRAKO_TAG("init: {}")<<std::endl;
}


template<typename T>
trako::Context<T>::~Context()
{
  std::cout<<TRAKO_TAG("term: {")<<std::endl;
  print(TRAKO_TAG("term: "), true);
  printDurationStats(TRAKO_TAG("term: "), true);
  std::cout<<TRAKO_TAG("term: }")<<std::endl;
}

template<typename T>
std::list<trako::MetaClassInterface const *>& trako::Context<T>::getClassCollection()
{
  std::list<trako::MetaClassInterface const *>* pInstance = NULL;
  if (!pInstance) pInstance = new std::list<trako::MetaClassInterface const *>;
  return *pInstance;
}

template<typename T>
std::map<char const * const, trako::Duration<> >& trako::Context<T>::getDurationCollection()
{
  return Duration<>::mCollection;
}


template<typename T>
void trako::Context<T>::print(char const * const context, bool force)
{
  std::list<trako::MetaClassInterface const *>::const_iterator it;

  for( it = mClassCollection.begin(); it != mClassCollection.end() ; ++it) {
    trako::MetaClassInterface const * const p = *it;
    if (p) p->print(context, force);
  }
}


template<typename T>
void trako::Context<T>::printDurationStats(char const * const prefix, bool verbose)
{
  trako::Duration<>::printStats(prefix, verbose);
}

#endif
