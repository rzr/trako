/* #ident "$Id:$"
 * @author: Philippe Coval <rzr@users.sf.net> -- Rev: $Author: rzr $
 * Copyright: LGPL-3 (See README file that comes with this distribution)
 *                                                           -*- Mode: c++ -*-
 *****************************************************************************/
#include "config.h"

#ifndef CONFIG_SUPPORT_API_C_STDIO_H_NO
# include <stdio.h>
#endif

#include <ctime>

#ifndef CONFIG_SUPPORT_API_SYS_TIME_NO
# include <sys/time.h>
#endif

#include "MetaScope.h"
#include "macros.h"

//template<>
int MetaScope::mCount = 0;

#ifndef CONFIG_SUPPORT_API_SYS_TIME_NO

timeval MetaScope::mEpoc = MetaScope::init();

timeval MetaScope::init()
{
  int failed = gettimeofday(&mEpoc,0);
  if ( failed ) { mEpoc.tv_sec = mEpoc.tv_usec = 0; }
  return mEpoc;
}

#endif

MetaScope::MetaScope
( char const * const text,
  char const * const prefix,
  void* caller,
  bool verbose, bool profile)
  : mText(text), mTextPrefix(prefix),
    mVerbose(verbose), mProfile(profile)
#ifndef CONFIG_SUPPORT_API_SYS_TIME_NO
	, mTime()
#endif
{

  if ( mVerbose )
    printf
      ("%sscope: { %s @%d",
       mTextPrefix, mText,mCount);

#ifndef CONFIG_SUPPORT_API_SYS_TIME_NO
    
  if ( mProfile ) {

    timeval tim;
    int failed = gettimeofday(&tim,0);
    if ( ! failed ) {
      mTime.tv_sec = tim.tv_sec - mEpoc.tv_sec;
      mTime.tv_usec = tim.tv_usec - mEpoc.tv_usec;
    }
  }

  if ( mVerbose )
    printf
      (" [=%lds %ldus]",
        mTime.tv_sec, mTime.tv_usec);
#endif

  if ( mVerbose )
    printf("\n");

  mCount++;
}


MetaScope::~MetaScope()
{
  mCount--;
  if ( mVerbose )
    printf("%sscope: } %s @%d",
       mTextPrefix, mText,mCount);

#ifndef CONFIG_SUPPORT_API_SYS_TIME_NO
  if ( mProfile ) {

    timeval tim;
    int failed = gettimeofday(&tim,0);
    if ( ! failed ) {
      mTime.tv_sec = tim.tv_sec - mEpoc.tv_sec - mTime.tv_sec;
      mTime.tv_usec = tim.tv_usec - mEpoc.tv_usec - mTime.tv_usec;
    }
  }

  if ( mVerbose )
    printf(" [+%lds %ldus]",
        mTime.tv_sec, mTime.tv_usec);
#endif

    if ( mVerbose )
    printf("\n");

}


