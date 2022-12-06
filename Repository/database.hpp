#include <odb/database.hxx>
#include <odb/sqlite/database.hxx>
#include <memory>

std::unique_ptr<odb::database>
create_database();

