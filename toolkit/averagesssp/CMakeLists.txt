project(averagesssp)

file(GLOB AVERAGESSSP_SOURCES "*.hpp" "*.cpp")

add_library(averagesssp ${AVERAGESSSP_SOURCES})
target_link_libraries(averagesssp model)

