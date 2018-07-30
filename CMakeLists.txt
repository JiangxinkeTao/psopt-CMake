cmake_minimum_required(VERSION 3.7)

project(psopt C CXX)

# Sub projects directories
set(LUSOL_DIR ${PROJECT_SOURCE_DIR}/lusol)
set(SSPARSE_DIR ${PROJECT_SOURCE_DIR}/SuiteSparse)
set(CXSPARSE_DIR ${SSPARSE_DIR}/CXSparse)
set(DMATRIX_DIR ${PROJECT_SOURCE_DIR}/dmatrix)
set(PSOPT_DIR ${PROJECT_SOURCE_DIR}/PSOPT)

# Include directories
include_directories(${LUSOL_DIR}/csrc
                    ${SSPARSE_DIR}/SuiteSparse_config
                    ${CXSPARSE_DIR}/Include
                    ${DMATRIX_DIR}/include
                    ${PSOPT_DIR}/src)

# Libraries path
link_directories($ENV{HOME}/usr/local/lib)

# Lusol headers and sources
set(LUSOL_HDR ${LUSOL_DIR}/csrc/lusol.h
              ${LUSOL_DIR}/csrc/mmio.h
              ${LUSOL_DIR}/csrc/commonlib.h
              ${LUSOL_DIR}/csrc/lusolio.h
              ${LUSOL_DIR}/csrc/hbio.h
              ${LUSOL_DIR}/csrc/myblas.h)

set(LUSOL_SRC ${LUSOL_DIR}/csrc/lusol.c
              ${LUSOL_DIR}/csrc/mmio.c
              ${LUSOL_DIR}/csrc/commonlib.c
              ${LUSOL_DIR}/csrc/lusolio.c
              ${LUSOL_DIR}/csrc/hbio.c
              ${LUSOL_DIR}/csrc/myblas.c)

# CXSparse sources
set(CXSPARSE_HDR ${CXSPARSE_DIR}/Include/cs.h)

set(CXSPARSE_SRC ${CXSPARSE_DIR}/Source/cs_add.c
                 ${CXSPARSE_DIR}/Source/cs_amd.c
                 ${CXSPARSE_DIR}/Source/cs_chol.c
                 ${CXSPARSE_DIR}/Source/cs_cholsol.c
                 ${CXSPARSE_DIR}/Source/cs_counts.c
                 ${CXSPARSE_DIR}/Source/cs_cumsum.c
                 ${CXSPARSE_DIR}/Source/cs_droptol.c
                 ${CXSPARSE_DIR}/Source/cs_dropzeros.c
                 ${CXSPARSE_DIR}/Source/cs_dupl.c
                 ${CXSPARSE_DIR}/Source/cs_entry.c
                 ${CXSPARSE_DIR}/Source/cs_etree.c
                 ${CXSPARSE_DIR}/Source/cs_fkeep.c
                 ${CXSPARSE_DIR}/Source/cs_gaxpy.c
                 ${CXSPARSE_DIR}/Source/cs_happly.c
                 ${CXSPARSE_DIR}/Source/cs_house.c
                 ${CXSPARSE_DIR}/Source/cs_ipvec.c
                 ${CXSPARSE_DIR}/Source/cs_lsolve.c
                 ${CXSPARSE_DIR}/Source/cs_ltsolve.c
                 ${CXSPARSE_DIR}/Source/cs_lu.c
                 ${CXSPARSE_DIR}/Source/cs_lusol.c
                 ${CXSPARSE_DIR}/Source/cs_util.c
                 ${CXSPARSE_DIR}/Source/cs_multiply.c
                 ${CXSPARSE_DIR}/Source/cs_permute.c
                 ${CXSPARSE_DIR}/Source/cs_pinv.c
                 ${CXSPARSE_DIR}/Source/cs_post.c
                 ${CXSPARSE_DIR}/Source/cs_pvec.c
                 ${CXSPARSE_DIR}/Source/cs_qr.c
                 ${CXSPARSE_DIR}/Source/cs_qrsol.c
                 ${CXSPARSE_DIR}/Source/cs_scatter.c
                 ${CXSPARSE_DIR}/Source/cs_schol.c
                 ${CXSPARSE_DIR}/Source/cs_sqr.c
                 ${CXSPARSE_DIR}/Source/cs_symperm.c
                 ${CXSPARSE_DIR}/Source/cs_tdfs.c
                 ${CXSPARSE_DIR}/Source/cs_malloc.c
                 ${CXSPARSE_DIR}/Source/cs_transpose.c
                 ${CXSPARSE_DIR}/Source/cs_compress.c
                 ${CXSPARSE_DIR}/Source/cs_usolve.c
                 ${CXSPARSE_DIR}/Source/cs_utsolve.c
                 ${CXSPARSE_DIR}/Source/cs_scc.c
                 ${CXSPARSE_DIR}/Source/cs_maxtrans.c
                 ${CXSPARSE_DIR}/Source/cs_dmperm.c
                 ${CXSPARSE_DIR}/Source/cs_updown.c
                 ${CXSPARSE_DIR}/Source/cs_print.c
                 ${CXSPARSE_DIR}/Source/cs_norm.c
                 ${CXSPARSE_DIR}/Source/cs_load.c
                 ${CXSPARSE_DIR}/Source/cs_dfs.c
                 ${CXSPARSE_DIR}/Source/cs_reach.c
                 ${CXSPARSE_DIR}/Source/cs_spsolve.c
                 ${CXSPARSE_DIR}/Source/cs_leaf.c
                 ${CXSPARSE_DIR}/Source/cs_ereach.c
                 ${CXSPARSE_DIR}/Source/cs_convert.c )

# dmatrix headers and sources
set(DMATRIX_HDR ${DMATRIX_DIR}/include/dmatrixv.h
                ${DMATRIX_DIR}/include/f2c.h)

set(DMATRIX_SRC ${DMATRIX_DIR}/src/dmatrixv.cxx)

# build lusol sub project
add_library(lusol STATIC ${LUSOL_HDR} ${LUSOL_SRC})
target_compile_definitions(lusol PRIVATE YZHANG NDBUG)
target_compile_options(lusol PRIVATE -O3 -Wall -fexceptions -pthread -ansi 
                                     -fPIC)

# build cxsparse sub project
# as in the original psopt, builds just the CS_DI version of CXSparse
add_library(cxsparse STATIC ${CXSPARSE_HDR} ${CXSPARSE_SRC})
#target_compile_definitions(cxsparse)
target_compile_options(cxsparse PRIVATE -O0 -g -w)
set_target_properties(cxsparse PROPERTIES LINKER_LANGUAGE C)


# build dmatrix
add_library(dmatrix STATIC ${DMATRIX_HDR} ${DMATRIX_SRC})
target_compile_definitions(dmatrix PRIVATE UNIX LAPACK SPARSE_MATRIX
                                           HAVE_MALLOC)
target_compile_options(dmatrix PRIVATE -O0 -g -w)

# build psopt
add_subdirectory(PSOPT)

# installation rule
install(TARGETS lusol cxsparse dmatrix ARCHIVE DESTINATION lib)
install(FILES ${LUSOL_HDR} ${CXSPARSE_HDR} ${DMATRIX_HDR}
        DESTINATION include)


