
#reflang_harness(fields_harness "MyClass")

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  "generated")

add_executable(fields_harness 
  fields_harness.main.cpp
  generated/fields_harness.gen.cpp
  )

target_link_libraries(fields_harness libreflang)
  
