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
  : mClassCollection{}
{
  std::cout
    << "trako: init: {" << std::endl
    << "trako: init: " << TRAKO_PACKAGE << "-" << TRAKO_VERSION << std::endl
    << "trako: init: " << TRAKO_URL << std::endl;
  print(true, "trako: init: ", "init: ");
  std::cout<<"trako: init: }"<<std::endl;
}


template<typename T>
trako::Context<T>::~Context()
{
  std::cout<<"trako: term: {"<<std::endl;
  print(true, "trako: term: ", "term: ");
  std::cout
    << "trako: term: " << TRAKO_PACKAGE << "-" << TRAKO_VERSION << std::endl
    << "trako: term: " << TRAKO_URL << std::endl
    << "trako: term: }"<<std::endl;
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
void trako::Context<T>::printClass(bool verbose,
                                   char const * const prefix,
                                   char const * const suffix)
{
  std::list<trako::MetaClassInterface const *>::const_iterator it;

  for( it = mClassCollection.begin(); it != mClassCollection.end() ; ++it) {
    trako::MetaClassInterface const * const p = *it;
    if (p) p->print(verbose, prefix, suffix);
  }
}


template<typename T>
void trako::Context<T>::printFunct(bool verbose,
                                   char const * const prefix,
                                   char const * const suffix)
{
  trako::Duration<>::printStats(verbose, prefix, suffix);
}

#endif
