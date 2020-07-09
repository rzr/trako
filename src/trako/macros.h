/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*-
 * #ident "$Id:$"
 * @author: Philippe Coval <rzr@users.sf.net> -- Rev: $Author: rzr $
 * Copyright: LGPL-2 (See README file that comes with this distribution)
 *****************************************************************************/
#ifndef Macros_h_
#define Macros_h_ __FILE__

#define TRAKO_PACKAGE "trako"
#define TRAKO_VERSION "0.1.0"

/// msvc workaround
#ifdef _MSC_VER
# define __PRETTY_FUNCTION__ __FUNCTION__
#endif

# define PRETTY_FUNCTION  __PRETTY_FUNCTION__

/// @return text
#define STR_(symbol)                            \
  #symbol

/// @return text (safer)
#define STR(symbol)                             \
  STR_(symbol)

/// convert to text safer
#define CONCAT(a,b)                             \
  ((a)##(b))

/// context in source
#define FILE_LINE                               \
  __FILE__ ":" STR(__LINE__)": "

/// context
#define TRAKO_TAG(message)                      \
  "" FILE_LINE TRAKO_PACKAGE ": " message

#endif //_h_
