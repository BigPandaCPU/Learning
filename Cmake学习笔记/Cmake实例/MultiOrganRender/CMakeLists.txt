cmake_minimum_required( VERSION 3.0 )
project( viewImage )

set( CMAKE_PREFIX_PATH "E:\\OpenSource\\VTK711Pro32Release" )

#set( CMAKE_INCLUDE_CURRENT_DIR ON )

#set( CMAKE_AUTOMOC ON)

#set( CMAKE_INCLUDE_CURRENT_DIR ON )

find_package( VTK REQUIRED )
find_package( Qt5Widgets )

include( ${VTK_USE_FILE} )


SET( PROJECT_SRCS 
    main.cpp
	viewimage.cpp
	viewimage.h
	mywidget.cpp
	mywidget.h
	viewallwidget.cpp
	viewallwidget.h
	)
	
SET( PROJECT_UIS 
	 viewimage.ui 
	 viewallwidget.ui
	 )

SET( PROJECTS_MOC_HDRS
     viewimage.h
	 mywidget.h
	 viewallwidget.h
	)

QT5_WRAP_UI( PROJECT_UIS_H ${PROJECT_UIS})
QT5_WRAP_CPP( PROJECT_MOC_SRCS ${PROJECTS_MOC_HDRS})

include_directories( ${PEOJECT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${VTK_DIR} ${Qt5Core_INCLUDE_DIRS} )

ADD_EXECUTABLE( viewImage ${PROJECT_SRCS} ${PROJECT_UIS_H} ${PROJECT_MOC_SRCS} )

TARGET_LINK_LIBRARIES( viewImage ${VTK_LIBRARIES} Qt5::Widgets )