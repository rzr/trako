/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*-
 * @author: Philippe Coval <rzr@users.sf.net> -- Rev: $Author: rzr $
 * Copyright: LGPL-3 (See README file that comes with this distribution)
 *****************************************************************************/
#ifndef TrakoLib_h_
#define TrakoLib_h_

namespace trako {};

namespace trako {
  class MetaClassInterface;
};
// ### meta objects ###
#include "MetaClass.h"
#include "MetaMutex.h"
#include "Context.h"
#include "macros.h"

/// Generic macros to minimize pollution symbols
#  define TRAKO_ exit(42)

#  define TRAKO(CMD)                            \
  TRAKO_##CMD

#  define TRAKO_1(CMD)                          \
  TRAKO(CMD)()

#  define TRAKO_2(CMD,a)                         \
  TRAKO(CMD)(a)

/// macro to inject a trako's meta object into the user's class
#  define TRAKO_CLASS(type)					\
  private: trako::MetaClass<type> mMeta ## type ## _	/*<! TrakO */	\
  //}

/// macro to inject a trako's meta object into the user's function
#  define TRAKO_FUNCT_1(verbose)						\
  trako::MetaClass<> lTrakoMetaFunct_(TRAKO_TAG("FUNCT: "), PRETTY_FUNCTION, verbose)  /*<! TrakO */ \
  //}
#  define TRAKO_FUNCT()	\
  TRAKO_FUNCT_1(true)

/// macro to inject a trako's meta object into user's scope 
/// @param name : cstring to locate context
#  define TRAKO_SCOPE(name)				\
  trako::MetaClass<> lTrakoMetaScope_(TRAKO_TAG("SCOPE: "), name "@" FILE_LINE)  /*<! TrakO */ 
  //}

// ### tracing helper ###

#  define TRAKO_CALL_TAG_(ns, funct)            \
  ns::funct(TRAKO_TAG(#funct ": ") )

#  define TRAKO_CONTEXT(funct)                  \
  TRAKO_CALL_TAG_(trako::Context<>, funct)

/// trace all stats of all tracked class
#  define TRAKO_COUNT()			\
  TRAKO_CONTEXT(printStats)

/// trace changed stats of all tracked class since previous trace
#  define TRAKO_DIFF()			\
  TRAKO_CONTEXT(printDiff)

/// trace stats of the tracked class from tracked typename
#  define TRAKO_TYPE( type )			\
  trako::MetaClass<type>::printStats(TRAKO_TAG("type: "), true)

/// trace stats of the tracked class from tracked object
#if 0
#  define TRAKO_TYPE_OF( object )		\
  TRAKO_TYPE( typeof(object) )
#else
#  define TRAKO_TYPE_OF( object )		\
  TRAKO_TYPE( void*)
#endif

  

#endif
