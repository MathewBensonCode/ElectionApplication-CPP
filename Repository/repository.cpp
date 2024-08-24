#include "repository.hpp"
#include "County_odb.hpp"
#include "Constituency_odb.hpp"
#include "Ward.hxx"
#include "Ward_odb.hpp"
#include "PollingCenter_odb.hpp"
#include <memory>
#include <odb/database.hxx>
#include <odb/result.hxx>
#include <odb/sqlite/database.hxx>

Repository::Repository(const std::string &dbname)
    : m_database(std::make_unique<odb::sqlite::database>(
          odb::sqlite::database(dbname))) {}

std::vector<County> Repository::GetCounties() {

  odb::transaction transaction(m_database->begin());

  auto results = m_database->query(odb::query<County>());

  std::vector<County> counties{};

  const size_t number_of_counties{48};

  counties.reserve(number_of_counties);

  for (const auto &county : results) {
    counties.push_back(county);
  }

  transaction.commit();

  return counties;
}

Constituency Repository::GetConstituency(const unsigned int constituencyid) {

  odb::transaction transaction(m_database->begin());

  Constituency constituency;

  m_database->load(constituencyid, constituency);

  transaction.commit();

  return constituency;
}

Ward Repository::GetWard(const unsigned int wardid){

  odb::transaction transaction(m_database->begin());

  Ward ward;

  m_database->load(wardid, ward);

  transaction.commit();

  return ward;
}

PollingCenter Repository::GetPollingCenter(const unsigned int pollingcenterid){
    odb::transaction transaction(m_database->begin());
    
    PollingCenter pollingCenter;

    m_database->load(pollingcenterid, pollingCenter);

    transaction.commit();

    return pollingCenter;
}
