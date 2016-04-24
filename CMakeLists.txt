cmake_minimum_required(VERSION 2.6)

project(Robotarium)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


find_package(ASSIMP REQUIRED)
if(ASSIMP_FOUND)
    include_directories(${ASSIMP_INCLUDE_DIR})
endif() 

find_package(OGRE)
find_package(Bullet)
include_directories(${BULLET_INCLUDE_DIR})
find_package (Boost COMPONENTS REQUIRED chrono thread)

set (Boost_USE_STATIC_LIBS OFF) # enable dynamic linking
set (Boost_USE_MULTITHREAD ON)  # enable multithreading

include_directories(src/)

add_subdirectory (src/common/)
add_subdirectory (src/core/)
add_subdirectory (src/graphic/)


add_executable(Robotarium src/main.cpp)

target_link_libraries(Robotarium RbmCommon)
target_link_libraries(Robotarium RbmCore)
target_link_libraries(Robotarium RbmGraphic)
target_link_libraries(Robotarium ${Boost_LIBRARIES})
target_link_libraries(Robotarium ${OGRE_LIBRARIES})
target_link_libraries(Robotarium ${ASSIMP_LIBRARIES})

#install(TARGETS robotarium RUNTIME DESTINATION bin)
