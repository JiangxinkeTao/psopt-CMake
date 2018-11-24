cmake_minimum_required(VERSION 3.7)

add_executable(bryden bryson_denham.cxx)
target_link_libraries(bryden 
	adolc 
    ipopt
    lusol
    cxsparse
    dmatrix
    psopt
    lapack
)

