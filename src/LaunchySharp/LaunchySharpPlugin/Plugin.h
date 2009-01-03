#include "Launchy/plugin_interface.h"
#include "Launchy/plugin_info.h"
#include <QtCore/QList>

/** Entry point to LaunchySharp.
	This is the first code that is executed by Launchy
*/
namespace LaunchySharpPlugin 
{
	class Plugin : public QObject, public PluginInterface
	{
		Q_OBJECT
		Q_INTERFACES(PluginInterface)

	public:
		/** Interface for Launchy */
		//@{
		Plugin();
		~Plugin();
		virtual int msg(int msgId, void* wParam = NULL, void* lParam = NULL); 
		//@}

	private:
		void init();
		void getID(uint* pId);
		void getName(QString* pName);
		void loadPlugins(QList<PluginInfo>* additionalPlugins);
	};

}