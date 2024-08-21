#include "database.hpp"
#include <string>

std::unique_ptr<odb::database>
create_database(const std::string &dbname)
{
  auto database = std::make_unique<odb::sqlite::database>(dbname);
  return database;
}
