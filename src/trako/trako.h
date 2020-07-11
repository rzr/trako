/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*-
 * #ident "$Id:$"
 * @author: Philippe Coval <rzr@users.sf.net> -- Rev: $Author: rzr $
 * Copyright: LGPL-3 (See README file that comes with this distribution)
 *****************************************************************************/
#ifndef Trako_Trako_h_
#define Trako_Trako_h_

namespace trako {}

#ifndef TRAKO_CONFIG
# define TRAKO_CONFIG 1 ///< Enabled by default unless symbol defined to 0
#endif

#ifndef TRAKO_CONFIG_WARNING
# define TRAKO_CONFIG_WARNING 1 ///<! Show warnings in logs if set to 1 [1]
#endif

#if ! TRAKO_CONFIG
#  define TRAKO(CMD) ///< trako: Empty block
#else 
#  include "lib.h" /// Internal logic used by TRAKO macro
#  define TRAKO(CMD)                                    \
  TRAKO_ ## CMD ///< Paste internal macros
#endif

#if TRAKO_CONFIG_WARNING
#  if TRAKO_CONFIG
#    warning "trako: enabled: https://purl.org/rzr/trako for more"
#  else
#    warning "trako: disabled: https://purl.org/rzr/trako for more"
#  endif
#endif


#endif //_h_
