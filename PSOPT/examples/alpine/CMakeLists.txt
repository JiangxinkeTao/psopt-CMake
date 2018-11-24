cmake_minimum_required(VERSION 3.7)

add_executable(alpine alpine.cxx)
target_link_libraries(alpine
    adolc
    psopt
)

