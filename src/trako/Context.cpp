/* #ident "$Id:$"
 * @author: Philippe Coval <rzr@users.sf.net> -- Rev: $Author: rzr $
 * Copyright: LGPL-3 (See README file that comes with this distribution)
 *                                                           -*- Mode: c++ -*-
 *****************************************************************************/
#include "config.h"

#include <cstdio>
#include <iostream>

#include "MetaClass.h"
#include "macros.h"
#include "trako.h"

using namespace std;


std::list<MetaClassInterface const *> Context::mList;

Context Context::mSelf;


Context::Context()
{
  cout
    <<"trako.h:0: info: " 
    <<PACKAGE<< "-" << VERSION
    <<"program is beeing profiled"<<endl;
}


Context::~Context()
{
  cout<<"trako.h:0: info: {"<<endl;
  print(TAG("quit: "), true);
  cout<<"trako.h:0: info: }"<<endl;
}


void Context::print(char const * const context,bool force)
{
  list<MetaClassInterface const *>::const_iterator it;
  
  for( it = mList.begin();
       it != mList.end() ;
       ++it) {
    MetaClassInterface const * const p = *it;
    if ( p ) p->print(force, context);
  }
}
