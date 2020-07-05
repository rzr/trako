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
#include "MetaScope.h"
#include "MetaMutex.h"
#include "Context.h"
#include "macros.h"

/// macro to inject a trako's meta object into the user's class
#  define TRAKO_CLASS(type)					\
  private: trako::MetaClass<type> mMeta ## type ## _	/*<! TrakO */	\
  //}

/// macro to inject a trako's meta object into the user's function
#  define TRAKO_FUNCT()						\
  trako::MetaScope lmeta(PRETTY_FUNCTION, FILE_LINE)  /*<! TrakO */	\
  //}

/// macro to inject a trako's meta object into user's scope 
/// @param name : cstring to locate context
#  define TRAKO_SCOPE(name)				\
  trako::MetaScope lmeta(name , FILE_LINE) /*<! TrakO */	\
  //}

// ### tracing helper ###

/// trace all stats of all tracked class
#  define TRAKO_COUNT()			\
  trako::Context::printStats(TRAKO_TAG("trace: "))

/// trace changed stats of all tracked class since previous trace
#  define TRAKO_DIFF()			\
  trako::Context::printDiff(TRAKO_TAG("trace: "))

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