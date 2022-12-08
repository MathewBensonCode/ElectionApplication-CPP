#include <memory>
#include <odb/database.hxx>
#include <odb/session.hxx>
#include <vector>
#include "database.hpp"

struct CountyInfo{
    std::string Name;
    unsigned int Id;
};

class Repository {
  odb::session m_session{};
  std::unique_ptr<odb::database> m_database = create_database();

public:
  void PrintCounties();
  std::vector<CountyInfo> GetCounties();
};
