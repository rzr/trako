# !/usr/bin/make -f
project?=trako

default: help rule/version all


# Alternatively disable trako
# TRAKO_CONFIG?=0
# Alternatively "libtrako" can be created instead of inlined template
# TRAKO_CONFIG_LIB?=1
# Disabled internaly, but enabled for clients in trako.h
TRAKO_CONFIG_WARNING?=0

export V?=1

srcs?=$(wildcard src/${project}/*.cpp | sort)
headers?=$(wildcard src/${project}/*.h | sort)
objs?=${srcs:.cpp=.o}
lib?=lib${project}.a
libs?=
main_src?=src/main.cpp
main_exe?=${main_src:.cpp=}
target?=${main_exe}
log?=${target}.log.txt.tmp

CXXFLAGS+=-std=c++11
CXXFLAGS+=-Isrc
CXXFLAGS+=-Wall -Werror -Wpedantic

install_header_dir?=${DESTDIR}/usr/include/${project}
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

ifdef TRAKO_CONFIG_WARNING
export TRAKO_CONFIG_WARNING
CXXFLAGS+=-DTRAKO_CONFIG_WARNING=${TRAKO_CONFIG_WARNING}
libs+=${lib}
endif

all: COPYING ${lib} ${target}
	ls $^

run: ${target}
	${exec} ${<D}/${<F}

%.log.txt.tmp: %
	${exec} ${<D}/${<F} | tee $@ ; echo status=$$?

log: ${log}
	cat ${log}

update: main.log.txt ${log}
	cp -av ${log}  $<
	-git diff --exit-code # || git difftool $<
	-git commit -sm 'Update trace before release' $<


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

${lib}: ${objs}
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

rule/version:
	${MAKE} --version
	${CXX} --version
	-cmake --version

rule/debian/setup: /etc/debian_version
	cat $<
	${sudo} apt-get update
	${sudo}	apt-get install -y make

setup: rule/debian/setup
#	@echo "TODO: Support other OS"

-include ~/bin/mk-local.mk

rule/src/test: src
	grep -r "config.h" . \
  | grep -v 'config.h:' \
  | grep -v 'lib.h' \
  | grep -v '.cpp:' | grep '.h:' | grep 'include' \
  && exit 1 || echo "OK"


test: distclean all run
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

check: rule/version distclean all
	${MAKE} run > ${log}
	cat ${log} | grep '^trako: init: }'
	cat ${log} | grep ' trako: FUNCT: } int main('
	cat ${log} | grep 'trako: FUNCT: }'
	cat ${log} | grep 'trako: SCOPE: }'
	cat ${log} | grep 'trako: FUNCT/STATS: '
	cat ${log} | grep 'trako: CLASS'
	cat ${log} | grep 'trako: CLASS/STATS: '
	cat ${log} | grep 'trako: CLASS/DIFF: '
	cat ${log} | grep 'trako: CLASS/TYPE: '
	cat ${log} | grep 'trako: STATS: '
	cat ${log} | grep -e 'trako: FUNCT/STATS: .*% <int main(int, char\*\*)>'
	cat ${log} | grep -v '?' | grep -e 'trako: FUNCT/STATS: .*% <int main(int, char\*\*)>'
	cat ${log} | grep 'trako: term: }'
	@echo "# log: success: $@"

devel: distclean
	make check > /dev/null || make log
	@echo "# log: Safe check"
	make check log
	@echo "# log: success: $@"

rule/test/flag/TRAKO_CONFIG: distclean
	@echo "# log: try: $@"
	${MAKE} ${@D}/boolean/0/${@F} TRAKO_CONFIG_WARNING=1 2>&1 | grep 'trako: disabled'
	${MAKE} ${@D}/boolean/1/${@F} TRAKO_CONFIG_WARNING=1 2>&1 | grep 'trako: enabled'
	${MAKE} ${@D}/boolean/1/${@F}

rule/test/flag/TRAKO_CONFIG_LIB: distclean
	@echo "# log: try: $@"
	${MAKE} ${@D}/boolean/TRAKO_CONFIG_LIB
	@echo "# log: success: $@"

rule/test/flag/TRAKO_CONFIG_WARNING: distclean
	${MAKE} ${@D}/boolean/1/${@F} \
  2>&1 | grep "warning \"trako: enabled: "
	${MAKE} ${@D}/boolean/0/${@F} \
  2>&1 | grep "warning \"trako: " \
  && exit 1 || echo "# log: success: $@"

rule/tests: distclean
	@echo "# log: try: $@"
	${MAKE} distclean test
	${MAKE} rule/test/flag/TRAKO_CONFIG
	${MAKE} rule/test/flag/TRAKO_CONFIG_LIB
	${MAKE} rule/test/flag/TRAKO_CONFIG_WARNING
	-git status
	@echo "# log: success: $@"

rule/cmake: src/CMakeLists.txt
	cd ${<D} && cmake . && cmake --build .

rule/docker: Dockerfile
	docker build -t "${project}" .
	docker run "${project}"

rule/clang: distclean
	make CXX=clang++ -k
	make CXX=clang++ -k test

rule/tools: distclean rule/tests check
	${MAKE} rule/cmake
	${MAKE} rule/docker

rule/update/%:
	git describe --tags
	sed -e "s|\(\#define TRAKO_VERSION \).*|\1\"${@F}\"|g" \
  -i src/${project}/macros.h
	sed -e "s|\(git clone .* --branch \).*|\1\"${@F}\"|g" \
  -i README.md
	dch --newversion "${@F}-0" "Release ${@F}"

rule/release/%: distclean rule/update/%
	git checkout master
	grep VERSION src/${project}/macros.h | grep ${@F}
	${MAKE} test
	${MAKE} rule/tests
	${MAKE} update
	${MAKE} rule/tools
	git commit -sam 'Release ${@F}'
	git tag -sm "${project}-${@F}" "${@F}" HEAD
	git describe --tags | grep "^${@F}$$"
	@echo "# git push --force origin --tags master # To upload release"

#eof
