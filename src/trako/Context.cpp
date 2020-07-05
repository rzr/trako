/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*-
 * #ident "$Id:$"
 * @author: Philippe Coval <rzr@users.sf.net> -- Rev: $Author: rzr $
 * Copyright: LGPL-3 (See README file that comes with this distribution)
 *****************************************************************************/
#include "config.h"

#include <cstdio>
#include <iostream>

#include "Context.h"
#include "MetaClass.h"
#include "macros.h"

using namespace std;
using namespace trako;


std::list<MetaClassInterface const *> Context::mList;

Context Context::mSelf;


Context::Context()
{
  print(TRAKO_TAG("start: "), true);
}


Context::~Context()
{
  print(TRAKO_TAG("stop: "), true);
}


void Context::print(char const * const context, bool force)
{
  list<MetaClassInterface const *>::const_iterator it;
  
  for( it = mList.begin();
       it != mList.end() ;
       ++it) {
    MetaClassInterface const * const p = *it;
    if ( p ) p->print(context, force);
  }
}
