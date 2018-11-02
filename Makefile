MAKE_FLAGS?=-j5


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

PPA_TARGET?=trusty


#----------------------------------------------
# Cleaning
#----------------------------------------------

clean:
	rm -Rf build;
	git submodule update --init doc/dox/; cd doc/dox/; git clean -f; git reset --hard


#----------------------------------------------
# Generic targets
#----------------------------------------------

BUILD_SUBDIR=${BUILD_DIR}/${TC}-${TYPE}-OPTIONS_${OPTIONS}

build:
	mkdir -p ${BUILD_SUBDIR};
	cd ${BUILD_SUBDIR}; cmake 	-C ${ROOT_DIR}/tests/cmake_configs/options_${OPTIONS}.cmake\
								-DCMAKE_BUILD_TYPE=${TYPE} \
								-DCMAKE_TOOLCHAIN_FILE=${CMAKE_DIR}/toolchain_${TC}.cmake\
								${EXTRA_CMAKE_PARAM} \
								${ROOT_DIR};
	cd ${BUILD_SUBDIR}; ${MAKE} ${MAKE_FLAGS} ${TARGETS}

build-tests: build
	cd ${BUILD_SUBDIR}; ctest ${ARGS}
#	cd ${BUILD_SUBDIR}; ${MAKE} ${MAKE_FLAGS} test ${ARGS}

# -------

FETCH_DIR=${BUILD_DIR}/fetch

fetch:
	mkdir -p ${FETCH_DIR};
	cd ${FETCH_DIR}; cmake ${ROOT_DIR};
	cd ${FETCH_DIR}; ${MAKE} fetch-bridges;


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
# checks
#----------------------------------------------

ppa: clean
	${MAKE} build TC=${TC} TYPE=Release OPTIONS=deb_packages_${PPA_TARGET} TARGETS="ppa" \
		EXTRA_CMAKE_PARAM="${EXTRA_CMAKE_PARAM} -DPPA_BUILDPACKAGE_FLAGS='-d'"

ppa-upload:
	cd build/generic-Release-OPTIONS_deb_packages_trusty/Debian/trusty/ariles-*-source; \
		ftp -au ppa.launchpad.net:~asherikov/ubuntu/ppa/ \
			ariles_*~${PPA_TARGET}.dsc \
			ariles_*~${PPA_TARGET}.tar.xz \
			ariles_*~${PPA_TARGET}_source.buildinfo \
			ariles_*~${PPA_TARGET}_source.changes

test-ppa: clean
	${MAKE} build TC=${TC} TYPE=Release OPTIONS=deb_packages_${PPA_TARGET} TARGETS="ppa" \
		EXTRA_CMAKE_PARAM="${EXTRA_CMAKE_PARAM} -DPPA_BUILDPACKAGE_FLAGS='-us;-uc'"
	cd build/generic-Release-OPTIONS_deb_packages_${PPA_TARGET}/Debian/${PPA_TARGET}/ariles-*-source; \
		dpkg-buildpackage -us -uc -F


test-ros: clean
	${MAKE} build-tests TC=${TC} TYPE=Debug OPTIONS=default TARGETS="${TARGETS}" EXTRA_CMAKE_PARAM="${EXTRA_CMAKE_PARAM}"
	${MAKE} build-tests TC=${TC} TYPE=Debug OPTIONS=ros TARGETS="${TARGETS}" EXTRA_CMAKE_PARAM="${EXTRA_CMAKE_PARAM}"


test-noros: clean
	${MAKE} build TC=${TC} TYPE=Debug OPTIONS=no_core TARGETS="${TARGETS}" EXTRA_CMAKE_PARAM="${EXTRA_CMAKE_PARAM}"
	${MAKE} build-tests TC=${TC} TYPE=Debug OPTIONS=cpp11_on_noros TARGETS="${TARGETS}" EXTRA_CMAKE_PARAM="${EXTRA_CMAKE_PARAM}"
	${MAKE} build-tests TC=${TC} TYPE=Debug OPTIONS=cpp11_on_noros_sloppy TARGETS="${TARGETS}" EXTRA_CMAKE_PARAM="${EXTRA_CMAKE_PARAM}"
	${MAKE} build-tests TC=${TC} TYPE=Debug OPTIONS=cpp03_on_noros TARGETS="${TARGETS}" EXTRA_CMAKE_PARAM="${EXTRA_CMAKE_PARAM}"
	${MAKE} build-tests TC=${TC} TYPE=Debug OPTIONS=cpp11_build_noros TARGETS="${TARGETS}" EXTRA_CMAKE_PARAM="${EXTRA_CMAKE_PARAM}"
	${MAKE} build-tests TC=${TC} TYPE=Debug OPTIONS=cpp03_build_noros TARGETS="${TARGETS}" EXTRA_CMAKE_PARAM="${EXTRA_CMAKE_PARAM}"

test-cmake:
	${MAKE} build-tests TC=${TC} TYPE=Debug OPTIONS=conflict TARGETS="${TARGETS}" EXTRA_CMAKE_PARAM="${EXTRA_CMAKE_PARAM}"

#----------------------------------------------
# other
#----------------------------------------------

update:
	git submodule update

dox:
	cd doc; doxygen

install-ros:
	sh -c "echo \"deb http://packages.ros.org/ros/ubuntu ${UBUNTU_DISTRO} main\" > /etc/apt/sources.list.d/ros-latest.list"
	apt-key adv --keyserver hkp://ha.pool.sks-keyservers.net:80 --recv-key 421C365BD9FF1F717815A3895523BAEEB01FA116
	apt-get update -qq
	apt-get install dpkg
	apt-get install -y ros-${ROS_DISTRO}-ros-base
	bash -c 'source /opt/ros/${ROS_DISTRO}/setup.bash; rosdep init'

.PHONY: clean cmake build
