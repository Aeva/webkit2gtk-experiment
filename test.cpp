#include <gtkmm.h>
#include <webkit2/webkit2.h>
#include <JavaScriptCore/JavaScript.h>
#include <iostream>


int main(int argc, char **argv) {
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "test");

  Gtk::Window window;
  window.set_default_size(1024, 768);

  auto web_ctx = webkit_web_context_get_default();
  auto module_path = g_build_filename(g_get_current_dir(),
                                      "modules/",
                                      NULL);
  std::cout << "MODULE LOAD PATH: " << module_path << "\n";
  webkit_web_context_set_web_extensions_directory(web_ctx, module_path);


  auto config = webkit_settings_new();
  webkit_settings_set_enable_webgl(config, true);
  webkit_settings_set_enable_developer_extras(config, true);
  webkit_settings_set_enable_write_console_messages_to_stdout(config, true);
  
  WebKitWebView* view = WEBKIT_WEB_VIEW(webkit_web_view_new_with_settings(config));
  window.add(*Glib::wrap(GTK_WIDGET(view)));
  // auto web_ctx = webkit_web_view_get_context(view);
  // webkit_web_context_set_web_extensions_directory(web_ctx, "./modules/");
    
  const char* load_url = "http://localhost:8000/demos/light";
  webkit_web_view_load_uri(view, load_url);
  
  window.show_all();
  app->run(window);
  exit(0);
  return 0;
}
