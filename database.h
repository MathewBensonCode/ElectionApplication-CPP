#include <odb/database.hxx> 
#include <odb/sqlite/database.hxx> 
#include <memory> 
#include <string>
#include <iostream>

std::unique_ptr<odb::database> 
create_database() {
     auto database = std::make_unique<odb::sqlite::database>(std::string{"../Elections.db"}); 
     return database;
}
