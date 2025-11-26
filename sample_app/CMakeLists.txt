cmake_minimum_required(VERSION 3.20)
project(simple_qt_app LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core)

add_executable(simple_qt_app src/main.cpp)
target_link_libraries(simple_qt_app PRIVATE Qt6::Core)

install(TARGETS simple_qt_app RUNTIME DESTINATION bin)
