@ECHO OFF

cl.exe /nologo /Ox /MT /W0 /GS- /DNDEBUG /ThreadContextInjection.cpp /link /OUT:ThreadContextInjection.exe /SUBSYSTEM:CONSOLE /MACHINE:x64
del *.obj