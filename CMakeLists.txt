# Minimum required version of CMake
cmake_minimum_required(VERSION 3.30)
project(Depletion)

# cpp standard to 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

# getting all the .cpp files :) we love GLOB
file(GLOB DEPLETION_SOURCES src/*.cpp)

add_executable(depletion-opt ${DEPLETION_SOURCES})

#submodule time
include(ExternalProject) #ew petsc is not pretty
ExternalProject_Add(PETSc
  SOURCE_DIR "${CMAKE_SOURCE_DIR}/petsc"
  CONFIGURE_COMMAND cd ${CMAKE_SOURCE_DIR}/petsc && rm -rf arch-darwin-c-debug && ./configure --prefix=${CMAKE_SOURCE_DIR}/build/petsc --with-mpi --with-shared-libraries=0 --with-static-libraries=1 --with-fortran --download-fblaslapack
  BUILD_COMMAND cd ${CMAKE_SOURCE_DIR}/petsc && make -f GNUmakefile clean && make -f GNUmakefile all #make all clean
  INSTALL_COMMAND cd ${CMAKE_SOURCE_DIR}/petsc && make -f GNUmakefile install
  BUILD_BYPRODUCTS "${CMAKE_SOURCE_DIR}/build/petsc/lib/libpetsc.a"
)

add_dependencies(depletion-opt PETSc)
include_directories("${CMAKE_SOURCE_DIR}/build/petsc/include")

link_directories("${CMAKE_SOURCE_DIR}/build/petsc/lib")

target_link_libraries(depletion-opt PRIVATE "${CMAKE_SOURCE_DIR}/build/petsc/lib/libpetsc.a")

list(APPEND COMPILE_OPTIONS ${PETSC_CFLAGS})
list(APPEND LIBRARIES ${PETSC_LINK_LIBRARIES})