find_package(PkgConfig REQUIRED)
pkg_check_modules(
  GTKMM
  REQUIRED
  IMPORTED_TARGET
  gtkmm-4.0)

add_library(GtkUI)
target_sources(GtkUI PRIVATE ElectionsWindow.cpp)
target_include_directories(GtkUI PUBLIC ElectionRepository PkgConfig::GTKMM)
target_link_libraries(GtkUI PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} PkgConfig::GTKMM ElectionRepository)
