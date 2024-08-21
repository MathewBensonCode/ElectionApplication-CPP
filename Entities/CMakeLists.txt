set(ElectionCount_Sources
    src/County.cpp
    src/Constituency.cpp
    src/Ward.cpp
    src/PollingCenter.cpp
    src/PollingStation.cpp
    src/ResultsForm34A.cpp
    src/Candidate.cpp
    src/CandidateResult.cpp)

set(ElectionCount_Headers
    include/County.hxx
    include/Constituency.hxx
    include/Ward.hxx
    include/PollingCenter.hxx
    include/PollingStation.hxx
    include/ResultsForm34A.hxx
    include/Candidate.hxx
    include/CandidateResult.hxx
    include/votes_view.hxx)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules")

set(PKG_CONFIG_ARGN "--with-path=/home/benson/.local/lib/pkgconfig")

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

add_library(ElectionCountLib)

target_sources(ElectionCountLib PRIVATE ${ElectionCount_Sources})

target_include_directories(ElectionCountLib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" ${ODB_INCLUDE_DIRS})

target_link_libraries(ElectionCountLib PUBLIC project_options project_warnings ${ODB_LIBRARIES})

add_library(ElectionOdb ${ElectionCount_Odb_Sources})

target_compile_definitions(ElectionOdb PUBLIC DATABASE_SQLITE)

target_include_directories(ElectionOdb PUBLIC ${ODB_INCLUDE_DIRS} ${ODB_COMPILE_OUTPUT_DIR}
                                              ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(ElectionOdb PUBLIC ${ODB_LIBRARIES})
