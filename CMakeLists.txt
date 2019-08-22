cmake_minimum_required(VERSION 3.14)

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
set(CMAKE_DEBUG_POSTFIX "_d")

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
    src/GeometricObjects/GeometricObject.cpp
    src/GeometricObjects/Sphere.cpp
    src/Tracers/SingleSphere.cpp
    src/Tracers/Tracer.cpp
	src/Tracers/MultipleObjects.cpp
#    src/UserInterface/wxraytracer.cpp
    src/UserInterface/RenderThread.cpp
    src/UserInterface/RenderPixel.cpp
    src/UserInterface/RenderCanvas.cpp
	src/UserInterface/RenderFrame.cpp
	src/UserInterface/RenderApp.cpp
    src/Utilities/Normal.cpp
    src/Utilities/Point3D.cpp
    src/Utilities/RGBColor.cpp
    src/Utilities/Ray.cpp
    src/Utilities/ShadeRec.cpp
    src/Utilities/Vector3D.cpp
    src/World/ViewPlane.cpp
    src/World/World.cpp
    src/Events/Events.cpp
)

set (HEADERS
    src/GeometricObjects/GeometricObject.h
    src/GeometricObjects/Sphere.h
    src/Tracers/SingleSphere.h
    src/Tracers/Tracer.h
	src/Tracers/MultipleObjects.h
 #   src/UserInterface/wxraytracer.h
    src/UserInterface/RenderThread.h
    src/UserInterface/RenderPixel.h
    src/UserInterface/RenderCanvas.h
	src/UserInterface/RenderFrame.h
	src/UserInterface/RenderApp.h
    src/Utilities/Constants.h
    src/Utilities/Maths.h
    src/Utilities/Normal.h
    src/Utilities/Point3D.h
    src/Utilities/RGBColor.h
    src/Utilities/Ray.h
    src/Utilities/ShadeRec.h
    src/Utilities/Vector3D.h
    src/World/ViewPlane.h
    src/World/World.h
    src/Events/Events.h
)

if (MSVC)
    assign_source_group(${SOURCES})
    assign_source_group(${HEADERS})
endif ()

find_package(wxWidgets REQUIRED gl core base OPTIONAL_COMPONENTS net)
include(${wxWidgets_USE_FILE})

set(EXEC_NAME raytracer)
add_executable(${EXEC_NAME} WIN32 MACOSX_BUNDLE ${SOURCES} ${HEADERS})

target_link_libraries(${EXEC_NAME} ${wxWidgets_LIBRARIES})

# https://stackoverflow.com/questions/7304625/how-do-i-change-the-startup-project-of-a-visual-studio-solution-via-cmake/37994396#37994396
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${EXEC_NAME})
