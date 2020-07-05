/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*-
 * #ident "$Id:$"
 * @author: Philippe Coval <rzr@users.sf.net> -- Rev: $Author: rzr $
 * Copyright: LGPL-3 (See README file that comes with this distribution)
 *****************************************************************************/
#ifndef UtilsOf_h_
#define UtilsOf_h_

#include <typeinfo>

#include <iostream>

#ifndef CONFIG_SUPPORT_API_CXXABI_NO
# include <cxxabi.h>
#endif

#include "macros.h"

/// Generic helper
template <typename T>
class UtilsOf
{
 public:

  /// @return typename as string
  static char const * const nametype()
  {
    char const * res = 0;
    res = typeid(T).name();

#ifndef CONFIG_SUPPORT_API_CXXABI_NO
    int status = 0;
    res = abi::__cxa_demangle( res , 0 , 0 , &status );
#endif // remove extra mangeling decoration

    return res;
  }

};


/// Generic named counter
template <typename T = void, typename N = int>
class CounterOf
{
 public:
  /// @return current value
  N getValue(bool update=true)
  {
    if ( update ) { mPrev = mCurrent; }
    return mCurrent;
  }

  /// @return difference since previous getValue()
  N getDiff() const { return ( mCurrent - mPrev ); } 

  /// @return maximum value since begining
  N getMax() const { return mMax; } 

  /// @return minmum value since begining
  N getMin() const { return mMin; }

  /// @return count the total of added items
  N getEver() const { return mEver; }

  /// increase the counter by num items
  /// @return total items
  N add(N const num=1)
  {
    mEver+=num;
    mCurrent+=num;
    if ( mCurrent > mMax ) mMax = mCurrent;
    return mCurrent;
  }

  /// decrease the counter by num items
  /// @return total items
  N sub(N const items=1)
  {
    mCurrent-=items;
    if ( mCurrent < mMin ) mMin = mCurrent;
    return mCurrent;
  }

  /// reset the counter to total of num items
  N reset(N const num=0)
  {
    N res = mEver = mCurrent = mMax = mMin = num;
    return res;
  }

  N isChanged() const
  {
    return ( 0 != getDiff() );
  }

  /// @return absolute difference since previous querry if increaded else 0
  N isAdd()
  {
    N res = ( mCurrent - mPrev );
    res = ( res <= 0 ) ? 0 :  res ;
    return res;
  }

  /// @return absolute difference since previous query if decreased else 0
  N isSub()
  {
    N res = ( mCurrent - mPrev) ;
    res = ( res >= 0 ) ? 0 :  - res ;
    return res;
  }

  /// @param force : set to false if only printing if there are changes
   N print(char const * const prefix=TRAKO_TAG("trace: "), bool force=true) //const
  {
    N vcur = 0,vmax = 0, vevr =0, vdif=0;
    static int item = sizeof(T);
    
    if ( force || isChanged() != 0) {
      vdif = getDiff();
      vcur = getValue();
      vmax = getMax();
      vevr = getEver();
      
      std::cout
	<< prefix
	<< "<"<<UtilsOf<T>::nametype()<<">"
	<< (( vdif >= 0 ) ? " +" : " " ) <<vdif
	<< "=" << vcur
	<< " = " << vcur * item << "B"
	<< " (<" << vmax << "<" << vevr <<" )"
	<< std::endl;
    }
    return vdif;
  }

 protected:

  /// current value
  N mCurrent;

  /// maximum value at at given time
  N mMax;

  /// minunum value at at given time
  N mMin;

  /// value at previous querry
  N mPrev;

  /// count since begining
  N mEver;
};

#include "UtilsOf.hpp"

#endif //_h_

