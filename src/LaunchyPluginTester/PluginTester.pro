 TEMPLATE = app
 CONFIG       += qt console plugin
 
 TARGET		   = PluginTester
 SOURCES       = plugin_tester.cpp
 
 win32 {
     CONFIG -= embed_manifest_dll
}

