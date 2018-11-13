cmake_minimum_required( VERSION 2.8.9 )

project( fibonacci_memoized )

include_directories( $CMAKE_SOURCE_DIR )

add_executable( fibonacci_memoized fibonacci_memoized.c )

target_link_libraries( fibonacci_memoized )

