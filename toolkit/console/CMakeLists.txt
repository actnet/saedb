project(console)

file(GLOB CONSOLE_SOURCES "*.hpp" "*.cpp")

add_executable(console ${CONSOLE_SOURCES})
target_link_libraries(console averagesssp commonnb degreecentrality degreedistribution networkconstraints pagerank sssp)

add_test(NAME console COMMAND conosle)
