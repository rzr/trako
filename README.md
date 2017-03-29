Package: trako
Author: Philippe Coval <rzr@users.sf.net>
URL: http://rzr.online.fr/
Description: C++ tracking library that count instances funct calls etc


### INTRODUCTION ###

Trako aims to help profiling a C++ project in real time
without changing much of the architecture and related code to be studied...

Features :

* Class profiling :
    + count how many instances of class at a given type
    + tell how many instances where created since last query
    + ...

* Methods profiling :
    + trace methods call stack (entering or leaving)
    + mesure time spend in method or scope
    + count how many times methods have been called
    + ...

* Prevent pollution of code :
    + enable or disable using a single defines and link with a lib 
    + no additionnal code in user's files beside those a macros
    + usage of macros that can easly disabled or located removed etc
    + can be used everywhere investigation need to be focused on
      as long as you have the source code

* Integration in emacs (and probally other grep supported editors/IDE) :
    + file:line log entry format , just jump to the right place in one click


### USAGE ###

Link your app with libtrako's enabled

    CXXFLAGS+=-DCONFIG_WANT_LIBTRAKO=1
    LDFLAGS+=-ltrako


Add those "TRAKO keywords" in your tracked class ie :

    class MyClass { TRAKO_CLASS(MyClass); };


Then you can collect stats, anywhere you have to call :

    TRAKO_DIFF(); //will print new instances


and the result will be printed to console :

   src/main.cpp:73: trace: <MyClass> -1=1 =16B (<2<42 )

read it as :

* src/main.cpp: source where trace was invoked
* 54: line in previous file
* trace: tag to ease filtering
* <MyClass> : Typename of tracked class with TRAKO_CLASS keyword
* -1 : one instance was removed since last query
* =1 : number instances of it are living in ram
* = 16B  : taking 16Bytes of RAM
* (<2 : maximum different instances at a give time
* <42 ) : total of instance created


If you want to profile time spend in methods, ie:

    void funct() { TRAKO_FUNCT(); };

will display time since application startup and once returning function, ie:

    src/main.cpp:20: scope: { method @1 [=0s 706us]
    src/main.cpp:26: scope: { methodSub @2 [=0s 715us]
    src/main.cpp:26: scope: } methodSub @2 [+0s 3us]

For more have a look at those example files :

    src/main.cpp
    main.log.txt


### KNOWN BUGS AND LIMITATIONS ###

* fell free to report discovered bugs, wishes etc by email
* supporting only g++ so far
* barly supports typename collision among different namespaces


### TODO ###

Other features may come later,
most of them are already in progress if not done
I plan to publish them once polished...

* Features
** TODO [#A] assertion logs
** TODO [#B] script to ins/des/intrument source
** TODO [#B] also track non user pointers even on closed source code
** TODO [#C] port to other compilers clang msvc etc
** TODO [#C] script to display source along its trace
** TODO [#C] Integration with other tools, XML, gnuplot etc

* Refactoring tasks : 
** TODO [#C] use STL's functions objects
