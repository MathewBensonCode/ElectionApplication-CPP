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
