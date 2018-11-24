cmake_minimum_required(VERSION 3.7)

add_executable(bioreactor bioreactor.cxx)
target_link_libraries(bioreactor 
	adolc 
    ipopt
    lusol
    cxsparse
    dmatrix
    psopt
    lapack
)

