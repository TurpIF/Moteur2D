# List of all tests
set(MOTEUR2D_TESTS
    ""
    )

# Add all defined tests
foreach(e ${MOTEUR2D_TESTS})
    if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${e}")
        message(FATAL_ERROR "Cannot add test ${e}, no directory with that name lies in ${CMAKE_CURRENT_SOURCE_DIR}")
    else()
        set(e_exe_name "MOTEUR2D_${e}")
        file(GLOB_RECURSE e_sources "${CMAKE_CURRENT_SOURCE_DIR}/${e}/*.cpp")
        add_executable(${e_exe_name} ${e_sources})
        target_link_libraries(${e_exe_name} ${MOTEUR2D_LIB})
    endif()
endforeach()
