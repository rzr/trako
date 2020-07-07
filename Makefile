# !/usr/bin/make -f
default: help all

package?=trako

# Alternatively disable trako
# TRAKO_CONFIG?=0
# Alternatively "libtrako" can be created instead of inlined template
# TRAKO_CONFIG_LIB?=1

export V?=1

srcs?=$(wildcard src/${package}/*.cpp | sort)
headers?=$(wildcard src/${package}/*.h | sort)
objs?=${srcs:.cpp=.o}
lib?=lib${package}.a
libs?=
main_src?=src/main.cpp
main_exe?=${main_src:.cpp=}
target?=${main_exe}

CXXFLAGS+=-Isrc

install_header_dir?=${DESTDIR}/usr/include/${package}
install_lib_dir?=${DESTDIR}/usr/lib/

sudo?=$(shell which sudo 2> /dev/null || echo)

ifdef TRAKO_CONFIG
export TRAKO_CONFIG
CXXFLAGS+=-DTRAKO_CONFIG=${TRAKO_CONFIG}
endif
ifdef TRAKO_CONFIG_LIB
export TRAKO_CONFIG_LIB
CXXFLAGS+=-DCONFIG_TRAKO_LIB=${TRAKO_CONFIG_LIB}
libs+=${lib}
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


clean: force
	find . -type f -iname "*.o" -exec rm -f '{}' \;
	find . -type f -iname "*~" -exec rm -f '{}' \;


cleanall: clean
	rm -f ${target} *.a
	-rm -rf */CMakeCache.txt */CMakeFiles */*.cmake
	-rm -rf ./CMakeCache.txt ./CMakeFiles ./*.cmake
	-rm -rf */*.a */main */tmp main tmp MANIFEST src/Makefile

distclean: cleanall
	${MAKE} cleanall

force:

help:
	@echo "# srcs=${srcs}"
	@echo "# CXXFLAGS=${CXXFLAGS}"

lib${package}.a: ${objs}
	${AR} cru $@ $^
#	nm --demangle $@


${target}: ${main_src:.cpp=.o} ${libs}
	${CXX} ${CXXFLAGS} -o $@ $^

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


test: distclean all run
	${MAKE} distclean
	@echo "# log: success: $@"

rule/test/flag/boolean/0/%:
	@echo "# log: try: $@"
	${MAKE} test ${@F}=0
	@echo "# log: success: $@"

rule/test/flag/boolean/1/%:
	@echo "# log: try: $@"
	${MAKE} test ${@F}=1
	@echo "# log: success: $@"

rule/test/flag/boolean/%:
	@echo "# log: try: $@"
	${MAKE} ${@D}/0/${@F}
	${MAKE} ${@D}/1/${@F}
	@echo "# log: success: $@"

rule/test/flag/TRAKO_CONFIG: distclean
	@echo "# log: try: $@"
	${MAKE} ${@D}/boolean/0/${@F} 2>&1 | grep 'trako: disabled'
	${MAKE} ${@D}/boolean/1/${@F} 2>&1 | grep 'trako: enabled'
	${MAKE} ${@D}/boolean/1/${@F} 2>&1 \
  | grep '^# Quitting$$'
	${MAKE} ${@D}/boolean/1/${@F} 2>&1 \
| grep 'src/main.cpp' | grep ': } int main(' \
  || echo "TODO: may static objects destruction investigated"
	@echo "# log: success: $@"

rule/test/flag/TRAKO_CONFIG_LIB: distclean
	@echo "# log: try: $@"
	${MAKE} ${@D}/boolean/TRAKO_CONFIG_LIB
	@echo "# log: success: $@"

tests: distclean
	@echo "# log: try: $@"
	${MAKE} rule/test/flag/TRAKO_CONFIG
	${MAKE} rule/test/flag/TRAKO_CONFIG_LIB
	-git status
	@echo "# log: success: $@"
#eof
