cmake_minimum_required(VERSION 3.9)

# -------------------------------------------------------------------------------
# Project definition
# -------------------------------------------------------------------------------
project(IntelIPP
  VERSION 8.2.1
  DESCRIPTION "Intel IPP library"
  LANGUAGES C
)

message(STATUS "########################################################################")
message(STATUS "${PROJECT_NAME} - configuring...")
message(STATUS "------------------------------------------------------------------------")

add_library(${PROJECT_NAME} INTERFACE)

# We also add an alias definition so that we shadown
# the export namespace when using add_subdirectory() instead.
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

if (WIN32)
    list( APPEND _LIBRARIES
        ippcoremt
        ippsmt
        ippscmt
        svml_disp
        libirc
    )

    foreach(_LIBRARY_NAME ${_LIBRARIES})
        add_library(${_LIBRARY_NAME} STATIC IMPORTED)
        set_target_properties(${_LIBRARY_NAME}
            PROPERTIES
                # IMPORTED_CONFIGURATIONS "Debug;Release"
                # IMPORTED_LOCATION_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/lib/${_LIBRARY_NAME}.lib"
                # IMPORTED_LOCATION_DEBUG   "${CMAKE_CURRENT_SOURCE_DIR}/lib/${_LIBRARY_NAME}.lib"
                IMPORTED_LOCATION   "${CMAKE_CURRENT_SOURCE_DIR}/lib/${_LIBRARY_NAME}.lib"
        )

        target_link_libraries(${PROJECT_NAME}
            INTERFACE ${_LIBRARY_NAME}
        )
    endforeach()
else()
    list( APPEND _LIBRARIES
        ippsc
        ipps
        ippcore
    )

    foreach(_LIBRARY_NAME ${_LIBRARIES})
        add_library(${_LIBRARY_NAME} STATIC IMPORTED)
        set_target_properties(${_LIBRARY_NAME}
            PROPERTIES
                IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/lib/lib${_LIBRARY_NAME}.a"
        )

        target_link_libraries(${PROJECT_NAME}
            INTERFACE ${_LIBRARY_NAME}
        )
    endforeach()

endif()

target_include_directories( ${PROJECT_NAME} 
     INTERFACE
        # where top-level project will look for the library's public headers
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        # where external projects will look for the library's public headers
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_directories( ${PROJECT_NAME} 
     INTERFACE
        # where top-level project will look for the library's binary files
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib>
        # where external projects will look for the library's binary files
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_LIBDIR}>
)

# ----------------------------------------------------------------------
# Unit tests
# ----------------------------------------------------------------------
include(CTest)
enable_testing()
add_subdirectory(tests)


# ----------------------------------------------------------------------
# Installation
# ----------------------------------------------------------------------
include(GNUInstallDirs)

# Library files
install(
    TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

# Copy all header files from "./include" directory
install(
   DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
   DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
   FILES_MATCHING # install only matched files
   PATTERN "*.h"
)

# Copy all libary files from "./lib" directory
if (WIN32)
    install(
      DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib/"
      DESTINATION "${CMAKE_INSTALL_LIBDIR}"
      FILES_MATCHING # install only matched files
      PATTERN "*.lib"
    )
else()
    install(
      DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib/"
      DESTINATION "${CMAKE_INSTALL_LIBDIR}"
      FILES_MATCHING # install only matched files
      PATTERN "*.a"
    )
endif()

# Install CMake targets file
install(
  EXPORT ${PROJECT_NAME}Targets
  FILE ${PROJECT_NAME}Targets.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)

# ----------------------------------------------------------------------
# Create CMake Package, so other projects can use find_package()
# ----------------------------------------------------------------------
include(CMakePackageConfigHelpers)
set(CPPUNIT_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}}")

configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake.packaging/Config.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
  NO_SET_AND_CHECK_MACRO
  NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  VERSION "${CMAKE_PROJECT_VERSION}"
  COMPATIBILITY AnyNewerVersion
)

install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)

# Export target from a build tree, so it can be used by an outside project
# that references the build three with no installation involved
export(
  EXPORT ${PROJECT_NAME}Targets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake"
  NAMESPACE ${PROJECT_NAME}::
)

# ]==]

message(STATUS "------------------------------------------------------------------------")
message(STATUS "${PROJECT_NAME} - Configuration completed")
message(STATUS "########################################################################")
