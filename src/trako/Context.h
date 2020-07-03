/* #ident "$Id:$"
 * @author: Philippe Coval <rzr@users.sf.net> -- Rev: $Author: rzr $
 * Copyright: LGPL-2 (See README file that comes with this distribution)
 *                                                           -*- Mode: c++ -*-
 *****************************************************************************/
#ifndef Context_h_
#define Context_h_

class MetaClassInterface;

#include <list>


/// global context to track all metaclass and print them
class Context
{
 public:

  ///@param prefix : used to put context in verbose output
  static void printAll(char const * const prefix=0) {
    print(prefix, true);
  }

  ///@param prefix : used to put context in verbose output
  static void printDiff(char const * const prefix=0) {
    print(prefix, false);
  }

 protected:

  ///@param force : all class type else only changed
  static void print(char const * const context=0, bool force=false);

 public:
  ///@param mList : stack on tracked class
  static std::list<MetaClassInterface const *> mList;

 private:
  Context();
  
  virtual ~Context();

  ///@param mSelf : meta object tied to the executable
  static Context mSelf;
};

#endif
