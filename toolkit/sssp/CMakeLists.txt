project(sssp)

file(GLOB SSSP_SOURCES "*.hpp" "*.cpp")

add_library(sssp ${SSSP_SOURCES})
target_link_libraries(sssp model)

