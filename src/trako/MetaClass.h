/* #ident "$Id:$"
 * @author: Philippe Coval <rzr@gna.org> -- Rev: $Author: rzr $
 * Copyright: LGPL-3 (See README file that comes with this distribution)
 *                                                           -*- Mode: c++ -*-
 *****************************************************************************/
#ifndef MetaClass_h_
#define MetaClass_h_

#include <list> //TODO
#include <cstdlib>

#include "UtilsOf.h"
#include "Context.h"


/// trako's common function to be used elsewhere (not tied to a type)
class MetaClassInterface
{
 public:
  ///@return typename
  virtual char const * getName() const=0;

  ///@param force : display even if did not changed since previous call
  virtual int print(bool force=true, char const * const prefix=0) const 
  {return 0;}
  virtual ~MetaClassInterface(){}
};


/// Meta Information to be injected into user's class
/// be used to track how many instance of classes are living at a given time
template<typename T>
class MetaClass : public MetaClassInterface
  {
  public: 

  MetaClass();

  virtual ~MetaClass()
  {
    if ( mShared != this )
      mCounter.sub();
  }

  /// @return typename of owner class
  virtual char const * getName() const
  {
    return mName;
  }

  ///@param force : display even if did not changed since previous call  
  virtual int print(bool force, char const * const prefix=0) const;

  protected:

  /// instances counter the smart thing is here
  static CounterOf<T> mCounter;

  /// typename
  static char const * mName;

  /// shared metaclass of all instances
  static MetaClass<T>* mShared;
  };

# include "MetaClass.hpp"

#endif //_h_
