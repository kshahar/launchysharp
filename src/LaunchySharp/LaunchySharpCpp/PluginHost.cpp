#include "Precompiled.h"
#include "LaunchySharpCpp/PluginHost.h"
#include "LaunchySharpCpp/CatItemFactory.h"

namespace LaunchySharpCpp
{

PluginHost::PluginHost()
{
	m_catItemFactory = gcnew CatItemFactory();
}

LaunchySharp::ICatItemFactory^ PluginHost::catItemFactory()
{
	return m_catItemFactory;
}

}