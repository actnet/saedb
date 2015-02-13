cmake_minimum_required (VERSION 2.8)

include_directories ("${CMAKE_CURRENT_SOURCE_DIR}")

# add the core libraries
add_subdirectory (model)
add_subdirectory (averagesssp)
add_subdirectory (commonnb)
add_subdirectory (degreecentrality)
add_subdirectory (degreedistribution)
add_subdirectory (networkconstraints)
add_subdirectory (pagerank)
add_subdirectory (sssp)
add_subdirectory (console)