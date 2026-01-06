cmake_minimum_required(VERSION 3.20)
project(simple_qt_app LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Request the strict C++ standard (no GNU extensions -> produces -std=c++26)
set(CMAKE_CXX_EXTENSIONS OFF)

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

# Enable experimental reflection flag when using Clang
# Ensure Clang uses libc++ headers and runtime only

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  target_compile_options(simple_qt_app PRIVATE -freflection-latest)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  # prefer the devtoolchain's libc++ headers if available
  if(EXISTS "/opt/clang-p2996/include/c++/v1")
    target_include_directories(simple_qt_app PRIVATE "/opt/clang-p2996/include/c++/v1")
	target_include_directories(simple_qt_app PRIVATE "/opt/clang-p2996/include/x86_64-unknown-linux-gnu/c++/v1")
  endif()
  # add runtime/linker flags for the toolchain libc++ location
  if(EXISTS "/opt/clang-p2996/lib/x86_64-unknown-linux-gnu")
    target_link_options(simple_qt_app PRIVATE
      "-L/opt/clang-p2996/lib/x86_64-unknown-linux-gnu"
      "-Wl,-rpath,/opt/clang-p2996/lib/x86_64-unknown-linux-gnu"
      "-lc++" "-lc++abi")
  endif()
  # Prefer the bundled libc++ implementation and avoid picking up the
  # system libstdc++ headers which would conflict with libc++ headers.
  if(EXISTS "/opt/clang-p2996/include/c++/v1")
    target_compile_options(simple_qt_app PRIVATE -stdlib=libc++ -nostdinc++)
    target_include_directories(simple_qt_app PRIVATE /opt/clang-p2996/include/c++/v1)
  endif()

  # Add linker flags for the bundled libc++ runtime (handle arch-specific path)
  if(EXISTS "/opt/clang-p2996/lib/x86_64-unknown-linux-gnu")
    target_link_options(simple_qt_app PRIVATE
      -L/opt/clang-p2996/lib/x86_64-unknown-linux-gnu
      -Wl,-rpath,/opt/clang-p2996/lib/x86_64-unknown-linux-gnu
      -lc++ -lc++abi)
  elseif(EXISTS "/opt/clang-p2996/lib")
    target_link_options(simple_qt_app PRIVATE
      -L/opt/clang-p2996/lib
      -Wl,-rpath,/opt/clang-p2996/lib
      -lc++ -lc++abi)
  endif()
endif()

target_link_libraries(simple_qt_app PRIVATE Qt6::Core)

install(TARGETS simple_qt_app RUNTIME DESTINATION bin)
