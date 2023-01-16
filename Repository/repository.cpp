#include "repository.hpp"
#include "Constituency.hxx"
#include "County_odb.hpp"
#include <iostream>

void Repository::PrintCounties() {

  odb::transaction transaction(m_database->begin());

  auto results = m_database->query(odb::query<County>());

  for (const auto &county : results) {
    std::cout << "County Name: " << county.Name() << '\n';

    for (const auto &constituency : county.Constituencies()) {
      auto constituency_lock = constituency.lock();
      std::cout << "\tConstituency Name: " << constituency_lock->Name() << '\n';
    }
  }

  transaction.commit();
}

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
