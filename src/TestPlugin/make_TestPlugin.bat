call "D:\Program Files\Microsoft Visual Studio 8\VC\vcvarsall.bat"
csc /t:library /reference:..\release\LaunchySharpAPI.dll TestPlugin.cs 
pause