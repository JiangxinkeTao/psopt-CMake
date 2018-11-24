cmake_minimum_required(VERSION 3.7)

add_executable(chain chain.cxx)
target_link_libraries(chain 
	adolc 
    ipopt
    lusol
    cxsparse
    dmatrix
    psopt
    lapack
)

