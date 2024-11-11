@ECHO OFF

cl.exe /nologo /Ox /MT /W0 /GS- /DNDEBUG /TcfunctionObfuscation.cpp /link /OUT:functionObfuscation.exe /SUBSYSTEM:CONSOLE /MACHINE:x64