/* #ident "$Id:$"
 * @author: Philippe Coval <rzr@users.sf.net> -- Rev: $Author: rzr $
 * Copyright: LGPL-3 (See README file that comes with this distribution)
 *****************************************************************************/
#ifndef MetaClass_hpp_
#define MetaClass_hpp_

#include "MetaClass.h"

template<typename T>
char const * trako::MetaClass<T>::mName = 0;

template<typename T>
trako::MetaClass<T>* trako::MetaClass<T>::mShared = 0;

template<typename T>
CounterOf<T> trako::MetaClass<T>::mCounter;


template<typename T>
trako::MetaClass<T>::MetaClass()
  {
    if ( ! mShared  ) { //tricky part here
      mShared = this; //prevent loop
      mShared = new MetaClass;
      mName = UtilsOf<T>::nametype();
      Context::mList.push_back( mShared );
    } else { //this part will be executed by new mShared on 1st
      mCounter.add();
    }
  }
 


template<typename T>
int trako::MetaClass<T>::print(bool force, char const * const prefix) const
{
  int res = CounterOf<T>::print( force, prefix);
  return res;
}

#endif
