@ECHO OFF

cl.exe /nologo /Ox /MT /W0 /GS- /DNDEBUG /TcProcessInjection.cpp /link /OUT:ProcessInjection.exe /SUBSYSTEM:CONSOLE /MACHINE:x64