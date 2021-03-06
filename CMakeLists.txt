cmake_minimum_required (VERSION 2.8)

project (toy)

set(EXECABLE_NAME toy)
set(INCLUDES 
    include
    external
    external/SOIL/src
    )

set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
set(CMAKE_BUILD_TYPE "Debug") #set debug mode

aux_source_directory(src DIR_SRCS)

add_subdirectory(external/glfw-3.2)

# framework for osx
if (APPLE)
    find_library(OPENGL OpenGl)
    find_library(CORE CoreFoundation)
    find_library(GLUT GLUT)
    mark_as_advanced(OPENGL
                     CORE
                     GLUT)
    set(EXTRA_LIBS ${OPENGL} ${CORE} ${GLUT})
endif(APPLE)

include_directories(${INCLUDES})

add_executable(${EXECABLE_NAME} ${DIR_SRCS})
target_compile_features(${EXECABLE_NAME} PRIVATE cxx_range_for)

target_link_libraries(${EXECABLE_NAME} soil glfw ${EXTRA_LIBS})

#external library
set(SOIL_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/external/SOIL/lib/libSOIL.a)

add_custom_target(build_soil ALL
    COMMAND ${CMAKE_MAKE_PROGRAM}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/external/SOIL/projects/makefile
    COMMENT "build soil lib...")

add_library(soil STATIC IMPORTED)

set_property(TARGET soil APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(soil PROPERTIES IMPORTED_LOCATION_NOCONFIG "${SOIL_LIBRARY}")

add_dependencies(soil build_soil)

add_custom_command(TARGET ${EXECABLE_NAME}
    POST_BUILD 
    COMMAND cp -r ${CMAKE_CURRENT_SOURCE_DIR}/resource .
    COMMENT "copying resource directory..."
    )
