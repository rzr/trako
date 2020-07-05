/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*-
 * #ident "$Id:$"
 * @author: Philippe Coval <rzr@users.sf.net> -- Rev: $Author: rzr $
 * Copyright: LGPL-2 (See README file that comes with this distribution)
 *****************************************************************************/
#ifndef MetaMutex_hpp_
#define MetaMutex_hpp_

#include "config.h"
#include "MetaMutex.h"


#ifndef CONFIG_SUPPORT_API_PTHREAD_NO
template<typename T>
pthread_mutex_t trako::MetaMutex<T>::mMutex = PTHREAD_MUTEX_INITIALIZER;

template<typename T>
trako::MetaMutex<T>::MetaMutex()
{
  pthread_mutex_lock(&mMutex);
}


template<typename T>
trako::MetaMutex<T>::~MetaMutex()
{
  pthread_mutex_unlock(&mMutex);
}
#endif

#endif
