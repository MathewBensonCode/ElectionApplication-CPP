#include "ElectionsWindow.hpp"
#include <iostream>
#include <vector>

ElectionsWindow::ElectionsWindow() {
  m_refTreeStore = Gtk::TreeStore::create(m_Columns);

  auto counties = m_repository.GetCounties();

  for (auto &county : counties) {
    auto iter = m_refTreeStore->append();
    auto row = *iter;
    row[m_Columns.m_col_text] = county.Name;
    row[m_Columns.m_col_number] = static_cast<int>(county.Id);
  }

  set_child(m_scrolledwindow);

  m_scrolledwindow.set_policy(Gtk::PolicyType::AUTOMATIC,
                              Gtk::PolicyType::AUTOMATIC);
  m_scrolledwindow.set_expand();

  m_scrolledwindow.set_child(m_treeview);

  m_treeview.set_model(m_refTreeStore);

  m_treeview.append_column("Id", m_Columns.m_col_number);
  m_treeview.append_column("Name", m_Columns.m_col_text);
}
