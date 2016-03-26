#include <webkit2/webkit-web-extension.h>
#include <JavaScriptCore/JavaScript.h>
#include <iostream>


//
//  Some basic c function to be exposed to the javascript environment
//
static JSValueRef some_method (JSContextRef context,
                               JSObjectRef function,
                               JSObjectRef thisObject,
                               size_t argumentCount,
                               const JSValueRef arguments[],
                               JSValueRef *exception)
{
  JSStringRef string = JSStringCreateWithUTF8CString("butts");
  return JSValueMakeString(context, string);
}




//
//  Boilerplate code / signal callback for attaching methods when a
//  new javascript context is created.
//
static void 
window_object_cleared_callback (WebKitScriptWorld *world, 
                                WebKitWebPage *web_page, 
                                WebKitFrame *frame, 
                                gpointer user_data)
{
  std::cout << "attempting to set up custom c function bindings\n";
  JSGlobalContextRef js_ctx;
  js_ctx = webkit_frame_get_javascript_context_for_script_world (frame, world);
  
  JSStringRef function_name = JSStringCreateWithUTF8CString("whatever");
  JSObjectRef boiler_plate = JSObjectMakeFunctionWithCallback(js_ctx,
                                                              function_name,
                                                              some_method);
  JSValueRef exception = 0;
  JSObjectRef global = JSContextGetGlobalObject(js_ctx);
  JSObjectSetProperty(js_ctx,
                      global,
                      JSStringCreateWithUTF8CString("myCFunction"),
                      boiler_plate,
                      kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly,
                      &exception);
  if (exception) {
    std::cout << "Argh! an exception!!!!\n";
  }
}




//
//  Extension initialization thing.
//
extern "C" G_MODULE_EXPORT void
webkit_web_extension_initialize (WebKitWebExtension *extension)
{
    std::cout << "EXTENSION INITIALIZED\n";
    
    g_signal_connect (webkit_script_world_get_default(),
                      "window-object-cleared", 
                      G_CALLBACK (window_object_cleared_callback), 
                      NULL);
}
