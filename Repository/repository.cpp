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

std::vector<CountyInfo> Repository::GetCounties() {

  odb::transaction transaction(m_database->begin());

  auto results = m_database->query(odb::query<County>());

  const auto num_of_counties{48};

  std::vector<CountyInfo> counties{num_of_counties};

  std::size_t countyindex{0};

  for (const auto &county : results) {
      counties[countyindex].Name = county.Name();
      counties[countyindex].Id = county.Id();
      countyindex++;
    }

  transaction.commit();

  return counties;
}
