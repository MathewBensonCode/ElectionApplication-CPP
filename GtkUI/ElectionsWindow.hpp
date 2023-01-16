#include <gtkmm/scrolledwindow.h>
#include <gtkmm/treemodelcolumn.h>
#include <gtkmm/treestore.h>
#include <gtkmm/treeview.h>
#include <gtkmm/window.h>
#include <repository.hpp>

struct ModelColumns : public Gtk::TreeModelColumnRecord {

  ModelColumns() {
    add(m_col_text);
    add(m_col_number);
  }

  [[nodiscard]] auto &TextColumn() const { return m_col_text; }
  [[nodiscard]] auto &NumberColumn() const { return m_col_number; }

private:
  Gtk::TreeModelColumn<Glib::ustring> m_col_text;
  Gtk::TreeModelColumn<int> m_col_number;
};

class ElectionsWindow : public Gtk::Window {
  ModelColumns m_Columns{};
  Repository m_repository{};
  Glib::RefPtr<Gtk::TreeStore> m_refTreeStore;
  Gtk::TreeView m_treeview{};
  Gtk::ScrolledWindow m_scrolledwindow{};

public:
  ElectionsWindow();
};
