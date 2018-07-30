cmake_minimum_required(VERSION 3.7)

# PSOPT headers and files
set(HEADERS ${PSOPT_DIR}/src/ipopt_psoc.h
            ${PSOPT_DIR}/src/ipopt_psopt.h
            ${PSOPT_DIR}/src/psopt.h)

set(SOURCES ${PSOPT_DIR}/src/derivatives.cxx
            ${PSOPT_DIR}/src/evaluate.cxx
            ${PSOPT_DIR}/src/get_numbers.cxx
            ${PSOPT_DIR}/src/get_variables.cxx
            ${PSOPT_DIR}/src/integrate.cxx
            ${PSOPT_DIR}/src/interpolation.cxx
            ${PSOPT_DIR}/src/IPOPT_interface.cxx
            ${PSOPT_DIR}/src/mesh.cxx
            ${PSOPT_DIR}/src/NLP_bounds.cxx
            ${PSOPT_DIR}/src/NLP_constraints.cxx
            ${PSOPT_DIR}/src/NLP_guess.cxx
            ${PSOPT_DIR}/src/NLP_interface.cxx
            ${PSOPT_DIR}/src/NLP_objective.cxx
            ${PSOPT_DIR}/src/parameter_estimation.cxx
            ${PSOPT_DIR}/src/phases.cxx
            ${PSOPT_DIR}/src/plot.cxx
            ${PSOPT_DIR}/src/print.cxx
            ${PSOPT_DIR}/src/propagate.cxx
            ${PSOPT_DIR}/src/pseudospectral.cxx
            ${PSOPT_DIR}/src/psopt.cxx
            ${PSOPT_DIR}/src/scaling.cxx
            ${PSOPT_DIR}/src/setup.cxx
            ${PSOPT_DIR}/src/SNOPT_interface.cxx
            ${PSOPT_DIR}/src/solution.cxx
            ${PSOPT_DIR}/src/trajectories.cxx
            ${PSOPT_DIR}/src/user_functions.cxx
            ${PSOPT_DIR}/src/util.cxx
            ${PSOPT_DIR}/src/validate.cxx
            ${PSOPT_DIR}/src/workspace.cxx)

# compiler settings
add_library(psopt STATIC ${HEADERS} ${SOURCES})
target_compile_definitions(psopt PRIVATE UNIX LAPACK SPARSE_MATRIX 
                                         USE_IPOPT)
target_compile_options(psopt PRIVATE -O0 -g -w)


# install settings
install(TARGETS psopt ARCHIVE DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include)

# compile examples
add_subdirectory(examples)

