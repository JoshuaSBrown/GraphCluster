cmake_minimum_required (VERSION 2.6)
project (test_GraphNode)

# Boost libraries
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED OFF)
set(Boost_USE_STATIC_RUNTIME OFF)

set(CMAKE_CXX_COMPILER /usr/local/bin/g++)
#project (test_tuple_graph)
# Set compiler flags
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wreorder -std=c++14")

find_package(Boost REQUIRED COMPONENTS system)

add_library(EdgeClass ../CPP_EdgeClass/EdgeClass.cpp)
add_library(BranchClass ../CPP_BranchClass/BranchClass.cpp)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    include_directories("${PROJECT_SOURCE_DIR}")
    include_directories("${PROJECT_SOURCE_DIR}/EdgeClass")
    include_directories("${PROJECT_SOURCE_DIR}/BranchClass")

    add_executable(test_GraphCluster test_GraphCluster.cpp)
    #add_executable(test_tuple_graph test_tuple_graph.cpp)

    target_link_libraries(test_GraphCluster ${Boost_LIBRARIES})
    target_link_libraries(test_GraphCluster EdgeClass)
    target_link_libraries(test_GraphCluster BranchClass)
endif()
