cmake_minimum_required(VERSION 3.4)

project(mct Fortran)

# get our source files
set(src_home ${CMAKE_CURRENT_LIST_DIR}) # path to src directory starting from the dir containing our CMakeLists.txt
file(GLOB all_sources ${src_home}/*.F90)

# depends on the mpeu library
add_subdirectory(../mpeu ${PROJECT_BINARY_DIR}/mpeu)

# create our library (set its name to name of this project)
add_library(${PROJECT_NAME} ${all_sources})
target_link_libraries(${PROJECT_NAME} mpeu)
target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_BINARY_DIR}) # depending projects should include our *.mod files
target_compile_definitions(${PROJECT_NAME} PRIVATE use_libMPI use_netCDF use_comm_MPI1)
target_compile_options(${PROJECT_NAME} PRIVATE $ENV{OASIS_FFLAGS})
target_link_options(${PROJECT_NAME} PRIVATE $ENV{OASIS_LFLAGS})
if(${CMAKE_Fortran_COMPILER_ID} STREQUAL  GNU)
   target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:Fortran>:-ffree-line-length-none>)
   if(CMAKE_Fortran_COMPILER_VERSION VERSION_GREATER_EQUAL 10)
      target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:Fortran>:-fallow-argument-mismatch>) # gfortran v10 is strict about erroneous API calls: "Rank mismatch between actual argument at (1) and actual argument at (2) (scalar and rank-1)"
   endif()
endif()
