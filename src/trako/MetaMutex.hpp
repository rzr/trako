/* #ident "$Id:$"
 * @author: Philippe Coval <rzr@gna.org> -- Rev: $Author: rzr $
 * Copyright: LGPL-2 (See README file that comes with this distribution)
 *                                                           -*- Mode: c++ -*-
 *****************************************************************************/
#include "config.h"
#include "MetaMutex.h"


#ifndef CONFIG_SUPPORT_API_PTHREAD_NO
template<typename T>
pthread_mutex_t MetaMutex<T>::mMutex = PTHREAD_MUTEX_INITIALIZER;

template<typename T>
MetaMutex<T>::MetaMutex()
{
  pthread_mutex_lock(&mMutex);
}


template<typename T>
MetaMutex<T>::~MetaMutex()
{
  pthread_mutex_unlock(&mMutex);
}

#endif
