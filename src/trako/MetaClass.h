/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*-
 * #ident "$Id:$"
 * @author: Philippe Coval <rzr@users.sf.net> -- Rev: $Author: rzr $
 * Copyright: LGPL-3 (See README file that comes with this distribution)
 *****************************************************************************/
#ifndef MetaClass_h_
#define MetaClass_h_

#include "Duration.h"
#include "UtilsOf.h"

namespace trako {

  /// trako's common function to be used elsewhere (not tied to a type)
  class MetaClassInterface
  {
  public:
    ///@return typename
    virtual char const * getName() const=0;

    ///@param verbose : display even if did not changed since previous call
    virtual int print(bool verbose=true,
                      char const * const prefix=0,
                      char const * const suffix="") const { return 0; }
    virtual ~MetaClassInterface(){}
  };


  /// Meta Information to be injected into user's class
  /// be used to track how many instance of classes are living at a given time
  template<typename T = void>
  class MetaClass : public MetaClassInterface
  {
  public:
    static int printStats(bool verbose=true,
                          char const * const prefix=0,
                          char const * const suffix="");

    MetaClass(char const * const prefix=0, char const * const name=0,
              bool verbose=true, bool profile=true);

    virtual ~MetaClass();

    /// @return typename of owner class
    virtual char const * getName() const
    {
      return mName;
    }

    ///@param force : display even if did not changed since previous call
    virtual int print(bool force=true,
                      char const * const prefix=0,
                      char const * const suffix="") const;

  protected:
    MetaClass(const MetaClass<T>&) = delete;
    MetaClass operator=(const MetaClass<T>&) = delete;

  protected:
    char const* mPrefix; ///< context's message's is used as id
    char const * mName;  ///< pretty name
    bool mFunct; ///< Execution Context for functions not classes
    bool mVerbose; ///< enable trace
    bool mProfile; ///< enable time profiling
    Duration<>* mDuration; ///< time counter for functs
    static MetaClass<T>* mShared; ///< Shared metaclass of all instances
    static CounterOf<T> mCounter; ///< instances counter smart
    static CounterOf< MetaClass<T> > mDepthCounter; ///< for functs
  };
}

# include "MetaClass.hpp"

#endif //_h_
