project(degreedistribution)

file(GLOB DEGREEDISTRIBUTION_SOURCES "*.hpp" "*.cpp")

add_library(degreedistribution ${DEGREEDISTRIBUTION_SOURCES})
target_link_libraries(degreedistribution model)

