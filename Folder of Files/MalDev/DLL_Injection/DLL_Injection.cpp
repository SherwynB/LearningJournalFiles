#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tlhelp32.h>

int SearchProcess(const char *processName)
{
	HANDLE hSnapshot;
	PROCESSENTRY32 processStruct;
	
	int pid=0;
	
	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == hSnapshot)
		return 0;
		
	processStruct.dwSize = sizeof(PROCESSENTRY32);
	
	if(!Process32First(hSnapshot, &processStruct))
	{
		CloseHandle(hSnapshot);
		return 0;
		
	}
	
	while(Process32Next(hSnapshot, &processStruct))
	{
		if(lstrcmpiA(processName, processStruct.szExeFile) == 0)
		{
			pid = processStruct.th32ProcessID;
			break;
		}
	}
	
	CloseHandle(hSnapshot);
	return pid;
}

int main(int argc, char *argv[])
{
	HANDLE hProcess;
	PVOID pRemoteProcAllocMem;
	PTHREAD_START_ROUTINE pLoadLibrary = NULL;
	//fix
	char DLLPath[] = "MyDLL.dll";
	char processToInject[] = "explorer.exe";
	int pid = 0;
	
	pid = SearchProcess(processToInject);
	if(pid == 0)
	{
		printf("Process not Found");
		return -1;
	}
	
	printf("PID: [ %d ]\nInjecting...", pid);
	
	pLoadLibrary = (PTHREAD_START_ROUTINE) GetProcAddress( GetModuleHandle("Kernel32.dll"), "LoadLibraryA");
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, (DWORD)(pid));
	
	if (hProcess != NULL) {
		pRemoteProcAllocMem = VirtualAllocEx(hProcess, NULL, sizeof(DLLPath), MEM_COMMIT, PAGE_READWRITE);	
	
		WriteProcessMemory(hProcess, pRemoteProcAllocMem, (LPVOID) DLLPath, sizeof(DLLPath), NULL);

		CreateRemoteThread(hProcess, NULL, 0, pLoadLibrary, pRemoteProcAllocMem, 0, NULL);
		printf("Allocated Memory addr = %p\n", pRemoteProcAllocMem);

		CloseHandle(hProcess); 
	}
	else {
		printf("OpenProcess failed.\n");
		return -2;
	}
	
}


