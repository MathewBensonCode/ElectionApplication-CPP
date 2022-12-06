cmake_minimum_required(VERSION 3.20...3.24)

project(ElectionsCount CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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

set(ElectionCount_Sources
    County.cpp
    Constituency.cpp
    Ward.cpp
    PollingCenter.cpp
    PollingStation.cpp
    ResultsForm34A.cpp
    Candidate.cpp
    CandidateResult.cpp)

set(ElectionCount_Headers
    County.hxx
    Constituency.hxx
    Ward.hxx
    PollingCenter.hxx
    PollingStation.hxx
    ResultsForm34A.hxx
    Candidate.hxx
    CandidateResult.hxx
    votes_view.hxx)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules")

find_package(ODB REQUIRED COMPONENTS sqlite)
include(${ODB_USE_FILE})

odb_compile(
  ElectionCount_Odb_Sources
  FILES
  ${ElectionCount_Headers}
  DB
  sqlite
  GENERATE_QUERY
  GENERATE_SESSION
  STANDARD
  c++20)

add_library(ElectionCountLib ${ElectionCount_Sources})
target_include_directories(ElectionCountLib
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(ElectionCountLib PUBLIC project_options project_warnings)

add_library(ElectionOdb ${ElectionCount_Odb_Sources})

target_compile_definitions(ElectionOdb PUBLIC DATABASE_SQLITE)

target_include_directories(ElectionOdb PUBLIC ${ODB_INCLUDE_DIRS}
                                              ${ODB_COMPILE_OUTPUT_DIR})
add_executable(ElectionCount Main.cpp database.cpp)

target_link_libraries(ElectionCount PRIVATE ElectionCountLib ElectionOdb
                                            ${ODB_LIBRARIES})

file(CREATE_LINK ${CMAKE_BINARY_DIR}/compile_commands.json
     ${CMAKE_SOURCE_DIR}/compile_commands.json COPY_ON_ERROR SYMBOLIC)

file(CREATE_LINK ${CMAKE_BINARY_DIR}/ElectionCount
     ${CMAKE_SOURCE_DIR}/ElectionCount SYMBOLIC)

file(COPY_FILE ${CMAKE_SOURCE_DIR}/Elections.db ${CMAKE_BINARY_DIR}/Elections.db
     ONLY_IF_DIFFERENT)
