/* #ident "$Id:$"
 * @author: Philippe Coval <rzr@gna.org> -- Rev: $Author: rzr $
 * Copyright: LGPL-3 (See README file that comes with this distribution)
 *                                                           -*- Mode: c++ -*-
 *****************************************************************************/
#ifndef MetaScope_h_
#define MetaScope_h_

#include "trako.h"

#ifndef CONFIG_SUPPORT_API_SYS_TIME_NO
# include <sys/time.h>
#endif

/// meta object related to a scope, counting calls and produce traces
class MetaScope
{
public:

  /// @param text : context ie : PRETTY_FUNCTION
  /// @param prefix : will be be printed before context ie : FILE_LINE
  /// @param caller : address of client's object ie : this
  /// @param verbose : enable tracing
  /// @param profile : enable profiling
  MetaScope
  (char const * const text=0,
   char const * const prefix=0,
   void* caller=0,
   bool verbose=true, bool profile=true);

  virtual ~MetaScope();

protected:
  /// context's message
  char const* mText;
  /// context's message's prefix
  char const* mTextPrefix;
  /// enable trace
  bool mVerbose;
  /// enable time profiling
  bool mProfile;
  /// level of depth in call stack of tracked functions
  static int mCount;

#ifndef CONFIG_SUPPORT_API_SYS_TIME_NO
  /// current time
  timeval mTime;
  /// reference time since application startup
  static timeval mEpoc;
 protected:
  /// helper to init app's epoc time
  static timeval init();
#endif

};

#endif
