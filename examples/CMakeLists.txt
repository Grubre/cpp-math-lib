foreach(example_source IN ITEMS matrix.cpp vector.cpp)
    get_filename_component(example_name ${example_source} NAME_WE)

    add_executable(${example_name} ${example_source})

    target_link_libraries(${example_name} PRIVATE CppMathLib)
endforeach()


