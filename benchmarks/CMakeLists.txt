add_executable(bench bm.cpp)
target_link_libraries(bench PRIVATE 
    project_options 
    project_warnings 
    Threads::Threads 
    utils 
    benchmark)

    check_ipo_supported(RESULT result)
    if(result)
        set_property(TARGET bench PROPERTY INTERPROCEDURAL_OPTIMIZATION True)
    endif()

set_target_properties(bench PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)