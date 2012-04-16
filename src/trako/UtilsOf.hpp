/* #ident "$Id:$"
 * @author: Philippe Coval <rzr@gna.org> -- Rev: $Author: rzr $
 * Copyright: LGPL-3 (See README file that comes with this distribution)
 *                                                           -*- Mode: c++ -*-
 *****************************************************************************/
#ifndef UtilsOf_hpp_
#define UtilsOf_hpp_


#include "UtilsOf.h"


///
template <typename T>
int CounterOf<T>::mCurrent = 0;

template <typename T>
int CounterOf<T>::mMin = 0;

template <typename T>
int CounterOf<T>::mMax = 0;

template <typename T>
int CounterOf<T>::mPrev = 0;

template <typename T>
int CounterOf<T>::mEver = 0;

#endif //_h_

