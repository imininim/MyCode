#include路径
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/raft/)
include_directories(${PROJECT_SOURCE_DIR}/common/)
include_directories(.)
#链接查找路径
link_directories(.)
link_directories(../lib)
link_directories(bin)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin/node_status/)

AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/example/node_status/ CPP_SRC)
#添加可执行程序test
add_executable(node_status ${CPP_SRC})
target_link_libraries(node_status raft common)
install(TARGETS node_status DESTINATION bin)

