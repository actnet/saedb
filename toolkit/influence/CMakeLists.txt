project(influence)

file(GLOB INFLUENCE_TEST_SOURCES "*.hpp" "*.cpp")

add_executable(influence_test ${INFLUENCE_TEST_SOURCES})
target_link_libraries(influence_test computing)

