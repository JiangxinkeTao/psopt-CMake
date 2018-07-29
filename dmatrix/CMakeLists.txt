cmake_minimum_required(VERSION 3.0)
project(dmatrix)

# dmatrix sources
set(HEADERS ${PROJECT_SOURCE_DIR}/include/dmatrixv.h
            ${PROJECT_SOURCE_DIR}/include/f2c.h)
set(SOURCES ${PROJECT_SOURCE_DIR}/src/dmatrixv.cxx )

# dmatrix directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# lusol directories 
set(LUSOL_DIR ${CMAKE_SOURCE_DIR}/lusol)
include_directories(${LUSOL_DIR}/csrc)

# cxsparse directories
set(CXSPARSE_DIR ${CMAKE_SOURCE_DIR}/SuiteSparse/CXSparse)
include_directories(${CXSPARSE_DIR}/../SuiteSparse_config
                    ${CXSPARSE_DIR}/Include)

# Compiler settings
set(CMAKE_CXX_FLAGS "-O0 -w")
add_definitions(-DLAPACK -DUNIX -DSPARSE_MATRIX -DHAVE_MALLOC)
add_library(dmatrix STATIC ${SOURCES} ${HEADERS})

# Installation settings
install(TARGETS dmatrix ARCHIVE DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include)

