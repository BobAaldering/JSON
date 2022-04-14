enable_testing()

add_executable(json_tester json_tester.cpp ../serializer/src/json_serializer.c)

list(APPEND TEST_TARGETS json_tester) # Append new tests to this list.

include(GoogleTest)

foreach(target ${TEST_TARGETS})
    target_compile_features(${target} PRIVATE cxx_std_20)
    set_target_properties(${target} PROPERTIES CXX_EXTENSIONS ON)

    target_include_directories(${target} PRIVATE ../serializer/inc)

    target_link_libraries(${target} gtest_main gmock)
    gtest_discover_tests(${target})
endforeach()
