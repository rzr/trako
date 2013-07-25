/* #ident "$Id:$"
 * @author: Philippe Coval <rzr@gna.org> -- Rev: $Author: rzr $
 * Copyright: LGPL-3 (See README file that comes with this distribution)
 *                                                           -*- Mode: c++ -*-
 *****************************************************************************/
#ifndef config_h_
#define config_h_ __FILE__

// This file should not be included in headers files (.h) 
// but it's safe to include it on 1st line of implementation files
// if you want to reuse it then just #include <trako/config.h>

#define PACKAGE "trako"
#define VERSION "0.0.0"

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
