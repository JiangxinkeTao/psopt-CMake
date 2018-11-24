cmake_minimum_required(VERSION 3.7)

add_executable(climb climb.cxx)
target_link_libraries(climb 
	adolc 
    ipopt
    lusol
    cxsparse
    dmatrix
    psopt
    lapack
)

