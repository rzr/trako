/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*-
 * #ident "$Id:$"
 * @author: Philippe Coval <rzr@users.sf.net> -- Rev: $Author: rzr $
 * Copyright: LGPL-3 (See README file that comes with this distribution)
 *****************************************************************************/
#include <iostream>

#define EXAMPLE_CONFIG_TRAKO 1  ///< Trako: Example's configuration (optional)

#if defined(EXAMPLE_CONFIG_TRAKO) && EXAMPLE_CONFIG_TRAKO
# include <trako/trako.h> ///< Trako: Lib must be included
# define EXAMPLE(arg)                                                   \
  TRAKO(arg) ///< Trako: TRAKO macro will be used through EXAMPLE macro (optional)
#else
# define EXAMPLE(arg) //<! Trako: Extra macro to avoid speading TRACO into example (optional)
#endif

using namespace std;

int myFunction(int arg=0)
{
  EXAMPLE(FUNCT()); //<! Trako: A meta object is injected here for monitoring function
  if (arg) {
    EXAMPLE(SCOPE("myFunctionAfterTest")); //<! Trako: or for minitoring scope
    myFunction(--arg);
  }
}


class MyClass
{
public:
  EXAMPLE(CLASS(MyClass)); //<! Trako: meta object is injected here for monitoring instances
};


class MyOtherClass
{
public:
  void myMethod() {
    EXAMPLE(FUNCT()); // <! Trako: Will trace function's start ("{") and end ("}")
  }

  void mySubMethod() {
    EXAMPLE(FUNCT_VERBOSE()); //<! Trako: Same as FUNCT (optional)
    myLongMethod();
  }

protected:

  void myLongMethod() {
    EXAMPLE(FUNCT_SILENT()); //<! Trako: Track time but don't trace
    for(int i=0;i<0xFFFF;i++){ i = i + 0 * i * 0xFFFFF / 42.;}
  }

  EXAMPLE(CLASS(MyOtherClass)); //<! Same as MyClass, note the type as argument
};

struct MyEncapsulerClass
{
  virtual ~MyEncapsulerClass() {
    EXAMPLE(FUNCT()); //<! Trako: Same as FUNCT (optional)
  }
  MyClass mMember;
};

/// sample unit test programm
int main(int argc, char* argv[])
{
  EXAMPLE(FUNCT()); //<! Trako: trace: ... main.cpp: ... FUNCT: { int main ...
  int status=0;

  myFunction(2);

  cout<<endl<<"# Profiling classes instances"<<endl;
  MyClass nested;
  EXAMPLE(COUNT()); //<! trako: Count all instances of all classed, Expected: +1=1
  {
    MyClass nested;
    EXAMPLE(COUNT()); //<! trako: Expected: +1=2
  }
  MyOtherClass other;
  EXAMPLE(COUNT()); //<! trako: Expected: MyClass=1, MyOtherClass=+1


  MyClass mySclass;
  {
    {
      MyOtherClass myOther;
      EXAMPLE(DIFF()); //<! trako: Only changed instances, Expected: +2

      MyClass* ptr = new MyClass;
      EXAMPLE(DIFF()); //<! trako: Expected: +1=3

      delete( ptr );
      EXAMPLE(DIFF()); //<! trako: Expected: -1=2
    }

    EXAMPLE(TYPE(MyClass)); //<! tarko: Only count instances of type, Expected: -1=1
  }

  cout<<endl<<"# Profiling methods"<<endl;

  EXAMPLE(COUNT()); //<! trako: Print all types
  {
    MyOtherClass local;
    local.myMethod();
    local.myMethod();
  }
  EXAMPLE(DIFF()); //<! trako: print updated

  MyOtherClass myOther;
  myOther.mySubMethod();
  myOther.mySubMethod();
  EXAMPLE(PRINT_CLASS()); //<! trako:

  cout<<endl<<"# Profiling program"<<endl;
  EXAMPLE(PRINT_FUNCT());  //<! trako: Print functions durations
  {
    MyOtherClass local;
    EXAMPLE(DIFF()); //<! trako:
  }

  EXAMPLE(COUNT()); //<! trako:

  cout<<endl<<"# Profiling scopes"<<endl;
  for (int x=0;x<2;x++){
    EXAMPLE(SCOPE("row")); //<! trako: same as Functions but need to be named
    for (int y=0;y<2;y++){
      EXAMPLE(SCOPE("col")); // <<! trako: if not named  "file:line: " will be generated
    }
  }
  for(int i=0;i<0xF; i++)
    myOther.mySubMethod();

#if defined(CONFIG_TRAKO) && CONFIG_TRAKO
  cout<<endl<<"# Multithreading"<<endl;
  {
    trako::MetaMutex<std::ostream> lock; //<! trako: Extra object if need
    EXAMPLE(SCOPE("mutex: this line wont be split")); //<!
  }
#endif

  cout<<endl<<"# Reports"<<endl;
  EXAMPLE(PRINT_CLASS()); //<! trako: Print Stats
  EXAMPLE(PRINT_FUNCT()); //<! trako: Print Duration's Stats
  cout<<endl<<"# Quitting"<<endl;

  return status;
}
