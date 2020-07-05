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
using namespace std;

template<typename T=void>
class Duration
{
public:
  static void printStats(char const * const prefix=0);
  static Duration<T>& get(char const * const name=0);
  Duration(bool verbose=false);
public:
  void print(char const * const prefix=0) const;
  void start(bool verbose=false);
  void stop(bool verbose=false);
protected:
  char const * mName;
  unsigned int mCount;
  bool mProfile;
  bool mVerbose;
  unsigned long mValue; /*!< Observed time, once stop is called */
  unsigned long mCumulated;
  unsigned long mMaximum;
  unsigned long mMinimum;
  float mRatio;
#ifndef CONFIG_SUPPORT_API_SYS_TIME_NO
public:
  static timeval getTime();
  static unsigned long getElapsed();
protected:
  static unsigned long mElapsed; /*!< Current time updated by getTime */
  static timeval mEpocTime; /*!< reference time since 1st use */
  static timeval mNowTime;
  timeval mStartTime;
  timeval mStopTime;
#endif
protected:
  static std::map<char const * const, Duration> mCollection;
};

#include "Duration.hpp"

#endif //_h_
