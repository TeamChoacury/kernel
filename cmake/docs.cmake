if(KERNEL_BUILD_DOCS)
    find_package(Doxygen)
    if(Doxygen_FOUND)
        message(STATUS "Found Doxygen version "
            "${DOXYGEN_VERSION} at ${DOXYGEN_EXECUTABLE}")

        set(KERNEL_DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
        set(KERNEL_DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

        configure_file(${KERNEL_DOXYGEN_IN} ${KERNEL_DOXYGEN_OUT} @ONLY)

        message(STATUS "Building Doxygen documentation")

        add_custom_target(flxr_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM
        )
    endif()
endif()