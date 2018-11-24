cmake_minimum_required(VERSION 3.7)

add_executable(brymr brymr.cxx)
target_link_libraries(brymr 
	adolc 
    ipopt
    lusol
    cxsparse
    dmatrix
    psopt
    lapack
)

