/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*-
 * @author: Philippe Coval <rzr@users.sf.net> -- Rev: $Author: rzr $
 * Copyright: LGPL-3 (See README file that comes with this distribution)
 *****************************************************************************/
#ifndef TrakoLib_h_
#define TrakoLib_h_

// Backup used macros if defined
#ifdef CLASS
#  define TRAKO_BACKUP_CLASS CLASS
#endif
#ifdef FUNCT
#  define TRAKO_BACKUP_FUNCT FUNCT
#endif
#ifdef SCOPE
#  define TRAKO_BACKUP_SCOP SCOPE
#endif


namespace trako {}

namespace trako {
  class MetaClassInterface;
}

// ### meta objects ###
#include "MetaClass.h"
#include "MetaMutex.h"
#include "Context.h"
#include "macros.h"

/// Generic macros to minimize pollution symbols
#  define TRAKO(CMD)                            \
  TRAKO_##CMD

#  define TRAKO_1(CMD)                          \
  TRAKO(CMD)()

#  define TRAKO_2(CMD, a)                       \
  TRAKO(CMD)(a)

/// macro to inject a trako's meta object into the user's class
#  define TRAKO_CLASS(type)                                             \
  private: trako::MetaClass<type> mTrakoMetaClass_{}      /*<! TrakO */ \
  //}

/// macro to inject a trako's meta object into the user's function
#  define TRAKO_FUNCT_1(verbose)                                        \
  trako::MetaClass<> lTrakoMetaFunct_(TRAKO_TAG("FUNCT: "),             \
                                      PRETTY_FUNCTION, verbose)  /*<! TrakO */ \
  //}
#  define TRAKO_FUNCT_VERBOSE()                 \
  TRAKO_FUNCT_1(true)

#  define TRAKO_FUNCT_SILENT()                  \
  TRAKO_FUNCT_1(false)

#  define TRAKO_FUNCT()                         \
  TRAKO_FUNCT_VERBOSE()

/// macro to inject a trako's meta object into user's scope
/// @param name : cstring to locate context
#  define TRAKO_SCOPE(name)                                             \
  trako::MetaClass<> lTrakoMetaScope_(TRAKO_TAG("SCOPE: "), name "@" FILE_LINE)  /*<! TrakO */
//}

// ### tracing helper ###

#  define TRAKO_CALL_TAG_(ns, funct)            \
  ns::funct(TRAKO_TAG(#funct ": ") )

#  define TRAKO_CONTEXT(funct)                                  \
  TRAKO_CALL_TAG_(trako::Context<>, getInstance().funct)

/// trace all stats of all tracked class
/// trace changed stats of all tracked class since previous trace
#  define TRAKO_CLASS_DIFF()                                            \
  trako::Context<>::getInstance().printClass(false, TRAKO_TAG("CLASS/DIFF: "));

#  define TRAKO_FUNCT_STATS()                                           \
  trako::Context<>::getInstance().printFunct(true, TRAKO_TAG("FUNCT/STATS: "));

#  define TRAKO_CLASS_STATS()                                           \
  trako::Context<>::getInstance().printClass(true, TRAKO_TAG("CLASS/STATS: "));

#  define TRAKO_STATS()                                                 \
  trako::Context<>::getInstance().print(true, TRAKO_TAG("STATS: "));

#  define TRAKO_TYPE_STATS(type)                \
  TRAKO_ #type _STATS

/// trace stats of the tracked class from tracked typename
#  define TRAKO_TYPE(type)                                              \
  trako::MetaClass<type>::printStats(true, TRAKO_TAG("CLASS/TYPE: "))

/// trace stats of the tracked class from tracked object
#if 0
#  define TRAKO_TYPE_OF( object )               \
  TRAKO_TYPE( typeof(object) )
#else
#  define TRAKO_TYPE_OF( object )               \
  TRAKO_TYPE( void*)
#endif

// Restore used macros if defined
#define TRAKO_MACRO_CLASS CLASS
#undef CLASS
#ifdef TRAKO_BACKUP_CLASS
#  define CLASS TRAKO_BACKUP_CLASS
#endif

#define TRAKO_MACRO_FUNCT FUNCT
#undef FUNCT
#ifdef TRAKO_BACKUP_FUNCT
#  define FUNCT TRAKO_BACKUP_FUNCT
#endif

#define TRAKO_MACRO_SCOPE SCOPE
#undef SCOPE
#ifdef TRAKO_BACKUP_SCOPE
#  define SCOPE TRAKO_BACKUP_SCOPE
#endif


#endif
