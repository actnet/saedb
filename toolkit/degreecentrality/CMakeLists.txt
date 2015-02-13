project(degreecentrality)

file(GLOB DEGREECENTRALITY_SOURCES "*.hpp" "*.cpp")

add_library(degreecentrality ${DEGREECENTRALITY_SOURCES})
target_link_libraries(degreecentrality model)

