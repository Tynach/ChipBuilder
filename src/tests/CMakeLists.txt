set(layer_test_src layer_test.cpp)
add_executable(layer_test ${layer_test_src})
target_link_libraries(layer_test layers)

set(array_test_src array_test.cpp)
add_executable(array_test ${array_test_src})