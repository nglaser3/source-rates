# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# name and version
project(DepletionProject VERSION 1.0)

# cpp standard to 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# setting the include directory
include_directories(include)

# getting all the .cpp files :) we love GLOB
file(GLOB DEPLETION_SOURCES depletion/src/*.cpp)

# adding NJOY21 and petsc as submodules
add_subdirectory(NJOY21)  # NJOY21 uses CMake so this works i guess?

# petsc is weird and uses GNUMakefile... what even is that? hopefully this works...
# If not need to ask around... Professor Huff likely knowns
include(ExternalProject)

ExternalProject_Add(
    PETSc
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/petsc_install
    BUILD_ALWAYS 1
)

# defining the executable
add_executable(DepletionExecutable ${DEPLETION_SOURCES})

# Linking njoy21 to this project
target_link_libraries(DepletionExecutable NJOY21)

# do petsc link after it has been built with the ExternalProject
add_dependencies(DepletionExecutable PETSc) # i think this builds petsc

# with petsc built we gotta link it
# check petsc is installed and its libraries are linked
target_include_directories(DepletionExecutable PRIVATE ${CMAKE_BINARY_DIR}/petsc_install/include)
target_link_directories(DepletionExecutable PRIVATE ${CMAKE_BINARY_DIR}/petsc_install/lib)

# If PETSc provides a specific library to link against (e.g., libpetsc), link it here
# target_link_libraries(DepletionExecutable ${CMAKE_BINARY_DIR}/petsc_install/lib/libpetsc.a)

# Optionally, if your project has custom install rules
# install(TARGETS DepletionExecutable DESTINATION /usr/local/bin)
