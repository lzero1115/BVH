cmake_minimum_required(VERSION 3.16)
project(boundaryvolumehierarchy LANGUAGES CXX)

# --- 1. Set Build Type to Release ---
# if(NOT CMAKE_BUILD_TYPE)
#   set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
# endif()
set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
# --- 2. Enable libigl Modules BEFORE add_subdirectory ---
# These names match exactly with the options in libigl/CMakeLists.txt
set(LIBIGL_GLFW           ON CACHE BOOL "" FORCE)
set(LIBIGL_OPENGL         ON CACHE BOOL "" FORCE)
set(LIBIGL_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(LIBIGL_BUILD_TUTORIALS OFF CACHE BOOL "" FORCE)

# --- 3. Add libigl subdirectory ---
add_subdirectory(deps/libigl)

# --- 4. Define your Library ---
file(GLOB SRCFILES "src/*.cpp")
add_library(core STATIC ${SRCFILES})

# Link your own include directory
target_include_directories(core PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

# --- 5. Link Libraries ---
# According to the tutorial file, the standard target names are igl::glfw and igl::opengl
# Note: Linking to igl::glfw usually brings in igl::opengl automatically
target_link_libraries(core PUBLIC 
    igl::core 
    igl::opengl 
    igl::glfw
)

# --- 6. Create Executables ---
set(PROGRAMS rays distances intersections)

foreach(PROG ${PROGRAMS})
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${PROG}.cpp")
        add_executable(${PROG} "${PROG}.cpp")
        target_link_libraries(${PROG} PRIVATE core)
    endif()
endforeach()