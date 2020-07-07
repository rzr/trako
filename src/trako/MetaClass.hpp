/* #ident "$Id:$"
 * @author: Philippe Coval <rzr@users.sf.net> -- Rev: $Author: rzr $
 * Copyright: LGPL-3 (See README file that comes with this distribution)
 *****************************************************************************/
#ifndef MetaClass_hpp_
#define MetaClass_hpp_

#include <list>

#include "MetaClass.h"
#include "Context.h"

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
      Context<T>::mList.push_back( mShared );
    } else { //this part will be executed by new mShared on 1st
      mCounter.add();
    }
  }
 


template<typename T>
int trako::MetaClass<T>::print(char const * const prefix, bool force) const
{
  int res = mCounter.print(prefix, force);
  return res;
}


template<typename T>
int trako::MetaClass<T>::printStats(char const * const prefix, bool force)
{
  int res = mCounter.print(prefix, force);
  return res;
}

#endif
