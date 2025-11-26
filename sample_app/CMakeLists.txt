cmake_minimum_required(VERSION 3.20)
project(simple_qt_app LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Export compile commands for clangd / language servers
# This ensures `compile_commands.json` is generated in the build dir.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "Export compile commands for clangd" FORCE)

# Create a symlink from the build `compile_commands.json` to the source root
# so tools that look in the project root (like some editors) can find it.
if(NOT EXISTS "${CMAKE_SOURCE_DIR}/compile_commands.json")
	execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink
		"${CMAKE_BINARY_DIR}/compile_commands.json"
		"${CMAKE_SOURCE_DIR}/compile_commands.json"
	)
endif()

find_package(Qt6 REQUIRED COMPONENTS Core)

add_executable(simple_qt_app src/main.cpp)
target_link_libraries(simple_qt_app PRIVATE Qt6::Core)

install(TARGETS simple_qt_app RUNTIME DESTINATION bin)
