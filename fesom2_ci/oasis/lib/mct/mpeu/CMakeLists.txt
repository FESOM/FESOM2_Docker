cmake_minimum_required(VERSION 3.4)

project(mpeu C Fortran)

# get our source files
set(src_home ${CMAKE_CURRENT_LIST_DIR}) # path to src directory starting from the dir containing our CMakeLists.txt
file(GLOB sources_Fortran ${src_home}/*.F90)
list(REMOVE_ITEM sources_Fortran ${src_home}/m_StringLinkedList.F90) # this file is not included in the origonal Makefile build of mpeu

file(GLOB sources_C ${src_home}/get_zeits.c)

find_path(configure_generated_config_h_dir config.h HINTS ${CMAKE_CURRENT_LIST_DIR}/..)

# create our library (set its name to name of this project)
add_library(${PROJECT_NAME} ${sources_Fortran} ${sources_C})
target_include_directories(${PROJECT_NAME}
PRIVATE ${configure_generated_config_h_dir}
INTERFACE ${PROJECT_BINARY_DIR} # if other projects use this library (i.e. via add_subdirectory), we want them to include the directory where our mod files are placed by the compiler
)
target_compile_definitions(${PROJECT_NAME} PRIVATE use_libMPI use_netCDF use_comm_MPI1)
target_compile_options(${PROJECT_NAME} PRIVATE $ENV{OASIS_FFLAGS})
target_link_options(${PROJECT_NAME} PRIVATE $ENV{OASIS_LFLAGS})
if(${CMAKE_Fortran_COMPILER_ID} STREQUAL  GNU)
   target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:Fortran>:-ffree-line-length-none>)
   if(CMAKE_Fortran_COMPILER_VERSION VERSION_GREATER_EQUAL 10)
      target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:Fortran>:-fallow-argument-mismatch>) # gfortran v10 is strict about erroneous API calls: "Rank mismatch between actual argument at (1) and actual argument at (2) (scalar and rank-1)"
   endif()
endif()
