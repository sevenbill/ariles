MAKE_FLAGS?=-j7


CMAKE_DIR=./cmake/
BUILD_DIR=./build/
ROOT_DIR=../../


# Toolchains
TC?=generic

OPTIONS?=default

# Build type as in CMAKE_BUILD_TYPE
TYPE?=Debug

TARGETS?=all

ARGS?=

DEB_TARGET?=xenial

TEST_ENV=UBSAN_OPTIONS=print_stacktrace=1:halt_on_error=1:suppressions=../../../cmake/sanitizer_undefined.supp \
		 ASAN_OPTIONS=suppressions=../../../cmake/sanitizer_address.supp \
		 LSAN_OPTIONS=suppressions=../../../cmake/sanitizer_leak.supp \


#----------------------------------------------
# Cleaning
#----------------------------------------------

clean:
	rm -Rf build;
	rm -Rf include/ariles/internal/cpput_*.h
	#git submodule update --init doc/dox/; cd doc/dox/; git clean -f; git reset --hard


#----------------------------------------------
# Generic targets
#----------------------------------------------

BUILD_SUBDIR=${BUILD_DIR}/${TC}-${TYPE}-OPTIONS_${OPTIONS}

build:
	mkdir -p ${BUILD_SUBDIR};
	cd ${BUILD_SUBDIR}; cmake 	-C ${ROOT_DIR}/tests/cmake/configs/options_${OPTIONS}.cmake\
								-DCMAKE_BUILD_TYPE=${TYPE} \
								-DCMAKE_TOOLCHAIN_FILE=${CMAKE_DIR}/toolchain_${TC}.cmake\
								${EXTRA_CMAKE_PARAM} \
								${ROOT_DIR};
	cd ${BUILD_SUBDIR}; ${MAKE} ${MAKE_FLAGS} ${TARGETS}

build-tests: build
	cd ${BUILD_SUBDIR}; env ${TEST_ENV} ctest ${ARGS}
#	cd ${BUILD_SUBDIR}; ${MAKE} ${MAKE_FLAGS} test ${ARGS}

# -------

#----------------------------------------------
# debug mode (all)
# Build & test
#----------------------------------------------

debug-all:
	${MAKE} build TC=${TC} TYPE=Debug TARGETS="${TARGETS}"

debug-all-tests:
	${MAKE} build-tests TC=${TC} TYPE=Debug TARGETS="${TARGETS}"

all: debug-all

debug: debug-all


#----------------------------------------------
# release mode
# Build & test
#----------------------------------------------

release-all:
	${MAKE} build TC=${TC} TYPE=Release TARGETS="${TARGETS}"

release-all-tests: release-all
	${MAKE} build-tests TC=${TC} TYPE=Release TARGETS="${TARGETS}"

release: release-all


#----------------------------------------------
# Debian packages
#----------------------------------------------

deb: clean
	${MAKE} build TC=${TC} TYPE=Release OPTIONS=deb_packages_${DEB_TARGET} TARGETS="pkg_deb" \
		EXTRA_CMAKE_PARAM="${EXTRA_CMAKE_PARAM} -DDEB_BUILDPACKAGE_FLAGS='-d'"

deb-build: clean
	${MAKE} build TC=${TC} TYPE=Release OPTIONS=deb_packages_${DEB_TARGET} TARGETS="pkg_deb" \
		EXTRA_CMAKE_PARAM="${EXTRA_CMAKE_PARAM} -DDEB_BUILDPACKAGE_FLAGS='-us;-uc'"
	cd build/generic-Release-OPTIONS_deb_packages_${DEB_TARGET}/Debian/${DEB_TARGET}/ariles-*-source; \
		dpkg-buildpackage -us -uc -F

deb-install:
	sudo dpkg -i build/generic-Release-OPTIONS_deb_packages_${DEB_TARGET}/Debian/${DEB_TARGET}/ariles-*.deb

deb-uninstall:
	dpkg --get-selections ariles* | awk '{print $1}' | xargs sudo dpkg -P

cmake_dependency: clean
	mkdir -p build/cmake_dependency_test
	cd build/cmake_dependency_test; cmake ../../tests/cmake/dependency/ -DARILES_COMPONENTS="core;ros;yaml-cpp;octave"
	cd build/cmake_dependency_test; ${MAKE} ${MAKE_FLAGS}

ppa-upload:
	cd build/generic-Release-OPTIONS_deb_packages_trusty/Debian/trusty/; \
		ftp -au ppa.launchpad.net:~asherikov/ubuntu/ppa/ \
			ariles_*~${DEB_TARGET}.dsc \
			ariles_*~${DEB_TARGET}.tar.xz \
			ariles_*~${DEB_TARGET}_source.buildinfo \
			ariles_*~${DEB_TARGET}_source.changes


#----------------------------------------------
# checks
#----------------------------------------------


test-ros: clean
	${MAKE} build-tests TC=${TC} TYPE=Debug OPTIONS=default TARGETS="${TARGETS}" EXTRA_CMAKE_PARAM="${EXTRA_CMAKE_PARAM}"
	${MAKE} build-tests TC=${TC} TYPE=Debug OPTIONS=ros TARGETS="${TARGETS}" EXTRA_CMAKE_PARAM="${EXTRA_CMAKE_PARAM}"


test-noros: clean
	${MAKE} build TC=${TC} TYPE=Debug OPTIONS=no_core TARGETS="${TARGETS}" EXTRA_CMAKE_PARAM="${EXTRA_CMAKE_PARAM}"
	${MAKE} build-tests TC=${TC} TYPE=Debug OPTIONS=cpp11_on_noros TARGETS="${TARGETS}" EXTRA_CMAKE_PARAM="${EXTRA_CMAKE_PARAM}"
	${MAKE} build-tests TC=${TC} TYPE=Debug OPTIONS=cpp11_on_noros_sloppy TARGETS="${TARGETS}" EXTRA_CMAKE_PARAM="${EXTRA_CMAKE_PARAM}"
	${MAKE} build-tests TC=${TC} TYPE=Debug OPTIONS=cpp03_on_noros TARGETS="${TARGETS}" EXTRA_CMAKE_PARAM="${EXTRA_CMAKE_PARAM}"

test-cmake:
	/bin/sh -c "! ${MAKE} build-tests TC=${TC} TYPE=Debug OPTIONS=conflict TARGETS='${TARGETS}' EXTRA_CMAKE_PARAM='${EXTRA_CMAKE_PARAM}'"

#----------------------------------------------
# other
#----------------------------------------------

addutils:
	git remote add cmakeut https://github.com/asherikov/cmakeut
	git remote add cpput https://github.com/asherikov/cpput

updateutils:
	git fetch --all
	git show remotes/cmakeut/master:cmake/FindEigen3.cmake > cmake/FindEigen3.cmake
	git show remotes/cmakeut/master:cmake/cmakeut_compiler_flags.cmake              > cmake/cmakeut_compiler_flags.cmake
	git show remotes/cmakeut/master:cmake/cmakeut_copy_dir_if_exists.cmake          > cmake/cmakeut_copy_dir_if_exists.cmake
	git show remotes/cmakeut/master:cmake/cmakeut_copy_file_if_exists.cmake         > cmake/cmakeut_copy_file_if_exists.cmake
	git show remotes/cmakeut/master:cmake/cmakeut_detect_func_macro.cmake           > cmake/cmakeut_detect_func_macro.cmake
	git show remotes/cmakeut/master:cmake/cmakeut_dump_variables.cmake              > cmake/cmakeut_dump_variables.cmake
	git show remotes/cmakeut/master:cmake/cmakeut_list_filenames.cmake              > cmake/cmakeut_list_filenames.cmake
	git rm --ignore-unmatch -rf cpput
	git read-tree --prefix=cpput -u cpput/master


update:
	git submodule update


doxclean:
	cd doc/dox; git fetch --all; git checkout gh-pages; git pull
	rm -Rf ./doc/dox/1

dox: doxclean clean
	cd doc; doxygen


install-ros:
	sh -c "echo \"deb http://packages.ros.org/ros/ubuntu ${UBUNTU_DISTRO} main\" > /etc/apt/sources.list.d/ros-latest.list"
	sh -c "apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654 \
	    || apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654 \
	    || apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654"
	sh -c "apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key 6B05F25D762E3157 \
	    || apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key 6B05F25D762E3157 \
	    || apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key 6B05F25D762E3157"
	apt update -qq
	apt install dpkg
	apt install -y ros-${ROS_DISTRO}-ros-base
	apt install python-rosdep python-rosinstall python-rosinstall-generator python-wstool build-essential
	bash -c 'source /opt/ros/${ROS_DISTRO}/setup.bash; rosdep init'

install-jsonnet:
	git clone https://github.com/asherikov/jsonnet.git
	cd jsonnet; git checkout as_cmake_fix
	mkdir ./jsonnet/build
	cd ./jsonnet/build/; cmake -DBUILD_JSONNET=OFF -DBUILD_TESTS=OFF -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ ..
	cd ./jsonnet/build/; make install

format:
	find ./extra_visitors/ extra_adapters/ tests/ include/ -iname "*.h" -or -iname "*.cpp" | grep -v "better_enum.h" | xargs clang-format80 -verbose -i

cppcheck:
	# --inconclusive
	cppcheck \
		./ \
		--relative-paths \
		--quiet --verbose --force \
		--template='[{file}:{line}]  {severity}  {id}  {message}' \
		--language=c++ --std=c++03 \
	 	--enable=warning \
		--enable=style \
		--enable=performance \
		--enable=portability \
		--suppress=uninitMemberVar \
		--suppress=syntaxError \
		--suppress=useInitializationList \
		--suppress=functionStatic \
		--suppress=redundantAssignment:tests/api_v1/types/any.h \
		--suppress=unreadVariable:tests/api_v1/regression_test_019.cpp \
		--suppress=noExplicitConstructor:tests/api_v2/types/types.h \
		--suppress=constParameter:tests/api_v2/types/types.h \
		--suppress=redundantAssignment:tests/api_v2/types/any.h \
		-i ./build \
	3>&1 1>&2 2>&3 | tee cppcheck.err
	test 0 -eq `cat cppcheck.err | wc -l && rm cppcheck.err`

#
# make clangcheck SCANBUILD=scan-build-9 OPTIONS=ros
# make clangcheck SCANBUILD=scan-build80 OPTIONS=cpp11_on_noros
#
clangcheck:
	${SCANBUILD} \
		-o build/scanbuild_results \
		--status-bugs \
		--exclude ./build \
		--exclude /usr/include/ \
		--exclude /usr/local/include/ \
		--exclude /usr/src/ \
		--exclude /opt/ros/ \
		-enable-checker core.CallAndMessage \
		-enable-checker core.DivideZero \
		-enable-checker core.DynamicTypePropagation \
		-enable-checker core.NonNullParamChecker \
		-enable-checker core.NullDereference \
		-enable-checker core.StackAddressEscape \
		-enable-checker core.UndefinedBinaryOperatorResult \
		-enable-checker core.VLASize \
		-enable-checker core.uninitialized.ArraySubscript \
		-enable-checker core.uninitialized.Assign \
		-enable-checker core.uninitialized.Branch \
		-enable-checker core.uninitialized.CapturedBlockVariable \
		-enable-checker core.uninitialized.UndefReturn \
		-enable-checker cplusplus.InnerPointer \
		-enable-checker cplusplus.Move \
		-enable-checker cplusplus.NewDelete \
		-enable-checker cplusplus.NewDeleteLeaks \
		-enable-checker deadcode.DeadStores \
		-enable-checker nullability.NullPassedToNonnull \
		-enable-checker nullability.NullReturnedFromNonnull \
		-enable-checker nullability.NullableDereferenced \
		-enable-checker nullability.NullablePassedToNonnull \
		-enable-checker nullability.NullableReturnedFromNonnull \
		-enable-checker optin.cplusplus.UninitializedObject \
		-enable-checker optin.mpi.MPI-Checker \
		-enable-checker optin.performance.GCDAntipattern \
		-enable-checker optin.performance.Padding \
		-enable-checker optin.portability.UnixAPI \
		-enable-checker security.FloatLoopCounter \
		-enable-checker security.insecureAPI.DeprecatedOrUnsafeBufferHandling \
		-enable-checker security.insecureAPI.UncheckedReturn \
		-enable-checker security.insecureAPI.getpw \
		-enable-checker security.insecureAPI.gets \
		-enable-checker security.insecureAPI.mkstemp \
		-enable-checker security.insecureAPI.mktemp \
		-enable-checker security.insecureAPI.vfork \
		-enable-checker unix.API \
		-enable-checker unix.Malloc \
		-enable-checker unix.MallocSizeof \
		-enable-checker unix.MismatchedDeallocator \
		-enable-checker unix.Vfork \
		-enable-checker unix.cstring.BadSizeArg \
		-enable-checker unix.cstring.NullArg \
		-enable-checker valist.CopyToSelf \
		-enable-checker valist.Uninitialized \
		-enable-checker valist.Unterminated \
		${MAKE} build build TC=${TC} TYPE=${TYPE} OPTIONS=${OPTIONS} TARGETS="${TARGETS}" EXTRA_CMAKE_PARAM="${EXTRA_CMAKE_PARAM}"

travis-apt-clean:
	sudo rm \
		/etc/apt/sources.list.d/cassandra.list \
		/etc/apt/sources.list.d/cassandra.list.save \
		/etc/apt/sources.list.d/heroku-toolbelt.list \
		/etc/apt/sources.list.d/heroku-toolbelt.list.save \
		/etc/apt/sources.list.d/chris-lea-redis-server.list \
		/etc/apt/sources.list.d/chris-lea-redis-server.list.save \
		/etc/apt/sources.list.d/mongodb-3.4.list \
		/etc/apt/sources.list.d/mongodb-3.4.list.save \
		/etc/apt/sources.list.d/computology_apt-backport.list \
		/etc/apt/sources.list.d/computology_apt-backport.list.save \
		/etc/apt/sources.list.d/openjdk-r-java-ppa.list \
		/etc/apt/sources.list.d/openjdk-r-java-ppa.list.save \
		/etc/apt/sources.list.d/couchdb.list \
		/etc/apt/sources.list.d/couchdb.list.save \
		/etc/apt/sources.list.d/pgdg.list \
		/etc/apt/sources.list.d/pgdg.list.save \
		/etc/apt/sources.list.d/pollinate.list \
		/etc/apt/sources.list.d/pollinate.list.save \
		/etc/apt/sources.list.d/github_git-lfs.list \
		/etc/apt/sources.list.d/github_git-lfs.list.save \
		/etc/apt/sources.list.d/rabbitmq_rabbitmq-server.list \
		/etc/apt/sources.list.d/rabbitmq_rabbitmq-server.list.save \
		/etc/apt/sources.list.d/git-ppa.list \
		/etc/apt/sources.list.d/git-ppa.list.save \
		/etc/apt/sources.list.d/webupd8team-java-ppa.list \
		/etc/apt/sources.list.d/webupd8team-java-ppa.list.save \
		/etc/apt/sources.list.d/google-chrome.list \
		/etc/apt/sources.list.d/google-chrome.list.save

.PHONY: clean cmake build
