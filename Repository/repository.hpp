#include <memory>
#include <odb/database.hxx>
#include <odb/session.hxx>
#include <vector>
#include "County.hxx"
#include "Constituency.hxx"
#include "PollingCenter.hxx"
#include "database.hpp"

class Repository {
  odb::session m_session;
  std::unique_ptr<odb::database> m_database;

public:
  explicit Repository(const std::string&);
  void PrintCounties();
  std::vector<County> GetCounties();
  Constituency GetConstituency(unsigned int);
  Ward GetWard(unsigned int);
  PollingCenter GetPollingCenter(unsigned int);
};
