#include "database.h"
#include <string>

std::shared_ptr<odb::database>
create_database()
{
  auto database = std::make_unique<odb::sqlite::database>(std::string{ "./Elections.db" });
  return database;
}
