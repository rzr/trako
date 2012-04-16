/* #ident "$Id:$"
 * @author: Philippe Coval <rzr@gna.org> -- Rev: $Author: rzr $
 * Copyright: LGPL-3 (See README file that comes with this distribution)
 *                                                           -*- Mode: c++ -*-
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
template <typename T>
class CounterOf
{
 public:
  /// @return current value
  static int getValue(bool update=true)
  {
    if ( update ) { mPrev = mCurrent; }
    return mCurrent;
  }

  /// @return difference since previous getValue()
  static int getDiff() { return ( mCurrent - mPrev ); }

  /// @return maximum value since begining
  static int getMax() { return mMax; }

  /// @return minmum value since begining
  static int getMin() { return mMin; }

  /// @return count the total of added items
  static int getEver() { return mEver; }

  /// increase the counter by num items
  /// @return total items
  static int add(int const num=1)
  {
    mEver+=num;
    mCurrent+=num;
    if ( mCurrent > mMax ) mMax = mCurrent;
    return mCurrent;
  }

  /// decrease the counter by num items
  /// @return total items
  static int sub(int const items=1)
  {
    mCurrent-=items;
    if ( mCurrent < mMin ) mMin = mCurrent;
    return mCurrent;
  }

  /// reset the counter to total of num items
  static int reset(int const num=0)
  {
    int res = mEver = mCurrent = mMax = mMin = num;
    return res;
  }

  static int isChanged()
  {
    return ( 0 != getDiff() );
  }

  /// @return absolute difference since previous querry if increaded else 0
  static int isAdd()
  {
    int res = ( mCurrent - mPrev );
    res = ( res <= 0 ) ? 0 :  res ;
    return res;
  }

  /// @return absolute difference since previous query if decreased else 0
  static int isSub()
  {
    int res = ( mCurrent - mPrev) ;
    res = ( res >= 0 ) ? 0 :  - res ;
    return res;
  }

  /// @param force : set to false if only printing if there are changes
  static int print(bool force=true, char const * const prefix=TAG("trace: "))
  {
    int vcur = 0, vmax = 0, vevr =0, vdif=0;
    static int item = sizeof(T);
    
    if ( force || isChanged() != 0) {
      vdif = getDiff();
      vcur = getValue();
      vmax = getMax();
      vevr = getEver();
      
      std::cout
	<< prefix
	<< "<"<<UtilsOf<T>::nametype()<<">"
	<< (( vdif > 0 ) ? " +" : " " ) <<vdif
	<< "=" << vcur
	<< " = " << vcur * item << "B"
	<< " (<" << vmax << "<" << vevr <<" )"
	<< std::endl;
    }
    return vdif;
  }

 protected:

  /// current value
  static int mCurrent;

  /// maximum value at at given time
  static int mMax;

  /// minunum value at at given time
  static int mMin;

  /// value at previous querry
  static int mPrev;

  /// count since begining
  static int mEver;
};

#include "UtilsOf.hpp"

#endif //_h_

