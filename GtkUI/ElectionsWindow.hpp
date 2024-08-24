#include <gtkmm/scrolledwindow.h>
#include <gtkmm/treelistmodel.h>
#include <gtkmm/columnview.h>
#include <gtkmm/window.h>
#include <gtkmm/listitem.h>
#include <repository.hpp>
#include <utility>

class ElectionsWindow : public Gtk::Window {
  Gtk::ColumnView m_columnview;
  Gtk::ScrolledWindow m_scrolledwindow;
  Glib::RefPtr<Gtk::TreeListModel> m_refTreeListModel;
  Repository m_repository{"Elections.db"};

protected:
  //Signal handlers:
  void on_setup_id(const Glib::RefPtr<Gtk::ListItem>&);
  void on_setup_name(const Glib::RefPtr<Gtk::ListItem>&);
  void on_bind_id(const Glib::RefPtr<Gtk::ListItem>&);
  void on_bind_name(const Glib::RefPtr<Gtk::ListItem>&);

  enum class EntityTypeEnum{ 
      COUNTY,
      CONSTITUENCY,
      WARD,
      POLLING_CENTER,
      POLLING_STATION
  };


  Glib::RefPtr<Gio::ListModel> create_model(
          const Glib::RefPtr<Glib::ObjectBase>& item = {});

  class ModelColumns : public Glib::Object{
    Glib::ustring name;
    unsigned entityid;
    
  EntityTypeEnum entitytype;

  protected:
    ModelColumns(unsigned myid, Glib::ustring myname, EntityTypeEnum mytype)
        : name(std::move(myname)), entityid(myid), entitytype(mytype) {}

  public:
    static Glib::RefPtr<ModelColumns> create(unsigned entityid,
                                             const Glib::ustring &name, EntityTypeEnum entitytype) {
      return Glib::make_refptr_for_instance(new ModelColumns(entityid, name, entitytype));
    }

    [[nodiscard]] const auto &Name() const { return name; }
    [[nodiscard]] const auto &Id() const { return entityid; }
    [[nodiscard]] const auto &EntityType() const { return entitytype; }
  };

public:
  ElectionsWindow();
};
