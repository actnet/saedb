project(model)

file(GLOB MODEL_SOURCES "*.hpp" "*.cpp")

add_library(model ${MODEL_SOURCES})
target_link_libraries(model computing testing)