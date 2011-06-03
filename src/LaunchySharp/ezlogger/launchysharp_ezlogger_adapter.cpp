#include "Precompiled.h"
#include "launchysharp_ezlogger_adapter.h"

namespace LaunchySharpPlugin 
{

std::string getLogFileName()
{
	const char* tempPath = getenv("TEMP");
	if (tempPath) {
		return std::string(tempPath) + "/LaunchySharpPlugin.log";
	}
	else {
		return "LaunchySharpPlugin.log";
	}
}

};
