@ECHO OFF

cl.exe /nologo /Ox /MT /W0 /GS- /DNDEBUG /TcXOR.cpp /link /OUT:XOR.exe /SUBSYSTEM:CONSOLE /MACHINE:x64