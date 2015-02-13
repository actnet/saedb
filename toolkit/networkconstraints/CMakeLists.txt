project(networkconstraints)

file(GLOB NETWORKCONSTRAINS_SOURCES "*.hpp" "*.cpp")

add_library(networkconstraints ${NETWORKCONSTRAINS_SOURCES})
target_link_libraries(networkconstraints model)

