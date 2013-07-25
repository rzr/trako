/* #ident "$Id:$"
 * @author: Philippe Coval <rzr@gna.org> -- Rev: $Author: rzr $
 * Copyright: LGPL-3 (See README file that comes with this distribution)
 *                                                           -*- Mode: c++ -*-
 *****************************************************************************/
#include <iostream>

#define CONFIG_WANT_LIBTRAKO
#include "trako/config.h"
#include "trako/trako.h"

#include "Context.h"

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

    //TRAKO_TYPE( MyClass ); //<! @INFO:
  }

  cout<<endl<<"# Profiling methods"<<endl;

  TRAKO_COUNT(); //<! @INFO

  {
    MyClass local;
    local.method();
    local.method();
  }

  TRAKO_DIFF(); //<! @INFO:

  MyOtherClass local;
  local.methodLong();
  TRAKO_TYPE_OF( local ); //<! @INFO:

  cout<<endl<<"# Profiling program"<<endl;
  {
    MyOtherClass local;
  }

  TRAKO_COUNT(); //<! @INFO:

  cout<<endl<<"# Profiling scopes"<<endl;
  for (int x=0;x<2;x++){
    TRAKO_SCOPE("row");
    for (int y=0;y<2;y++){
      TRAKO_SCOPE("col");
    }
  }

  cout<<endl<<"# Multithreading"<<endl;
  {
    MetaMutex lock;
    TRAKO_SCOPE("mutex: this line wont be split"); //<! @INFO
  }


  cout<<endl<<"# Quitting"<<endl;

  return status;
}
