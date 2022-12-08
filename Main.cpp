#include <ElectionsWindow.hpp>
#include <gtkmm/application.h>
#include <iostream>

int main(int argc, char **argv) {
  try {
    auto application =
        Gtk::Application::create("codes.mathewbenson.ElectionApplication");
    return application->make_window_and_run<ElectionsWindow>(argc, argv);
  } catch (std::exception &e) {
    std::cerr << e.what()<<'\n';
  }
}
