project(commonnb)

file(GLOB COMMONNB_SOURCES "*.hpp" "*.cpp")

add_library(commonnb ${COMMONNB_SOURCES})
target_link_libraries(commonnb model)

