#pragma once

namespace LaunchySharpCpp
{
	//! Allows to place Launchy#API.dll in the same directory as LaunchySharpPlugin.dll
	ref class AssemblyResolver
	{
	public:
		AssemblyResolver(const char* pluginPath);

	private:
		System::Reflection::Assembly^ AssemblyResolve(
			System::Object^ sender, System::ResolveEventArgs^ args);

		System::String^ m_apiAssemblyPath;
	};

}
