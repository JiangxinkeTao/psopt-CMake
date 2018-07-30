cmake_minimum_required(VERSION 3.7)

add_executable(alpine alpine.cxx)
target_compile_definitions(alpine PRIVATE UNIX LAPACK)
target_link_libraries(alpine adolc 
                             ipopt
                             liblusol.a
                             libcxsparse.a 
                             libdmatrix.a
                             libpsopt.a
                             lapack
                             )

