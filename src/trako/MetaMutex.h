/* #ident "$Id:$"
 * @author: Philippe Coval <rzr@gna.org> -- Rev: $Author: rzr $
 * Copyright: LGPL-3 (See README file that comes with this distribution)
 *                                                           -*- Mode: c++ -*-
 *****************************************************************************/
#ifndef MetaMutex_h_
#define MetaMutex_h_


#ifndef CONFIG_SUPPORT_API_PTHREAD_NO
# include <pthread.h>
#endif

template<typename T=void>
class MetaMutex
{
public: 
  MetaMutex();
  virtual ~MetaMutex();
private:
#ifndef CONFIG_SUPPORT_API_PTHREAD_NO
  static pthread_mutex_t mMutex;
#endif
};

# include "MetaMutex.hpp"


#endif //_h_
