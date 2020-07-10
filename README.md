# TRAKO #

[![GitHub forks](
https://img.shields.io/github/forks/rzr/trako.svg?style=social&label=Fork&maxAge=2592000
)](
https://GitHub.com/rzr/trako/network/
)
[![license](
https://img.shields.io/badge/license-LGPL-3p.svg
)](COPYING)
[![Codacy Badge](
https://app.codacy.com/project/badge/Grade/1974469fd285468380f5223dee280949
)](
https://www.codacy.com/manual/rzr/trako?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=rzr/trako&amp;utm_campaign=Badge_Grade
)
[![Fediverse](
https://img.shields.io/mastodon/follow/279303?domain=https%3A%2F%2Fmastodon.social&style=social
)](
https://mastodon.social/@rzr/104472726388678528#Trako#
)
[![IRC Channel](
https://img.shields.io/badge/chat-on%20freenode-brightgreen.svg
)](
https://kiwiirc.com/client/irc.freenode.net/#iot
)

Trako profiler to optimize C++ projects with a single macro !

## INTRODUCTION ##

Trako aims to help profiling a C++ project in real time
without changing much of the architecture and related code to be studied...

Features :

* Class profiling :
  * count how many instances of class at a given type
  * tell how many instances where created since last query
  * ...

* Methods profiling :
  * trace methods call stack (entering or leaving)
  * measure time spend in method or scope
  * count how many times methods have been called
  * ...

* Prevent pollution of code :
  * enable or disable using a single defines and link with a lib
  * no additional code in user's files beside those a macros
  * usage of macros that can easily disabled or located removed etc
  * can be used everywhere investigation need to be focused on
    as long as you have the source code

* Integration in emacs (and probably other grep supported editors/IDE) :
  * file:line log entry format , just jump to the right place in one click

## USAGE ##

### Download ###

In your project directory or system dirs (ie: /usr/local/include/trako)

```sh
git clone --depth 1 https://github.com/rzr/trako --branch "0.2.0"
# Optionally build and run the example program, to profile execution.
make -C trako run
```

### Include Header ###

Include trako.h in your project,
let me suggest to do this a common included file (ie: config.h or private.h etc):

```c++
#define EXAMPLE_CONFIG_TRAKO 1

#if defined(EXAMPLE_CONFIG_TRAKO) && EXAMPLE_CONFIG_TRAKO
# include <trako/trako.h>
# define EXAMPLE(cmd)                           \
  TRAKO(cmd)
#else
# define EXAMPLE(cmd)                           \
  TRAKO(cmd)
#endif
```

### Modify Code ###

Use the single "TRAKO" macro with a couple of TRAKO commands

For classes:

```c++
class MyClass { TRAKO(CLASS(MyClass)); };
```

Then you can collect stats, anywhere you have to call :

```c++
TRAKO(CLASS_STATS()); //will print new instances
```

and the result will be printed to console :

```c++
src/main.cpp:73: trace: <MyClass> -1=1 =16B (<2<42 )
```

read it as :

* src/main.cpp: source where trace was invoked
* 54: line in previous file
* trace: tag to ease filtering
* MyClass : Typename of tracked class with TRAKO_CLASS keyword
* -1 : one instance was removed since last query
* =1 : number instances of it are living in ram
* = 16B  : taking 16Bytes of RAM
* (<2 : maximum different instances at a give time
* <42 ) : total of instance created

If you want to profile time spend in methods, ie:

```c++
void funct() { TRAKO(FUNCT); };
```

Or Scopes too:

```c++
void funct(bool enabled) { if (enabled) { TRAKO(SCOPE("enabled")); } };
```

Then call and time will be traced like:

```
src/main.cpp:20: scope: { method @1 [=0s 706us]
src/main.cpp:26: scope: { methodSub @2 [=0s 715us]
src/main.cpp:26: scope: } funct() @1 [+0s 3us]
```

For more have a look at the example file and it's trace :

* src/main.cpp
* main.log.txt

## KNOWN BUGS AND LIMITATIONS ##

* fell free to report discovered bugs, wishes etc by email
* supporting only g++ so far
* barely supports typename collision among different namespaces

## SUPPORT ##

Some success have been observed with following compilers:

* g++ (Debian 6.3.0-18+deb9u1) 6.3.0 20170516 @ debian:9/amd64
* g++ (Raspbian 6.3.0-18+rpi1+deb9u1) 6.3.0 20170516 @ Raspbian_9.0/armv7l
* g++ (Debian 8.3.0-6) 8.3.0 @ debian:10/x86_64
* g++ (Ubuntu 9.3.0-10ubuntu2) 9.3.0 @ Ubuntu_20.04/x86_64
* clang version 10.0.0-4ubuntu1  @ Ubuntu_20.04/x86_64

While those versions may need extra efforts (please submit tickets for no cxx11 support):

* g++ (Debian 4.9.2-10+deb8u2) 4.9.2 @ Debian:8
* g++ (Ubuntu 5.3.1-14ubuntu2) 5.3.1 20160413 @ Ubuntu_16.04/i586
* clang version 11.0.3 (clang-1103.0.32.59) @ Mac Os 10.15 : [#2](https://github.com/rzr/trako/issues/2)

Please report for others platforms:

* clang : TODO
* msvc : TODO
* others ?

## TODO ##

Other features may come later,
most of them are already in progress if not done
I plan to publish them once polished...

* Features
  * TODO [#A] assertion logs
* TODO [#B] script to ins/des/intrument source
  * TODO [#B] also track non user pointers even on closed source code
* TODO [#C] port to other compilers clang msvc etc
  * TODO [#C] script to display source along its trace
* TODO [#C] Integration with other tools, XML, gnuplot etc

* Refactoring tasks :
  * TODO [#C] use STL's functions objects

## RESOURCES ##

*   <https://purl.org/rzr/trako>
*   <https://github.com/rzr/trako/>
*   <https://mastodon.social/@rzr/104472772309868728>
*   <https://mastodon.social/@rzr/104472726388678528>
*   <https://gitorious.org/trako>
*   <https://archive.softwareheritage.org/browse/content/ed87e2ddd12353b8924bb5652b9527822d81028a/>
*   <https://notabug.org/rzr/trako>
