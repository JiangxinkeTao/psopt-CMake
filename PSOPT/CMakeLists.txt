cmake_minimum_required(VERSION 3.0)
project(PSOPT)

# Source files
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(HEADERS ${SRC_DIR}/ipopt_psoc.h
            ${SRC_DIR}/ipopt_psopt.h
            ${SRC_DIR}/psopt.h)
file(GLOB SOURCES ${SRC_DIR}/*.cxx) #TODO: improve this lazy man solution

# dmatrix includes
include_directories(${CMAKE_SOURCE_DIR}/dmatrix/include)

# lusol includes
include_directories(${CMAKE_SOURCE_DIR}/lusol/csrc)

# adol-c includes
# TODO: give the option to build adol-c as part of this package
# include_directories(${CMAKE_SOURCE_DIR}/ADOL-C/include)

# ipopt includes
# TODO: give the option to build ipopt as part of this package
# include_directories(${CMAKE_SOURCE_DIR}/IPOPT/include)

# compiler settings
set(CMAKE_CXX_FLAGS "-O0 -Wall")
add_definitions(-DUNIX -DUSE_IPOPT)
add_library(psopt STATIC ${HEADERS} ${SOURCES})

# install settings
install(TARGETS psopt ARCHIVE DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include)

