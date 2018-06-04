add_executable(Maketable MakeTable.cxx)

add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Table.h
	DEPENDS Maketable
	COMMAND Maketable ${CMAKE_CURRENT_BINARY_DIR}/Table.h
)
include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

add_library(MathFunctions mysqrt.cxx ${CMAKE_CURRENT_BINARY_DIR}/Table.h)

install(TARGETS MathFunctions DESTINATION bin)
install(FILES mysqrt.h DESTINATION include)