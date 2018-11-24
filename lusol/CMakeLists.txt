cmake_minimum_required(VERSION 2.8.3)
project(lusol)

include_directories(csrc)

# Lusol headers and sources
set(LUSOL_HDR csrc/lusol.h
              csrc/mmio.h
              csrc/commonlib.h
              csrc/lusolio.h
              csrc/hbio.h
              csrc/myblas.h)

set(LUSOL_SRC csrc/lusol.c
              csrc/mmio.c
              csrc/commonlib.c
              csrc/lusolio.c
              csrc/hbio.c
              csrc/myblas.c)

add_library(lusol STATIC ${LUSOL_HDR} ${LUSOL_SRC})
target_compile_definitions(lusol PRIVATE YZHANG NDBUG)
target_compile_options(lusol PRIVATE -pthread -ansi -fPIC)