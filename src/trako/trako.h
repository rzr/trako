/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*-
 * #ident "$Id:$"
 * @author: Philippe Coval <rzr@users.sf.net> -- Rev: $Author: rzr $
 * Copyright: LGPL-3 (See README file that comes with this distribution)
 *****************************************************************************/
#ifndef Trako_h_
#define Trako_h_

namespace trako {};

#ifndef CONFIG_WANT_LIBTRAKO
#  warning "trako: not enabled maybe it can be removed :TODO:"
#  define TRAKO(CMD)
#  define TRAKO_CLASS(type)
#  define TRAKO_FUNCT() //!<deprecated used TRAKO(CMD)
#  define TRAKO_SCOPE(name)
#  define TRAKO_DIFF()
#  define TRAKO_COUNT()
#  define TRAKO_TYPE(type)
#  define TRAKO_TYPE_OF(object)
#else

#  warning "trako: enabled it may slowdown your program :TODO:"
#  include "lib.h"

#endif

#endif //_h_
