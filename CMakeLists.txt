cmake_minimum_required(VERSION 3.14)

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

set(CMAKE_BUILD_TYPE Release)

project(ElectionsCount CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules")

find_package(ODB REQUIRED COMPONENTS sqlite)
include(${ODB_USE_FILE})

set(ElectionCount_Sources
	Main.cpp
	database.h
   )

set(ElectionCount_Headers
	County.hxx
	Constituency.hxx
	Ward.hxx
	PollingCenter.hxx
	PollingStation.hxx
	ResultsForm34A.hxx
	Candidate.hxx
	CandidateResult.hxx
)

odb_compile(ElectionCount_Sources FILES ${ElectionCount_Headers} DB sqlite GENERATE_QUERY GENERATE_SESSION STANDARD c++17) 

add_executable(ElectionCount 
	${ElectionCount_Sources}
	)
set_property(TARGET ElectionCount PROPERTY CXXSTANDARD 17)

target_link_libraries(ElectionCount 
	PRIVATE
		${ODB_LIBRARIES})

target_include_directories(ElectionCount
	PRIVATE
		${ODB_INCLUDE_DIRS}
		${ODB_COMPILE_OUTPUT_DIR})

target_compile_definitions(ElectionCount
	PRIVATE
		DATABASE_SQLITE)
