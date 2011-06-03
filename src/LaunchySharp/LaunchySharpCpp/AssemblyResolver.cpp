#include "Precompiled.h"
#include "AssemblyResolver.h"

using namespace System::Reflection;
using namespace System::Runtime::InteropServices;

namespace LaunchySharpCpp
{

AssemblyResolver::AssemblyResolver( const char* pluginPathStr )
{
	System::String^ pluginPath = gcnew System::String(pluginPathStr);
	m_apiAssemblyPath = System::IO::Path::Combine(
		pluginPath, "Launchy#API.dll");

	System::AppDomain^ currentDomain = System::AppDomain::CurrentDomain;
	currentDomain->AssemblyResolve += gcnew System::ResolveEventHandler(
		this, &AssemblyResolver::AssemblyResolve);
}

Assembly^ AssemblyResolver::AssemblyResolve( System::Object^ sender, System::ResolveEventArgs^ args )
{
	const char* name = (const char*)(Marshal::StringToHGlobalAnsi(args->Name)).ToPointer();
	LOG_DEBUG("AssemblyResolve: %s", name);

	bool isOurApiAssembly = args->Name->StartsWith("Launchy#API");
	if (!isOurApiAssembly) {
		LOG_DEBUG("Not loading assembly, only Launchy#API can be resolved");
		return nullptr;
	}

	LOG_DEBUG("Loading Launchy#API.dll");
	Assembly^ assembly = Assembly::LoadFrom(m_apiAssemblyPath);

	return assembly;
}

}
