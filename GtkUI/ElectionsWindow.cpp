#include "ElectionsWindow.hpp"
#include "PollingStation.hxx"
#include <Constituency.hxx>
#include <County.hxx>
#include <PollingCenter.hxx>
#include <Ward.hxx>
#include <giomm/liststore.h>
#include <gtkmm/label.h>
#include <gtkmm/multiselection.h>
#include <gtkmm/signallistitemfactory.h>
#include <gtkmm/treeexpander.h>
#include <format>

ElectionsWindow::ElectionsWindow() {

  set_child(m_scrolledwindow);

  m_scrolledwindow.set_policy(Gtk::PolicyType::AUTOMATIC,
                              Gtk::PolicyType::AUTOMATIC);
  m_scrolledwindow.set_expand();

  m_scrolledwindow.set_child(m_columnview);

  // create root model:
  auto root = create_model();

  // Set list model and selection model
  // passthrough must be false when Gtk::TreeExpander is used in the view

  m_refTreeListModel = Gtk::TreeListModel::create(
      root, sigc::mem_fun(*this, &ElectionsWindow::create_model),
      /*passthrough*/ false, /*autoexpand*/ false);

  auto selection_model = Gtk::MultiSelection::create(m_refTreeListModel);

  m_columnview.set_model(selection_model);
  m_columnview.add_css_class("data-table");

  m_columnview.set_reorderable(true);

  // Id Column
  auto factory = Gtk::SignalListItemFactory::create();
  factory->signal_setup().connect(
      sigc::mem_fun(*this, &ElectionsWindow::on_setup_id));
  factory->signal_bind().connect(
      sigc::mem_fun(*this, &ElectionsWindow::on_bind_id));
  auto column = Gtk::ColumnViewColumn::create("ID", factory);
  m_columnview.append_column(column);

  // Name Column
  factory = Gtk::SignalListItemFactory::create();
  factory->signal_setup().connect(
      sigc::mem_fun(*this, &ElectionsWindow::on_setup_name));
  factory->signal_bind().connect(
      sigc::mem_fun(*this, &ElectionsWindow::on_bind_name));
  column = Gtk::ColumnViewColumn::create("NAME", factory);
  m_columnview.append_column(column);
}

Glib::RefPtr<Gio::ListModel>
ElectionsWindow::create_model(const Glib::RefPtr<Glib::ObjectBase> &item) {
  auto col = std::dynamic_pointer_cast<ModelColumns>(item);
  auto result = Gio::ListStore<ModelColumns>::create();
  auto counties = m_repository.GetCounties();

  if (!col) {
    for (auto &county : counties) {
      result->append(ModelColumns::create(county.Id(), county.Name(),
                                          EntityTypeEnum::COUNTY));
    }
  } else {
    EntityTypeEnum mytype = col->EntityType();

    if (mytype == EntityTypeEnum::COUNTY) {
      const auto &county = counties.at(col->Id() - 1);
      for (const auto &weak_ptr : county.Constituencies()) {

        const auto constituency_ptr = weak_ptr.lock();
        assert(constituency_ptr);
        const auto &constituency = *constituency_ptr;
        result->append(ModelColumns::create(constituency.Id(),
                                            constituency.Name(),
                                            EntityTypeEnum::CONSTITUENCY));
      }
    }

    if (mytype == EntityTypeEnum::CONSTITUENCY) {
      const auto &constituency = m_repository.GetConstituency(col->Id());
      for (const auto &weak_ptr : constituency.Wards()) {

        const auto ward_ptr = weak_ptr.lock();
        assert(ward_ptr);
        const Ward &ward = *ward_ptr;
        result->append(
            ModelColumns::create(ward.Id(), ward.Name(), EntityTypeEnum::WARD));
      }
    }

    if (mytype == EntityTypeEnum::WARD) {
      const auto &ward = m_repository.GetWard(col->Id());
      for (const auto &weak_ptr : ward.PollingCenters()) {

        const auto pollingCenter_ptr = weak_ptr.lock();
        assert(pollingCenter_ptr);
        const PollingCenter &pollingCenter = *pollingCenter_ptr;
        result->append(ModelColumns::create(pollingCenter.Id(),
                                            pollingCenter.Name(),
                                            EntityTypeEnum::POLLING_CENTER));
      }
    }

    if (mytype == EntityTypeEnum::POLLING_CENTER) {
      const auto &pollingcenter = m_repository.GetPollingCenter(col->Id());
      for (const auto &weak_ptr : pollingcenter.PollingStations()) {

        const auto pollingStation_ptr = weak_ptr.lock();
        assert(pollingCenter_ptr);
        const PollingStation &pollingStation = *pollingStation_ptr;
        auto pollingstationname = std::format("{} {}", pollingStation.Name(), pollingStation.altId());
        result->append(ModelColumns::create(pollingStation.Id(),
                                            pollingstationname,
                                            EntityTypeEnum::POLLING_STATION));
      }
    }
  }

  return (result->get_n_items() > 0) ? result : Glib::RefPtr<Gio::ListModel>();
}

void ElectionsWindow::on_setup_id(
    const Glib::RefPtr<Gtk::ListItem> &list_item) {
  auto *expander = Gtk::make_managed<Gtk::TreeExpander>();
  auto *label = Gtk::make_managed<Gtk::Label>();
  label->set_halign(Gtk::Align::END);
  expander->set_child(*label);
  list_item->set_child(*expander);
}

void ElectionsWindow::on_setup_name(
    const Glib::RefPtr<Gtk::ListItem> &list_item) {
  list_item->set_child(*Gtk::make_managed<Gtk::Label>("", Gtk::Align::START));
}

void ElectionsWindow::on_bind_id(const Glib::RefPtr<Gtk::ListItem> &list_item) {
  auto row = std::dynamic_pointer_cast<Gtk::TreeListRow>(list_item->get_item());
  assert(row);
  auto col = std::dynamic_pointer_cast<ModelColumns>(row->get_item());
  assert(col);
  auto *expander = dynamic_cast<Gtk::TreeExpander *>(list_item->get_child());
  assert(expander);
  expander->set_list_row(row);
  auto *label = dynamic_cast<Gtk::Label *>(expander->get_child());
  assert(label);
  label->set_text(Glib::ustring::format(col->Id()));
}

void ElectionsWindow::on_bind_name(
    const Glib::RefPtr<Gtk::ListItem> &list_item) {
  auto row = std::dynamic_pointer_cast<Gtk::TreeListRow>(list_item->get_item());
  if (!row) {
    return;
  }
  auto col = std::dynamic_pointer_cast<ModelColumns>(row->get_item());
  if (!col) {
    return;
  }
  auto *label = dynamic_cast<Gtk::Label *>(list_item->get_child());
  if (!label) {
    return;
  }
  label->set_text(col->Name());
}
