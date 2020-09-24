
#reflang_harness(fields_harness "MyClass")

set(CMAKE_VERBOSE_MAKEFILE ON)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/../../tagwire
  "generated")

add_executable(fields_harness 
  fields_harness.main.cpp
  generated/fields_harness.gen.cpp
  )

#add_executable(emapi_harness 
# emapi_harness.main.cpp
#  generated/emapi.gen.cpp
#)


target_link_libraries(fields_harness libreflang)

##add_library(yaml-cpp STATIC IMPORTED)
##set_target_properties(yaml-cpp PROPERTIES
##	IMPORTED_LOCATION /home/root/git/devutils/third_party/yaml-cpp/build/libyaml-cpp.a)
#
#add_executable(yaml_harness
#  yaml_main.cpp
#  )
##target_link_libraries(yaml_harness /home/root/git/devutils/yaml-cpp/build/yaml-cppd.a)
#target_link_libraries(yaml_harness yaml-cppd)


