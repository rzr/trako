/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*-
 * #ident "$Id:$"
 * @author: Philippe Coval <rzr@users.sf.net> -- Rev: $Author: rzr $
 * Copyright: LGPL-3 (See README file that comes with this distribution)
 *****************************************************************************/
#include <iostream>
///< Trako: First download headers https://github.com/rzr/trako/
#define EXAMPLE_CONFIG_TRAKO 1  ///< Trako: Example's configuration (optional)

#if defined(EXAMPLE_CONFIG_TRAKO) && EXAMPLE_CONFIG_TRAKO
# include <trako/trako.h> ///< Trako: Find Headers (If missing clone from git)
# define EXAMPLE_TRAKO(arg)                                                   \
  TRAKO(arg) ///< Trako: Wrap to TRAKO macro to avoid spreading TRACO macro into example
#else
# define EXAMPLE_TRAKO(arg) //<! Trako: If trako not included macro can remain in code
#endif

using namespace std;

int myFunction(int arg=0)
{
  EXAMPLE_TRAKO(FUNCT()); //<! Trako: A meta object is injected here for monitoring function
  if (arg) {
    EXAMPLE_TRAKO(SCOPE("myFunctionAfterTest")); //<! Trako: or for minitoring scope
    myFunction(--arg);
  }
}


class MyClass
{
public:
  EXAMPLE_TRAKO(CLASS(MyClass)); //<! Trako: meta object is injected here for monitoring instances
};


class MyOtherClass
{
public:
  void myMethod() {
    EXAMPLE_TRAKO(FUNCT()); // <! Trako: Will trace function's start ("{") and end ("}")
  }

  void mySubMethod() {
    EXAMPLE_TRAKO(FUNCT_VERBOSE()); //<! Trako: Same as FUNCT (optional)
    myLongMethod();
  }

protected:

  void myLongMethod() {
    EXAMPLE_TRAKO(FUNCT_SILENT()); //<! Trako: Track time but don't trace
    for(int i=0;i<0xFFFF;i++){ i = i + 0 * i * 0xFFFFF / 42.;}
  }

  EXAMPLE_TRAKO(CLASS(MyOtherClass)); //<! Same as MyClass, note the type as argument
};

struct MyEncapsulerClass
{
  virtual ~MyEncapsulerClass() {
    EXAMPLE_TRAKO(FUNCT()); //<! Trako: Same as FUNCT (optional)
  }
  MyClass mMember;
};

/// sample unit test programm
int main(int argc, char* argv[])
{
  EXAMPLE_TRAKO(FUNCT()); //<! Trako: trace: ... main.cpp: ... FUNCT: { int main ...
  int status=0;

  myFunction(2);

  cout<<endl<<"# Profiling classes instances"<<endl;
  MyClass nested;
  EXAMPLE_TRAKO(COUNT()); //<! trako: Count all instances of all classed, Expected: +1=1
  {
    MyClass nested;
    EXAMPLE_TRAKO(COUNT()); //<! trako: Expected: +1=2
  }
  MyOtherClass other;
  EXAMPLE_TRAKO(COUNT()); //<! trako: Expected: MyClass=1, MyOtherClass=+1


  MyClass mySclass;
  {
    {
      MyOtherClass myOther;
      EXAMPLE_TRAKO(DIFF()); //<! trako: Only changed instances, Expected: +2

      MyClass* ptr = new MyClass;
      EXAMPLE_TRAKO(DIFF()); //<! trako: Expected: +1=3

      delete( ptr );
      EXAMPLE_TRAKO(DIFF()); //<! trako: Expected: -1=2
    }

    EXAMPLE_TRAKO(TYPE(MyClass)); //<! tarko: Only count instances of type, Expected: -1=1
  }

  cout<<endl<<"# Profiling methods"<<endl;

  EXAMPLE_TRAKO(COUNT()); //<! trako: Print all types
  {
    MyOtherClass local;
    local.myMethod();
    local.myMethod();
  }
  EXAMPLE_TRAKO(DIFF()); //<! trako: print updated

  MyOtherClass myOther;
  myOther.mySubMethod();
  myOther.mySubMethod();
  EXAMPLE_TRAKO(PRINT_CLASS()); //<! trako:

  cout<<endl<<"# Profiling program"<<endl;
  EXAMPLE_TRAKO(PRINT_FUNCT());  //<! trako: Print functions durations
  {
    MyOtherClass local;
    EXAMPLE_TRAKO(DIFF()); //<! trako:
  }

  EXAMPLE_TRAKO(COUNT()); //<! trako:

  cout<<endl<<"# Profiling scopes"<<endl;
  for (int x=0;x<2;x++){
    EXAMPLE_TRAKO(SCOPE("row")); //<! trako: same as Functions but need to be named
    for (int y=0;y<2;y++){
      EXAMPLE_TRAKO(SCOPE("col")); // <<! trako: if not named  "file:line: " will be generated
    }
  }
  for(int i=0;i<0xF; i++)
    myOther.mySubMethod();

#if defined(EXAMPLE_CONFIG_TRAKO) & EXAMPLE_CONFIG_TRAKO
  cout<<endl<<"# Multithreading"<<endl;
  {
    trako::MetaMutex<std::ostream> lock; //<! trako: Extra object if need
    EXAMPLE_TRAKO(SCOPE("mutex: this line wont be split")); //<!
  }
#endif

  cout<<endl<<"# Reports"<<endl;
  EXAMPLE_TRAKO(PRINT_CLASS()); //<! trako: Print Stats
  EXAMPLE_TRAKO(PRINT_FUNCT()); //<! trako: Print Duration's Stats
  cout<<endl<<"# Quitting"<<endl;

  return status;
}
