call "D:\Program Files\Microsoft Visual Studio 8\VC\vcvarsall.bat" x86
call ../set_environment.bat
qmake
nmake Release