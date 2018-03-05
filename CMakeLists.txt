cmake_minimum_required(VERSION 3.8)
project(OperatingSystemsProject1)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)
add_executable(OperatingSystemsProject1 ${SOURCE_FILES})

find_package(Boost 1.54.0 REQUIRED COMPONENTS system filesystem)
if (NOT Boost_FOUND)
    BUILD_ERROR("Could not find boost")
endif()

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})
target_link_libraries(OperatingSystemsProject1 ${Boost_LIBRARIES})