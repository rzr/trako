/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*-
 * #ident "$Id:$"
 * @author: Philippe Coval <rzr@users.sf.net> -- Rev: $Author: rzr $
 * Copyright: LGPL-3 (See README file that comes with this distribution)
 *****************************************************************************/
#include <iostream>

#define CONFIG_WANT_LIBTRAKO

#if defined(CONFIG_TRAKO_WANT_INLINE) && CONFIG_TRAKO_WANT_INLINE
# include <trako/trako.cxx>
#else
# include <trako/trako.h>
#endif

#ifndef TRACKO
# warning "trako: TODO: include problem"
#endif

using namespace std;


class MyClass;

/// sample class nothing special here, beside then lines marked @INFO
class MyClass
{
public:
  void method() {
    TRAKO_FUNCT(); //<! @INFO: here a metaobject is injected in the function
    methodSub();
  }

private:
  void methodSub() {
    TRAKO_FUNCT(); //<! @INFO: here a metaobject is injected in the function
  }

  TRAKO_CLASS(MyClass); //<! @INFO: here a metaobject is injected in the class
};


class MyOtherClass
{
public:
  void methodLong()
  {
    TRAKO_FUNCT(); //<! @INFO: here a metaobject is injected in the function
    for(int i=0;i<0xFFFF;i++){ 0xFFFFF / 42.;}
  }

  TRAKO_CLASS(MyOtherClass);
};


/// sample unit test programm
int main(int argc, char* argv[])
{
  TRAKO_FUNCT(); //<! @INFO:
  int status=0;

  cout<<endl<<"# Profiling classes instances"<<endl;
  MyClass sta;
  TRAKO_DIFF(); //<! @INFO:

  {
    {
      MyClass local;
      TRAKO_DIFF(); //<! @INFO:

      MyClass* ptr = new MyClass;
      TRAKO_DIFF(); //<! @INFO:

      delete( ptr );
      TRAKO_DIFF(); //<! @INFO:
    }

    TRAKO_TYPE( MyClass ); //<! @INFO:
  }

  cout<<endl<<"# Profiling methods"<<endl;

  TRAKO_COUNT(); //<! @INFO

  {
    MyClass local;
    local.method();
    local.method();
  }
  TRAKO_CONTEXT(printDurationStats); //<! @INFO
  TRAKO_DIFF(); //<! @INFO:

  MyOtherClass local;
  local.methodLong();
  local.methodLong();
  TRAKO_TYPE_OF( local ); //<! @INFO:

  cout<<endl<<"# Profiling program"<<endl;
  {
    MyOtherClass local;
    TRAKO_DIFF(); //<! @INFO:
  }

  TRAKO_COUNT(); //<! @INFO:

  cout<<endl<<"# Profiling scopes"<<endl;
  for (int x=0;x<2;x++){
    TRAKO_SCOPE("row");
    for (int y=0;y<2;y++){
      TRAKO_SCOPE("col");
    }
  }
  for(int i=0;i<0xFF; i++)
    local.methodLong();

  cout<<endl<<"# Multithreading"<<endl;
  {
    trako::MetaMutex<std::ostream> lock;
    TRAKO_SCOPE("mutex: this line wont be split"); //<! @INFO
  }

  cout<<endl<<"# Reports"<<endl;
  TRAKO_CONTEXT(printDurationStats); //<! @INFO

  cout<<endl<<"# Quitting"<<endl;
  TRAKO_COUNT(); //<! @INFO:

  return status;
}
