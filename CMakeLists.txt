cmake_minimum_required (VERSION 2.8.7)
project (devutils)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(third_party/reflang/lib/)
include_directories(third_party/reflang)
include_directories(third_party/yaml-cpp/include)

#link_directories(/home/root/git/devutils/third_party/yaml-cpp/build)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -v -std=c++17 -stdlib=libc++")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	set(LLVM_CONFIG true)
	set(CLANG_INCLUDEDIR "C:/Program Files (x86)/LLVM/include")
	set(CLANG_LIBDIR "C:/Program Files (x86)/LLVM/lib")
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_library(libreflang STATIC third_party/reflang/lib/reflang.hpp third_party/reflang/lib/reflang.cpp)
#add_library(yaml-cppd STATIC IMPORTED)
#set_target_properties(yaml-cppd PROPERTIES
#	IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/third_party/yaml-cpp/build/libyaml-cppd.a)

#add_subdirectory(third_party)
add_subdirectory(harness)

add_subdirectory(tagwire)

