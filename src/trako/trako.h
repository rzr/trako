/* #ident "$Id:$"
 * @author: Philippe Coval <rzr@gna.org> -- Rev: $Author: rzr $
 * Copyright: LGPL-3 (See README file that comes with this distribution)
 *                                                           -*- Mode: c++ -*-
 *****************************************************************************/
#ifndef Trako_h_
#define Trako_h_

class MetaClassInterface;

#include "MetaClass.h"
#include "MetaScope.h"
#include "Context.h"
#include "macros.h"


// ### meta objects ###


# ifndef CONFIG_WANT_LIBTRAKO //undefine used macros

#  define TRAKO_CLASS(type)
#  define TRAKO_FUNCT()
#  define TRAKO_SCOPE(name)
#  define TRAKO_DIFF()
#  define TRAKO_COUNT()
#  define TRAKO_TYPE(type)
#  define TRAKO_TYPE_OF(object)

# else

/// macro to inject a trako's meta object into the user's class
#  define TRAKO_CLASS(type)					\
  private: MetaClass<type> mMeta ## type ## _	/*<! TrakO */	\
  //}

/// macro to inject a trako's meta object into the user's function
#  define TRAKO_FUNCT()						\
  MetaScope lmeta(PRETTY_FUNCTION, FILE_LINE)  /*<! TrakO */	\
  //}

/// macro to inject a trako's meta object into user's scope 
/// @param name : cstring to locate context
#  define TRAKO_SCOPE(name)				\
  MetaScope lmeta(name , FILE_LINE) /*<! TrakO */	\
  //}

// ### tracing helper ###

/// trace all stats of all tracked class
#  define TRAKO_COUNT()			\
  Context::printAll( TAG("trace: ") )

/// trace changed stats of all tracked class since previous trace
#  define TRAKO_DIFF()			\
  Context::printDiff( TAG("trace: ") )

/// trace stats of the tracked class from tracked typename
#  define TRAKO_TYPE( type )			\
  CounterOf<type>::print(true, TAG("type: ") )

/// trace stats of the tracked class from tracked object
#if 0
#  define TRAKO_TYPE_OF( object )		\
  TRAKO_TYPE( typeof(object) )
#else
#  define TRAKO_TYPE_OF( object )		\
  TRAKO_TYPE( void*)
#endif


# endif

#endif //_h_
