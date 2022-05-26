cmake_minimum_required(VERSION 3.7)

project(ProcessingPP)


set(CMAKE_CXX_STANDARD 17)
include_directories("./include")
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(SOURCES
    include/Processing.h
    include/Processing.cpp
)
set(LIBRARIES ${CONAN_LIBS})


include_directories(${SDL2_INCLUDE_DIRS})

add_executable(HanoyTower ${SOURCES} tests/main.cpp)
target_link_libraries(HanoyTower ${LIBRARIES})

add_executable(RunningBlock ${SOURCES} tests/test.cpp)
target_link_libraries(RunningBlock ${LIBRARIES})
