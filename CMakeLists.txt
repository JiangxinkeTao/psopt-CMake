cmake_minimum_required(VERSION 3.7)
project(psopt C CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
find_package(IPOPT REQUIRED)
find_package(ADOLC REQUIRED)
find_package(CXSparse REQUIRED)

add_definitions("-DHAVE_CSTDDEF -DSPARSE_MATRIX -DUNIX")

include_directories(lusol/csrc
                    dmatrix/include
                    PSOPT/src
                    ${CXSPARSE_INCLUDE_DIRS}
                    ${IPOPT_INCLUDE_DIRS})

add_library(lusol
    lusol/csrc/lusol.c
    lusol/csrc/mmio.c
    lusol/csrc/commonlib.c
    lusol/csrc/lusolio.c
    lusol/csrc/hbio.c
    lusol/csrc/myblas.c)
target_compile_definitions(lusol PRIVATE YZHANG NDBUG)
target_compile_options(lusol PRIVATE -pthread -ansi -fPIC)

add_library(dmatrix dmatrix/src/dmatrixv.cxx)
target_compile_definitions(dmatrix PRIVATE UNIX LAPACK SPARSE_MATRIX HAVE_MALLOC)
target_link_libraries(dmatrix cxsparse lusol)


add_library(psopt
    PSOPT/src/derivatives.cxx
    PSOPT/src/evaluate.cxx
    PSOPT/src/get_numbers.cxx
    PSOPT/src/get_variables.cxx
    PSOPT/src/integrate.cxx
    PSOPT/src/interpolation.cxx
    PSOPT/src/IPOPT_interface.cxx
    PSOPT/src/mesh.cxx
    PSOPT/src/NLP_bounds.cxx
    PSOPT/src/NLP_constraints.cxx
    PSOPT/src/NLP_guess.cxx
    PSOPT/src/NLP_interface.cxx
    PSOPT/src/NLP_objective.cxx
    PSOPT/src/parameter_estimation.cxx
    PSOPT/src/phases.cxx
    PSOPT/src/plot.cxx
    PSOPT/src/print.cxx
    PSOPT/src/propagate.cxx
    PSOPT/src/pseudospectral.cxx
    PSOPT/src/psopt.cxx
    PSOPT/src/scaling.cxx
    PSOPT/src/setup.cxx
    PSOPT/src/SNOPT_interface.cxx
    PSOPT/src/solution.cxx
    PSOPT/src/trajectories.cxx
    PSOPT/src/user_functions.cxx
    PSOPT/src/util.cxx
    PSOPT/src/validate.cxx
    PSOPT/src/workspace.cxx)
target_link_libraries(psopt lusol dmatrix dl ${CXSPARSE_LIBRARIES} ${IPOPT_LIBRARIES})
target_compile_definitions(psopt PRIVATE USE_IPOPT)

if(PSOPT_BUILD_EXAMPLES)
	add_subdirectory(PSOPT/examples)
endif(PSOPT_BUILD_EXAMPLES)