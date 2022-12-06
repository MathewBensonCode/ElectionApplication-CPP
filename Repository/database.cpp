#include "database.hpp"
#include <string>

std::unique_ptr<odb::database>
create_database()
{
  auto database = std::make_unique<odb::sqlite::database>(std::string{ "./Elections.db" });
  return database;
}
