# !/usr/bin/make -f
default: all

package?=trako

CONFIG_WANT_LIBTRAKO?=1
export CONFIG_WANT_LIBTRAKO
# Alternatively "libtrako" can be inlined with trako.cxx instead of lib
CONFIG_TRAKO_WANT_INLINE?=0
export CONFIG_TRAKO_WANT_INLINE
export V?=1

srcs?=$(wildcard src/${package}/*.cpp | sort)
headers?=$(wildcard src/${package}/*.h | sort)
objs?=${srcs:.cpp=.o}
lib?=lib${package}.a
main_src?=src/main.cpp
main_exe?=${main_src:.cpp=}
target?=${main_exe}

CXXFLAGS+=-Isrc/${package}  -Isrc
CXXFLAGS+=-DCONFIG_WANT_LIBTRAKO=0${CONFIG_WANT_LIBTRAKO}

install_header_dir?=${DESTDIR}/usr/include/${package}
install_lib_dir?=${DESTDIR}/usr/lib/

sudo?=$(shell which sudo 2> /dev/null || echo)

ifeq (1, ${CONFIG_TRAKO_WANT_INLINE})
CXXFLAGS+=-DCONFIG_TRAKO_WANT_INLINE=${CONFIG_TRAKO_WANT_INLINE}
endif


all: COPYING ${lib} ${target}
	ls $^

run: ${target}
	${exec} ${<D}/${<F}

%.log.txt.tmp: %
	${exec} ${<D}/${<F} | tee $@ ; echo status=$$?

update: main.log.txt ${target}.log.txt.tmp
	cp -av ${target}.log.txt.tmp  $<
	-git diff --exit-code || git difftool $<


clean:force
	find . -type f -iname "*.o" -exec rm -f '{}' \;
	find . -type f -iname "*~" -exec rm -f '{}' \;


distclean: clean
	rm -f ${target} *.a
	-rm -rf */CMakeCache.txt */CMakeFiles */*.cmake
	-rm -rf ./CMakeCache.txt ./CMakeFiles ./*.cmake
	-rm -rf */*.a */main */tmp main tmp MANIFEST src/Makefile


test: distclean run clean

force:

help:
	echo "# srcs=${srcs}"


lib${package}.a: ${objs}
	${AR} cru $@ $^
#	nm --demangle $@


ifeq (1, ${CONFIG_TRAKO_WANT_INLINE})
${target}: ${main_src:.cpp=.o}
	${CXX} ${CXXFLAGS} -o $@ $^
else
${target}: ${main_src:.cpp=.o} ${lib}
	${CXX} ${CXXFLAGS} -o $@ $^
endif

install: ${headers}
	install -d ${install_header_dir}
	for f in ${^F}; do install ${<D}/$${f} ${install_header_dir}/$${f} ; done
	install -d ${install_lib_dir}
	install ${lib} ${install_lib_dir}/


cmake:src/CMakeLists.txt distclean
	cd ${<D} && cmake .
	make -C ${<D} V=1 VERBOSE=1


COPYING:/usr/share/common-licenses/LGPL-3
	cp $< $@

/etc/debian_version:
	test -e $@ || echo "TODO: port to other OS"
	cat $@

rule/debian/setup: /etc/debian_version
	cat $<
	${sudo} apt-get update
	${sudo}	apt-get install -y make

-include ~/bin/mk-local.mk

rule/src/test: src
	grep -r "config.h" . \
  | grep -v 'config.h:' \
  | grep -v 'lib.h' \
  | grep -v '.cpp:' | grep '.h:' | grep 'include' \
  && exit 1 || echo "OK"

rule/test/want/%:
	make CONFIG_WANT_LIBTRAKO=${@F} distclean
	make CONFIG_WANT_LIBTRAKO=${@F} run
	make CONFIG_WANT_LIBTRAKO=${@F} distclean

rule/test/inline/%:
	make rule/test/want/1 CONFIG_TRAKO_WANT_INLINE=${@F}

rule/test/inline:
	make rule/test/inline/0
	make rule/test/inline/1

test: distclean rule/src/test
	make rule/test/want/1
	make rule/test/want/1 | grep 'trako: '
	make rule/test/want/0
	make rule/test/want/0 | grep 'trako: ' && exit 1 || echo "ignored"
	make rule/test/inline/0
	make rule/test/inline/1
	-git status

#eof
