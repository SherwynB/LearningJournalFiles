@ECHO OFF

cl.exe /O2 /D_USRDLL /D_WINDLL MyDLL.cpp MyDLL.def /MT /link /DLL /OUT:MyDLL.dll