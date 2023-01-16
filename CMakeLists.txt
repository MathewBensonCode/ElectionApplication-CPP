cmake_minimum_required(VERSION 3.20...3.24)

project(ElectionsCount CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/StandardProjectSettings.cmake)
include(cmake/PreventInSourceBuilds.cmake)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  option(ENABLE_BUILD_WITH_TIME_TRACE
         "Enable -ftime-trace to generate time tracing .json files on clang"
         OFF)
  if(ENABLE_BUILD_WITH_TIME_TRACE)
    target_compile_options(project_options INTERFACE -ftime-trace)
  endif()
endif()

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)

# enable cache system
include(cmake/Cache.cmake)

# Add linker configuration
include(cmake/Linker.cmake)
configure_linker(project_options)

# standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# sanitizer options if supported by compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

# enable doxygen
include(cmake/Doxygen.cmake)
enable_doxygen()

# allow for static analysis options
include(cmake/StaticAnalyzers.cmake)

set(CMAKE_BUILD_TYPE RelWithDebInfo)

add_subdirectory(Entities)

add_subdirectory(Repository)

add_subdirectory(GtkUI)

add_executable(ElectionCount Main.cpp)

target_include_directories(ElectionCount PRIVATE GtkUI)

target_link_libraries(ElectionCount PRIVATE GtkUI)

file(CREATE_LINK ${CMAKE_BINARY_DIR}/compile_commands.json
     ${CMAKE_SOURCE_DIR}/compile_commands.json COPY_ON_ERROR SYMBOLIC)

file(CREATE_LINK ${CMAKE_BINARY_DIR}/ElectionCount
     ${CMAKE_SOURCE_DIR}/ElectionCount SYMBOLIC)

file(COPY_FILE ${CMAKE_SOURCE_DIR}/Elections.db
     ${CMAKE_BINARY_DIR}/Elections.db ONLY_IF_DIFFERENT)
