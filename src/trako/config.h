/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*-
 * #ident "$Id:$"
 * @author: Philippe Coval <rzr@users.sf.net> -- Rev: $Author: rzr $
 * Copyright: LGPL-3 (See README file that comes with this distribution)
 *****************************************************************************/
#ifndef config_h_
#define config_h_ __FILE__

// This file should not be included in headers files (.h) 
// but it's safe to include it on 1st line of implementation files
// if you want to reuse it then just #include <trako/config.h>

#define TRAKO_PACKAGE "trako"
#define TRAKO_VERSION "0.1.0"

#ifndef PACKAGE
#  define PACKAGE TRAKO_PACKAGE
#endif

#ifndef VERSION
#  define VERSION TRAKO_VERSION
#endif

//----------------------------------------------------------------------------

//#{ platform settings:

#ifdef _MSC_VER
//# define CONFIG_SUPPORT_API_CXX_CSTDIO_NO 1
# define CONFIG_SUPPORT_API_CXXABI_NO 1
# define CONFIG_SUPPORT_API_SYS_TIME_NO 1
# define CONFIG_SUPPORT_API_PTHREAD_NO 1
#endif

//#} platform settings:

#endif //_h_
