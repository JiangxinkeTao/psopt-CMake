cmake_minimum_required(VERSION 3.7)

add_executable(steps steps.cxx)
target_link_libraries(steps
    adolc
    psopt
)

