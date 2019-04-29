include_directories(
    ${PROJECT_SOURCE_DIR}/catch
    include
)

set(SLS_TEST_SOURCES 
    test_main.cpp
    test_1bit.cpp
)

add_executable(t ${SLS_TEST_SOURCES})
target_link_libraries(t 
    project_options
    project_warnings
    utils
)  
set_target_properties(t PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    )

# configure_file(data/single.bin ${CMAKE_BINARY_DIR}/data/single.bin)
configure_file(data/single.bin ${CMAKE_BINARY_DIR}/data/single.bin COPYONLY)
# include(CTest)
# include(Catch)
# catch_discover_tests(tests)
