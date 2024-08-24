add_library(ElectionRepository)

target_sources(
  ElectionRepository
  PRIVATE repository.cpp database.cpp
  PRIVATE FILE_SET repository_headers TYPE HEADERS FILES repository.hpp database.hpp)

target_include_directories(
    ElectionRepository PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(ElectionRepository PUBLIC ElectionCountLib ElectionOdb)
