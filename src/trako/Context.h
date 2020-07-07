/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*-
 * #ident "$Id:$"
 * @author: Philippe Coval <rzr@users.sf.net> -- Rev: $Author: rzr $
 * Copyright: LGPL-2 (See README file that comes with this distribution)
 *****************************************************************************/
#ifndef Context_h_
#define Context_h_

#include <list>
#include <map>

namespace trako {  
  class MetaClassInterface;
};
#include "Duration.h"

namespace trako {
  
template <typename T=void>
class Context
{
public:
  static Context<>& getInstance();

//private:

  ///@param prefix : used to put context in verbose output
  void printStats(char const * const prefix=0) {
    print(prefix, true);
  }

  ///@param prefix : used to put context in verbose output
  void printDiff(char const * const prefix=0) {
    print(prefix, false);
  }

  void printDurationStats(char const * const prefix=0, bool verbose = true);

// protected:

  ///@param force : all class type else only changed
  void print(char const * const context=0, bool force=false);

 public:
  std::list<MetaClassInterface const *>& getClassCollection();
  std::map<char const * const, Duration<> >& getDurationCollection();

  ///@param mList : stack on tracked class
  std::list<MetaClassInterface const *> mClassCollection;

 private:
  Context();
public:  
  virtual ~Context();
};
};
#include "Context.hpp"
#endif
