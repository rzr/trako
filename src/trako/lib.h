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

/// macro to inject a trako's meta object into the user's class
#  define TRAKO_MACRO_CLASS(type)                                       \
  private: trako::MetaClass<type> mTrakoMetaClass_{}      /*<! TrakO */ \
  //}

/// macro to inject a trako's meta object into the user's function
#  define TRAKO_MACRO_FUNCT_1(verbose)                                  \
  trako::MetaClass<> lTrakoMetaFunct_(TRAKO_TAG("FUNCT: "),             \
                                      PRETTY_FUNCTION, verbose)  /*<! TrakO */ \
  //}
#  define TRAKO_MACRO_FUNCT_VERBOSE()           \
  TRAKO_MACRO_FUNCT_1(true)

#  define TRAKO_MACRO_FUNCT_SILENT()            \
  TRAKO_MACRO_FUNCT_1(false)

#  define TRAKO_MACRO_FUNCT()                   \
  TRAKO_MACRO_FUNCT_VERBOSE()

/// macro to inject a trako's meta object into user's scope
/// @param name : cstring to locate context
#  define TRAKO_MACRO_SCOPE(name)                                       \
  trako::MetaClass<> lTrakoMetaScope_(TRAKO_TAG("SCOPE: "), name "@" FILE_LINE)  /*<! TrakO */
//}

// ### tracing helper ###

#  define TRAKO_MACRO_CALL_TAG_(ns, funct)      \
  ns::funct(TRAKO_TAG(#funct ": ") )

#  define TRAKO_MACRO_CONTEXT(funct)                            \
  TRAKO_MACRO_CALL_TAG_(trako::Context<>, getInstance().funct)

/// trace all stats of all tracked class
/// trace changed stats of all tracked class since previous trace
#  define TRAKO_MACRO_CLASS_DIFF()                                      \
  trako::Context<>::getInstance().printClass(false, TRAKO_TAG("CLASS/DIFF: "));

#  define TRAKO_MACRO_FUNCT_STATS()                                     \
  trako::Context<>::getInstance().printFunct(true, TRAKO_TAG("FUNCT/STATS: "));

#  define TRAKO_MACRO_CLASS_STATS()                                     \
  trako::Context<>::getInstance().printClass(true, TRAKO_TAG("CLASS/STATS: "));

#  define TRAKO_MACRO_STATS()                                           \
  trako::Context<>::getInstance().print(true, TRAKO_TAG("STATS: "));

#  define TRAKO_MACRO_TYPE_STATS(type)          \
  TRAKO_MACRO_ #type _STATS

/// trace stats of the tracked class from tracked typename
#  define TRAKO_MACRO_TYPE(type)                                        \
  trako::MetaClass<type>::printStats(true, TRAKO_TAG("CLASS/TYPE: "))

/// trace stats of the tracked class from tracked object
#  define TRAKO_MACRO_TYPE_OF( object )         \
  TRAKO_MACRO_TYPE( typeof(object) )

#define TRAKO_FUNCT()                           \
  TRAKO_MACRO_FUNCT()
#define TRAKO_FUNCT_SILENT()                    \
  TRAKO_MACRO_FUNCT_SILENT()
#define TRAKO_FUNCT_VERBOSE()                   \
  TRAKO_MACRO_FUNCT_VERBOSE()
#define TRAKO_FUNCT_STATS()                     \
  TRAKO_MACRO_FUNCT_STATS()
#define TRAKO_SCOPE(id)                         \
  TRAKO_MACRO_SCOPE(id)

#define TRAKO_CLASS(type)                       \
  TRAKO_MACRO_CLASS(type)
#define TRAKO_CLASS_DIFF()                      \
  TRAKO_MACRO_CLASS_DIFF()
#define TRAKO_CLASS_STATS()                     \
  TRAKO_MACRO_CLASS_STATS()
#define TRAKO_TYPE(type)                        \
  TRAKO_MACRO_TYPE(type)

#define TRAKO_STATS()                           \
  TRAKO_MACRO_STATS()

/// Restore used macros if defined
#undef CLASS
#ifdef TRAKO_BACKUP_CLASS
#  define CLASS TRAKO_BACKUP_CLASS
#endif

#undef FUNCT
#ifdef TRAKO_BACKUP_FUNCT
#  define FUNCT TRAKO_BACKUP_FUNCT
#endif

#undef SCOPE
#ifdef TRAKO_BACKUP_SCOPE
#  define SCOPE TRAKO_BACKUP_SCOPE
#endif

#endif
