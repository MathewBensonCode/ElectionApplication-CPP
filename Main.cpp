#include <iostream>

#include "database.h"

#include "County.hxx"
#include "County_odb.hpp"

#include "Constituency.hxx"
#include "Constituency_odb.hpp"

int main() {

  auto database = create_database();

  try {
    odb::session session;

    odb::transaction transaction(database->begin());

    auto results = database->query(odb::query<County>());

    for (const auto &county: results)
    {
        std::cout<<"County Name: " << county.Name() <<'\n';

        for(const auto& constituency: county.Constituencies()){
            auto constituency_lock = constituency.lock();
            std::cout<<"\tConstituency Name: "<< constituency_lock->Name()<<'\n';
        }
    }
    
    transaction.commit();
  }

  catch (std::exception &e) {
    std::cerr << e.what();
    return 1;
  }

  return 0;
}
