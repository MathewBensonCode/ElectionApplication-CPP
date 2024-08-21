#include <memory>
#include <odb/database.hxx>
#include <odb/sqlite/database.hxx>

std::unique_ptr<odb::database> create_database();
