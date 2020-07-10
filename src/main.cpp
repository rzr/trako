/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*-
 * #ident "$Id:$"
 * @author: Philippe Coval <rzr@users.sf.net> -- Rev: $Author: rzr $
 * Copyright: LGPL-3 (See README file that comes with this distribution)
 *****************************************************************************/
#include <iostream>
///< trako:: First download headers https://github.com/rzr/trako/
#define EXAMPLE_CONFIG_TRAKO 1  ///< trako:: Example's configuration (optional)

#if defined(EXAMPLE_CONFIG_TRAKO) && EXAMPLE_CONFIG_TRAKO
# include <trako/trako.h> ///< trako:: Find Headers (If missing clone from git)
//# undef  TRAKO_FUNCT_VERBOSE ///trako: Redefine trako macro for different behaviour
//# define TRAKO_FUNCT_VERBOSE() TRAKO_FUNCT_SILENT() ///< trako: disable trace (optional)
# define EXAMPLE_TRAKO(arg)                                             \
  TRAKO(arg) ///< trako:: Wrap to TRAKO macro to avoid spreading TRACO macro into example
#else
# define EXAMPLE_TRAKO(arg) ///< trako: If trako not included macro can remain in code
#endif



using namespace std;

void myFunction(int arg=0)
{
  EXAMPLE_TRAKO(FUNCT()); /// trako: A meta object is injected here for monitoring function
  if (arg) {
    EXAMPLE_TRAKO(SCOPE("myFunctionAfterTest")); /// trako: or for minitoring scope
    myFunction(--arg);
  }
}


class MyClass
{
public:
  void myMethod() {
    EXAMPLE_TRAKO(FUNCT()); ///< trako: Will trace function's start ("{") and end ("}")
  }
  EXAMPLE_TRAKO(CLASS(MyClass)); /// trako: meta object is injected here for monitoring instances
};


class MyOtherClass
{
public:
  void myMethod() {
    EXAMPLE_TRAKO(FUNCT()); ///< trako: Will trace function's start ("{") and end ("}")
  }

  void mySubMethod() {
    EXAMPLE_TRAKO(FUNCT_VERBOSE()); /// trako: Same as FUNCT (optional)
    myLongMethod();
  }

protected:

  void myLongMethod() {
    EXAMPLE_TRAKO(FUNCT_SILENT()); /// trako: Track time but don't trace
    for(int i=0;i<0xFFFF;i++){ i = i + 0 * i * 0xFFFFF / 42.;}
  }

  EXAMPLE_TRAKO(CLASS(MyOtherClass)); //<! Same as MyClass, note the type as argument
};

struct MyEncapsulerClass
{
  virtual ~MyEncapsulerClass() {
    EXAMPLE_TRAKO(FUNCT()); /// trako: Same as FUNCT (optional)
  }
  MyClass mMember;
};

/// sample unit test programm
int main(int argc, char* argv[])
{
  EXAMPLE_TRAKO(FUNCT()); /// trako: trace: ... main.cpp: ... FUNCT: { int main ...
  int status=0;

  cout<<endl<<"# Tracing functions:"<<endl;
  myFunction(2);

  cout<<endl<<"# Monitoring classes instances"<<endl;
  MyClass nested;
  EXAMPLE_TRAKO(CLASS_STATS()); ///< trako: Count all instances of all classed, Expected: +1=1
  nested.myMethod(); ///< Just use to prevent error: unused variable 
  {
    MyClass nested;
    EXAMPLE_TRAKO(CLASS_STATS()); ///< trako: Expected: +1=2
    nested.myMethod(); ///< Just use to prevent error: unused variable 
  }
  MyOtherClass other;
  EXAMPLE_TRAKO(CLASS_STATS()); ///< trako: Expected: MyClass=1, MyOtherClass=+1

  MyClass mySclass;
  {
    EXAMPLE_TRAKO(TYPE(MyClass)); //<! tarko: Only count instances of type
    {
      MyOtherClass myOther;
      EXAMPLE_TRAKO(CLASS_DIFF()); ///< trako: Only changed instances, Expected: +2
      myOther.myMethod();

      MyClass* ptr = new MyClass;
      EXAMPLE_TRAKO(CLASS_DIFF()); ///< trako: Expected: +1=3

      delete( ptr );
      EXAMPLE_TRAKO(CLASS_DIFF()); ///< trako: Expected: -1=2
    }
  }
  cout<<endl<<"# Monitoring methods"<<endl;

  EXAMPLE_TRAKO(CLASS_STATS()); ///< trako: Print all types
  {
    MyOtherClass local;
    local.myMethod();
    local.myMethod();
  }
  EXAMPLE_TRAKO(CLASS_DIFF()); ///< trako: print updated

  MyOtherClass myOther;
  myOther.mySubMethod();
  myOther.mySubMethod();
  EXAMPLE_TRAKO(CLASS_STATS()); ///< trako:

  cout<<endl<<"# Monitoring program"<<endl;
  EXAMPLE_TRAKO(FUNCT_STATS());  ///< trako: Print functions durations
  {
    MyOtherClass local;
    EXAMPLE_TRAKO(CLASS_DIFF()); ///< trako:
    local.myMethod();
  }

  EXAMPLE_TRAKO(CLASS_STATS()); ///< trako:

  cout<<endl<<"# Monitoring scopes"<<endl;
  for (int x=0;x<2;x++){
    EXAMPLE_TRAKO(SCOPE("row")); ///< trako: same as Functions but need to be named
    for (int y=0;y<2;y++){
      EXAMPLE_TRAKO(SCOPE("col")); ///<! trako: if not named  "file:line: " will be generated
    }
  }
  for(int i=0;i<0xF; i++)
    myOther.mySubMethod();

#if defined(EXAMPLE_CONFIG_TRAKO) & EXAMPLE_CONFIG_TRAKO && CONFIG_TRAKO
  cout<<endl<<"# Multithreading"<<endl;
  {
    trako::MetaMutex<std::ostream> lock; ///< trako: Extra object if need
    EXAMPLE_TRAKO(SCOPE("mutex: this line wont be split")); //<!
  }
#endif

  cout<<endl<<"# Reports"<<endl;
  EXAMPLE_TRAKO(STATS()); ///< trako: Print Stats (Functs and Classes)
  cout<<endl<<"# Quitting"<<endl;

  return status;
}
