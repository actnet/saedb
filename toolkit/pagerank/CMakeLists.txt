project(pagerank)

file(GLOB PAGERANK_SOURCES "*.hpp" "*.cpp")

add_library(pagerank ${PAGERANK_SOURCES})
target_link_libraries(pagerank model)

