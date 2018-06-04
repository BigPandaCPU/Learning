cmake_minimum_required (VERSION 2.6)
project (Tutorial)
#版本号
set(Tutorial_VERSION_MAJOR 1)
set(Tutorial_VERSION_MINOR 0)
include(${CMAKE_ROOT}/Modules/CheckFunctionExists.cmake)

check_function_exists(log HAVE_LOG)
check_function_exists(exp HAVE_EXP)


#include_directories("${PROJECT_SOURCE_DIR}/MathFunctions}")
#add_subdirectory(MathFunctions)

option(USE_MYMATH "Use tutorial provided math implementation" ON)
if(USE_MYMATH)
	include_directories("${PROJECT_SOURCE_DIR}/MathFunctions}")
	add_subdirectory(MathFunctions)
	set(EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif(USE_MYMATH)




#配置一个头文件，通过它向源码传递一些Cmake设置
configure_file(
"${PROJECT_SOURCE_DIR}/TutorialConfig.h.in"
"${PROJECT_BINARY_DIR}/TutorialConfig.h"
)


#将二进制文件树添加到到包含文件的搜索路径中，这样我们可以找到
include_directories("${PROJECT_BINARY_DIR}")


#添加可执行文件
add_executable(Tutorial Tutorial.cxx)
target_link_libraries(Tutorial ${EXTRA_LIBS})
install(TARGETS Tutorial DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h" DESTINATION include)

add_test(TutorialRuns Tutorial 25)