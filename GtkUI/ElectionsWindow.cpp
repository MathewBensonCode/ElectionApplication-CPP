#include "ElectionsWindow.hpp"
#include "Constituency.hxx"
#include "PollingCenter.hxx"
#include "PollingStation.hxx"
#include "Ward.hxx"
#include <iostream>
#include <vector>
#include <sstream>

ElectionsWindow::ElectionsWindow() {
  m_refTreeStore = Gtk::TreeStore::create(m_Columns);

  auto counties = m_repository.GetCounties();

  for (auto &county : counties) {
    auto county_row = *(m_refTreeStore->append());
    county_row[m_Columns.TextColumn()] = county.Name();
    county_row[m_Columns.NumberColumn()] = static_cast<int>(county.Id());

    for (const auto &constituency : county.Constituencies()) {
      auto constituency_row = *(m_refTreeStore->append(county_row.children()));
      auto myconstituency = constituency.lock();
      constituency_row[m_Columns.TextColumn()] = myconstituency->Name();
      constituency_row[m_Columns.NumberColumn()] =
          static_cast<int>(myconstituency->Id());

      for (const auto &ward : myconstituency->Wards()) {
        auto ward_row = *(m_refTreeStore->append(constituency_row.children()));
        auto myward = ward.lock();
        ward_row[m_Columns.TextColumn()] = myward->Name();
        ward_row[m_Columns.NumberColumn()] = static_cast<int>(myward->Id());

        for (const auto &pollingcenter : myward->PollingCenters()) {
          auto pollingcenter_row =
              *(m_refTreeStore->append(ward_row.children()));
          auto mypollingcenter = pollingcenter.lock();
          pollingcenter_row[m_Columns.TextColumn()] = mypollingcenter->Name();
          pollingcenter_row[m_Columns.NumberColumn()] =
              static_cast<int>(mypollingcenter->Id());

          for (const auto &pollingstation :
               mypollingcenter->PollingStations()) {
            auto pollingstation_row =
                *(m_refTreeStore->append(pollingcenter_row.children()));
            auto mypollingstation = pollingstation.lock();
            std::stringstream str_strm{}; 
            str_strm << mypollingstation->Name()<<' '<<mypollingstation->altId();
            pollingstation_row[m_Columns.TextColumn()] = str_strm.str();
            pollingstation_row[m_Columns.NumberColumn()] =
                static_cast<int>(mypollingstation->Id());
          }
        }
      }
    }
  }

  set_child(m_scrolledwindow);

  m_scrolledwindow.set_policy(Gtk::PolicyType::AUTOMATIC,
                              Gtk::PolicyType::AUTOMATIC);
  m_scrolledwindow.set_expand();

  m_scrolledwindow.set_child(m_treeview);

  m_treeview.set_model(m_refTreeStore);

  m_treeview.append_column("Id", m_Columns.NumberColumn());
  m_treeview.append_column("Name", m_Columns.TextColumn());
}
