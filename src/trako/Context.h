/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*-
 * #ident "$Id:$"
 * @author: Philippe Coval <rzr@users.sf.net> -- Rev: $Author: rzr $
 * Copyright: LGPL-2 (See README file that comes with this distribution)
 *****************************************************************************/
#ifndef Context_h_
#define Context_h_

#include <list>

namespace trako {
class MetaClassInterface;
}

namespace trako {

/// global context to track all metaclass and print them
template <typename T=void>
class Context
{
 public:

  ///@param prefix : used to put context in verbose output
  static void printStats(char const * const prefix=0) {
    print(prefix, true);
  }

  ///@param prefix : used to put context in verbose output
  static void printDiff(char const * const prefix=0) {
    print(prefix, false);
  }

  static void printDurationStats(char const * const prefix=0);

 protected:

  ///@param force : all class type else only changed
  static void print(char const * const context=0, bool force=false);

 public:
  ///@param mList : stack on tracked class
  static std::list<trako::MetaClassInterface const *> mList;

 private:
  Context();
  
  virtual ~Context();

  ///@param mSelf : meta object tied to the executable
  static Context mSelf;
};
};
#include "Context.hpp"
#endif
