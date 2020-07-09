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
    void print(bool verbose=true,
               char const * const prefix=0, char const* const suffix="") {
      printClass(verbose, prefix, suffix);
      printFunct(verbose, prefix, suffix);
    }

    ///@param verbose : all class type else only changed
    void printClass(bool verbose=true,
                    char const * const prefix=0,
                    char const * const suffix="");

    void printFunct(bool verbose=true,
                    char const * const prefix=0,
                    char const * const suffix="");

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
