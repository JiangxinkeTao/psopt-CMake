cmake_minimum_required(VERSION 3.7)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

project(psopt C CXX)
find_package(IPOPT REQUIRED)
find_package(ADOLC REQUIRED)
find_package(CXSparse REQUIRED)

add_definitions("-DHAVE_CSTDDEF -DSPARSE_MATRIX -DUNIX")

# Sub projects directories

# Include directories
include_directories(lusol/csrc
                    dmatrix/include
                    PSOPT/src
                    ${CXSPARSE_INCLUDE_DIRS})



# dmatrix headers and sources
set(DMATRIX_HDR ${DMATRIX_DIR}/include/dmatrixv.h
                ${DMATRIX_DIR}/include/f2c.h)
set(DMATRIX_SRC ${DMATRIX_DIR}/src/dmatrixv.cxx)

# build dmatrix
add_library(dmatrix STATIC ${DMATRIX_HDR} ${DMATRIX_SRC})
target_compile_definitions(dmatrix PRIVATE UNIX LAPACK SPARSE_MATRIX HAVE_MALLOC)
target_link_libraries(dmatrix cxsparse lusol)

add_subdirectory(lusol)
add_subdirectory(PSOPT)
