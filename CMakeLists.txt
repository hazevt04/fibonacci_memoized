cmake_minimum_required( VERSION 2.8.9 )

project( fibonacci_memoized )

add_definitions(-std=c++11 )

include_directories( "include" )

option(DO_GPROF "Whether or not to compile and link for use with gprof for profiling" OFF)

if(DO_GPROF) 
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
   set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
   set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg")
endif()


set(SRCS
   "src/utils.cpp"
   "src/fibonacci_memoized.cpp"
)

add_executable( fibonacci_memoized "${SRCS}" )

#target_link_libraries( fibonacci_memoized m )

