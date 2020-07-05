/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*-
 * #ident "$Id:$"
 * @author: Philippe Coval <rzr@users.sf.net> -- Rev: $Author: rzr $
 * Copyright: LGPL-3 (See README file that comes with this distribution)
 *****************************************************************************/
#ifndef MetaScope_h_
#define MetaScope_h_

#include "UtilsOf.hpp"


namespace trako {
/// meta object related to a scope, counting calls and produce traces
template <typename T = void>
class MetaScope
{
public:
  static void print(char const * const prefix = TRAKO_TAG("count: "));
public:

  /// @param text : context ie : PRETTY_FUNCTION
  /// @param prefix : will be be printed before context ie : FILE_LINE
  /// @param verbose : enable tracing
  MetaScope
  (char const * const name=0, char const * const prefix=0,
   bool verbose=true);

  virtual ~MetaScope();

protected:
  /// context's id
  char const* mName;
  /// context's message's prefix
  char const* mPrefix;
  /// enable trace
  bool mVerbose;
  /// enable time profiling
  bool mProfile;
  /// level of depth in call stack of tracked functions
  static CounterOf<MetaScope<T>> mCounter;
};
};

#include "MetaScope.hpp"

#endif
