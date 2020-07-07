/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*-
 * #ident "$Id:$"
 * @author: Philippe Coval <rzr@users.sf.net> -- Rev: $Author: rzr $
 * Copyright: LGPL-3 (See README file that comes with this distribution)
 *****************************************************************************/
#ifndef Trako_Trako_h_
#define Trako_Trako_h_

namespace trako {};

#ifndef TRAKO_CONFIG
# define TRAKO_CONFIG 1
#endif

#if TRAKO_CONFIG
#  warning "trako: enabled, TRAKO macro can be used"
#  include "lib.h"
#else
#  warning "trako: disabled, only TRAKO macros are still exported, remove include if not needed"
#  define TRAKO(CMD) /// !<empty block, that will not be compiled
#  define TRAKO_1(CMD)  /// !<empty block have no effect on perf
#  define TRAKO_2(CMD, a) ///!<empty if command use args

#  define TRAKO_CLASS(type) /// !<deprecated, prefer TRAKO_2(CLASS, type)
#  define TRAKO_FUNCT() /// !<deprecated, prefer TRAKO_1(FUNCT)
#  define TRAKO_SCOPE(name) /// !<deprecated prefer TRAKO_2(SCOPE, name)
#  define TRAKO_DIFF() /// !<deprecated prefer TRAKO_1(...)
#  define TRAKO_COUNT() /// !<deprecated prefer TRAKO_N(COUNT)
#  define TRAKO_TYPE(type) /// !<deprecated prefer TRAKO_N(TYPE, name)
#  define TRAKO_TYPE_OF(object) /// !<deprecated prefer TRAKO_N(...)
#endif


#endif //_h_
