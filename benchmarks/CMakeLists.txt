add_executable(bench bm.cpp)
target_link_libraries(bench PRIVATE 
    project_options 
    project_warnings 
    Threads::Threads 
    utils 
    benchmark)

set_target_properties(bench PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)