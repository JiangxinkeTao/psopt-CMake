cmake_minimum_required(VERSION 3.7)

add_executable(brac1 brac1.cxx)
target_link_libraries(brac1 
	adolc 
    ipopt
    lusol
    cxsparse
    dmatrix
    psopt
    lapack
)

