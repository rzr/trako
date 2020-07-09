/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*-
 * #ident "$Id:$"
 * @author: Philippe Coval <rzr@users.sf.net> -- Rev: $Author: rzr $
 * Copyright: LGPL-3 (See README file that comes with this distribution)
 *****************************************************************************/
#ifndef MetaMutex_h_
#define MetaMutex_h_


#ifndef CONFIG_SUPPORT_API_PTHREAD_NO
# include <pthread.h>
#endif

namespace trako {

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
}

# include "MetaMutex.hpp"


#endif //_h_
