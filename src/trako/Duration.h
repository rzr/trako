/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*-
 * @author: Philippe Coval <rzr@users.sf.net> -- Rev: $Author: rzr $
 * Copyright: LGPL-3 (See README file that comes with this distribution)
 *****************************************************************************/

#ifndef Duration_h_
#define Duration_h_

#ifndef CONFIG_SUPPORT_API_SYS_TIME_NO
# include <sys/time.h>
#else
# warning "TODO: port to use std::chrono"
#endif
#include <map>


namespace trako {

template<typename T=void>
class Duration
{
public:
  static void printStats(char const * const prefix=0, bool verbose=true);
  static Duration<>& get(char const * const prefix, char const * const name=0);
  Duration(char const * const prefix=0, char const * const name=0,
           bool verbose=false);
public:
  void print(char const * const prefix=0, bool verbose=true,
             char const * const suffix="\n") const;
  void start(bool verbose=false);
  void stop(bool verbose=false);
protected:
  char const * mPrefix; ///< Id context used as map's key
  char const * mName;
  unsigned int mCount;
  unsigned int mDepth; ///< handle Rentrants functions (TODO improve w/ counter)
  bool mProfile;
  bool mVerbose;
  unsigned long mValue; /*!< Observed time, once stop is called */
  unsigned long mCumulated; ///< total time spend in function
  unsigned long mMaximum; ///< unused yet
  unsigned long mMinimum; ///< use counter TODO
  float mRatio;
#ifndef CONFIG_SUPPORT_API_SYS_TIME_NO
public:
  static timeval getTime();
  static unsigned long timeToDuration(timeval time);
  static timeval diffTime(timeval before, timeval after);
  static unsigned long getDuration();
  static unsigned long getElapsed();
protected:
  static unsigned long mElapsed; /*!< Current time updated by getTime */
  static timeval mEpocTime; /*!< reference time since 1st use */
  static timeval mNowTime;
  timeval mStartTime;
  timeval mStopTime;
#endif
protected:
  static std::map<char const * const, Duration<>> mCollection;
};
};

#include "Duration.hpp"

#endif //_h_
