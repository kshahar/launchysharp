#include <QApplication>
#include <QLibrary>
#include <QDir>
#include <QPluginLoader>
#include <QGlobal.h>
#include <cstdio>

static const int TEST_FAILURE=0;
static const int TEST_SUCCESS=1;

static void ExitHandler();
static bool g_normalExit(false);

int main(int argc, char* argv[])
{
    atexit(ExitHandler);

    qWarning("Begining tester");
    QApplication app(argc, argv);

    if (argc != 2) {
        qWarning("Usage: PluginTester name_of_plugin.dll");
        return TEST_FAILURE;
    }
    QString fileName = argv[1];

    QDir pluginsDir = QDir::current();
    pluginsDir.cd("plugins");

    if (!QLibrary::isLibrary(fileName)) {
        qWarning("%s is not a library", fileName);
        
    }
   
    const QString pluginFilePath = pluginsDir.absoluteFilePath(fileName);
    qWarning("Plugin file name is %s", (const char*)pluginFilePath.toUtf8());
    
    QPluginLoader loader(pluginFilePath);
    
    qWarning("Loading plugin");
    loader.load();
    
    qWarning("Testing plugin");
    QObject *plugin = loader.instance();

    g_normalExit = true;
    if (!plugin) {
        qWarning("Loaded plugin is NULL");
        qWarning("Reported error: %s", loader.errorString());
        return TEST_FAILURE;
    }
    else {
        qWarning("Plugin loaded!");
        return TEST_SUCCESS;
    }
}

static void ExitHandler()
{
    if ( !g_normalExit ) {
        printf("Abnormal exit!\n");
    }
    printf("Preparing for exit...\n");
}