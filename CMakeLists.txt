cmake_minimum_required(VERSION 3.1)

project(dblp CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Release)

set(EXTERNAL_INSTALL_DIR ${CMAKE_BINARY_DIR}/external)
link_directories(${EXTERNAL_INSTALL_DIR}/lib)
include_directories(${EXTERNAL_INSTALL_DIR}/include)

add_executable(dblp-extractor extract_and_convert_to_json.cpp)
target_link_libraries(dblp-extractor json11 tinyxml2)

#include(ExternalProject)
#ExternalProject_Add(
#	json11
#	GIT_REPOSITORY ${CMAKE_SOURCE_DIR}/external/json11
#	GIT_TAG ec4e45219af1d7cde3d58b49ed762376fccf1ace
#	INSTALL_DIR ${EXTERNAL_INSTALL_DIR}
#	CMAKE_ARGS 
##	-DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
#	-DJSON11_BUILD_TESTS=OFF
#	-DJSON11_ENABLE_DR1467_CANARY=OFF
#)
#ExternalProject_Add(
#	tinyxml2
#	GIT_REPOSITORY ${CMAKE_SOURCE_DIR}/external/tinyxml2
#	GIT_TAG c483646db00a6a9ac3a8e93f7c490aecb589979d
#	INSTALL_DIR ${EXTERNAL_INSTALL_DIR}
#	CMAKE_ARGS
##	-DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
#	-DBUILD_SHARED_LIBS=OFF
#	-DBUILD_TESTING=OFF
#	-DBUILD_TESTS=OFF
#)
# add_dependencies(dblp-extractor json11 tinyxml2)

install(TARGETS dblp-extractor DESTINATION bin)

