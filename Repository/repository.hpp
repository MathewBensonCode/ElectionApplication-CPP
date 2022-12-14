#include <memory>
#include <odb/database.hxx>
#include <odb/session.hxx>
#include <vector>
#include "County.hxx"
#include "database.hpp"

class Repository {
  odb::session m_session{};
  std::unique_ptr<odb::database> m_database = create_database();

public:
  void PrintCounties();
  std::vector<County> GetCounties();
};
