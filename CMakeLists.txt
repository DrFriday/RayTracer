cmake_minimum_required(VERSION 2.8)

project(RayTracer)



# From http://stackoverflow.com/questions/31422680/how-to-set-visual-studio-filters-for-nested-sub-directory-using-cmake
function(assign_source_group)
    foreach(_source IN ITEMS ${ARGN})
        if (IS_ABSOLUTE "${_source}")
            file(RELATIVE_PATH _source_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source}")
        else()
            set(_source_rel "${_source}")
        endif()
        get_filename_component(_source_path "${_source_rel}" PATH)
        string(REPLACE "/" "\\" _source_path_msvc "${_source_path}")
        source_group("${_source_path_msvc}" FILES "${_source}")
    endforeach()
endfunction(assign_source_group)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(targetDir ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${targetDir})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${targetDir})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${targetDir})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${targetDir})
if (MSVC)
    set_target_properties(${name} PROPERTIES LINK_FLAGS_RELEASE "/PDBSTRIPPED:\"${targetDir}/${name}_stripped.pdb\"")
endif()

# Set flags
if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set (CMAKE_CXX_FLAGS "-g -std=c++11 -Wall")
endif ()

set (SOURCES
    src/main.cpp
)

set (HEADERS
    src/tests/Test.h
)

if (MSVC)
    assign_source_group(${SOURCES})
    assign_source_group(${HEADERS})
endif ()

find_package(wxWidgets REQUIRED gl core net OPTIONAL_COMPONENTS base)
include(${wxWidgets_USE_FILE})

set(EXEC_NAME raytracer)
add_executable(${EXEC_NAME} WIN32 MACOSX_BUNDLE ${SOURCES} ${HEADERS})

target_link_libraries(${EXEC_NAME} ${wxWidgets_LIBRARIES})
