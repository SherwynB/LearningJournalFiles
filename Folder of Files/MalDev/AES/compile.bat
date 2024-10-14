@ECHO OFF

cl.exe /nologo /Ox /MT /W0 /GS- /DNDEBUG /TcAES.cpp /link /OUT:AES.exe /SUBSYSTEM:CONSOLE /MACHINE:x64