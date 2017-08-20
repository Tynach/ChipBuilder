set(layer_test_src layer_test.cpp)
add_executable(layer_test ${layer_test_src})

target_link_libraries(layer_test layers)