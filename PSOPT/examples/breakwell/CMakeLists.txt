cmake_minimum_required(VERSION 3.7)

add_executable(breakwell breakwell.cxx)
target_link_libraries(breakwell 
	adolc 
    ipopt
    lusol
    cxsparse
    dmatrix
    psopt
    lapack
)

