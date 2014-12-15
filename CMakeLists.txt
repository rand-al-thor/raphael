cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(raphael)

# Use PkgConfig to detect GTK+ headers and libraries
find_package(PkgConfig REQUIRED)
pkg_check_modules( GTK3 REQUIRED gtk+-3.0)
include_directories( ${GTK3_INCLUDE_DIRS} )
link_directories( ${GTK3_LIBRARY_DIRS} )

# User PkgConfig to detect GDK+ headers and libraries
pkg_check_modules( GDK3 REQUIRED gdk-pixbuf-2.0 )
include_directories( ${GDK3_INCLUDE_DIRS} )
link_directories( ${GDK3_LIBRARY_DIRS} )

set(CMAKE_C_DEBUG_FLAGS "-g")
set(CMAKE_CXX_DEBUG_FLAGS "-g")

set(CMAKE_CXX_FLAGS "-std=c++11")

# Unit test for Logging framework
add_executable( logger-tests
	logger-tests.cpp
)
target_link_libraries( logger-tests
	gtest_main
	gtest
	pthread
)

# Unit test for Raster class
add_executable( raster-tests
	raster-tests.cpp
)
target_link_libraries( raster-tests
	gtest_main
	gtest
	pthread
)

# BS test for gtk
add_executable (gtk-test
	gtk-test.cpp
)
target_link_libraries( gtk-test
	${GTK3_LIBRARIES}
)
