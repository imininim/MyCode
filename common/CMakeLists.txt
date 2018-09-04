#include路径
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/common/)
include_directories(.)
#链接查找路径
link_directories(.)
link_directories(../lib)
link_directories(bin)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/lib)

AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/common/ CPP_SRC)

add_library(common SHARED ${CPP_SRC})
target_link_libraries(common qthserver)
install(TARGETS common DESTINATION lib)
