@ECHO OFF

cl.exe /nologo /Ox /MT /W0 /GS- /DNDEBUG /TcDLL_Injection.cpp /link /OUT:DLL_Injection.exe /SUBSYSTEM:CONSOLE /MACHINE:x64