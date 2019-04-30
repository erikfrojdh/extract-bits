include_directories(
    ${PROJECT_SOURCE_DIR}/catch
    include
)

set(SLS_TEST_SOURCES 
    test_main.cpp
    test_1bit.cpp
)

add_executable(tests ${SLS_TEST_SOURCES})
target_link_libraries(tests 
    project_options
    project_warnings
    utils
)  
set_target_properties(tests PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    )

#Copy data from source tree to build folder for running tests
configure_file(data/single.bin ${CMAKE_BINARY_DIR}/data/single.bin COPYONLY)

include(CTest)
include(Catch)
catch_discover_tests(tests)
