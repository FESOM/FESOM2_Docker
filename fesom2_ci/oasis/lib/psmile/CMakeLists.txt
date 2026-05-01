cmake_minimum_required(VERSION 3.4)

project(psmile C Fortran)

# get our source files
set(src_home ${CMAKE_CURRENT_LIST_DIR}) # path to src directory starting from the dir containing our CMakeLists.txt
file(GLOB sources_Fortran ${src_home}/src/*.F90)
set(all_headers ${src_home}/include)
file(GLOB sources_C ${src_home}/src/*.c)

#if(${CMAKE_Fortran_COMPILER_ID} STREQUAL "Intel")
#	set(-ansi_alias -fp-model precise -no-fast-transcendentals)
#else()
#    set(-emf -O2 -h cpu=x86-skylake -h byteswapio)
#endif()
#message("#################################")
#message("${OASIS_FFLAGS}")
# depends on the mct library
add_subdirectory(../mct/mct ${PROJECT_BINARY_DIR}/mct)

# depends on the scrip library
add_subdirectory(../scrip/src ${PROJECT_BINARY_DIR}/scrip)

include(${CMAKE_CURRENT_LIST_DIR}/../../cmake/FindNETCDF.cmake)

# create our library (set its name to name of this project)
add_library(${PROJECT_NAME} ${sources_Fortran} ${sources_C})
target_link_libraries(${PROJECT_NAME} PRIVATE ${NETCDF_Fortran_LIBRARIES} mct scrip)
target_compile_definitions(${PROJECT_NAME} PRIVATE use_libMPI use_netCDF use_comm_MPI1 HAVE_SLASHPROC FORTRANUNDERSCORE )
target_include_directories(${PROJECT_NAME}
PRIVATE ${NETCDF_Fortran_INCLUDE_DIRECTORIES} ${all_headers}
INTERFACE ${PROJECT_BINARY_DIR}
)
target_compile_options(${PROJECT_NAME} PRIVATE $ENV{OASIS_FFLAGS})
target_link_options(${PROJECT_NAME} PRIVATE $ENV{OASIS_LFLAGS})
if(${CMAKE_Fortran_COMPILER_ID} STREQUAL  GNU)
   target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:Fortran>:-ffree-line-length-none>)
   if(CMAKE_Fortran_COMPILER_VERSION VERSION_GREATER_EQUAL 10)
      target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:Fortran>:-fallow-argument-mismatch>) # gfortran v10 is strict about erroneous API calls: "Rank mismatch between actual argument at (1) and actual argument at (2) (scalar and rank-1)"
   endif()
endif()
