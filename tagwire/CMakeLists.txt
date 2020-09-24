
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
  
