cmake_minimum_required(VERSION 3.7)

add_executable(catmix catmix.cxx)
target_link_libraries(catmix 
	adolc 
    ipopt
    lusol
    cxsparse
    dmatrix
    psopt
    lapack
)

