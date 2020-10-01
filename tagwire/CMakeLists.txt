
#reflang_harness(fields_harness "MyClass")

#include_directories(
#  ${CMAKE_CURRENT_SOURCE_DIR}
#  "generated")

add_executable(tagwire_harness 
  tagwire_harness_main.cpp
  TagwireDecoder.cpp
  TagwireEncoder.cpp
  EmapiTagwireWrapper.cpp
  emapi.cpp
 )
 add_executable(thailand_client 
  thailand_client.cpp
  TagwireDecoder.cpp
  TagwireEncoder.cpp
  EmapiTagwireWrapper.cpp
  emapi.cpp
 )

add_executable(thailand_sim 
  thailand_sim.cpp
  TagwireDecoder.cpp
  TagwireEncoder.cpp
  EmapiTagwireWrapper.cpp
  emapi.cpp
 )

