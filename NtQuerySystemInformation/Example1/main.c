#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winternl.h>

//assumes little endian
void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i=size-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}

typedef ULONG
(WINAPI *tNTQSI) (
	SYSTEM_INFORMATION_CLASS SystemInformationClass,
	PVOID SystemInformation,
	ULONG SystemInformationLength,
	PULONG ReturnLength);  // ULONG *ReturnLength

int main(int argc, char *argv[]) {
	HMODULE ntdllHandle = GetModuleHandle("ntdll.dll");
	if (!ntdllHandle)
	{
		return EXIT_FAILURE;
	}
	
	tNTQSI fpQSI = (tNTQSI)GetProcAddress(ntdllHandle, "NtQuerySystemInformation");
	
	ULONG cbBuffer = sizeof(SYSTEM_BASIC_INFORMATION);
	PVOID pBuffer = NULL;
	HANDLE hHeap = GetProcessHeap();
	pBuffer = HeapAlloc(hHeap, HEAP_ZERO_MEMORY, cbBuffer);
	ULONG Status = fpQSI(SystemBasicInformation, pBuffer, cbBuffer, &cbBuffer);
	
    PSYSTEM_BASIC_INFORMATION infoP = NULL;
	infoP = (PSYSTEM_BASIC_INFORMATION)pBuffer;

    printf("MaximumIncrement: %d\n", infoP->MaximumIncrement);  // ULONG
    
	printf("PhysicalPageSize: %d\n", infoP->PhysicalPageSize);  // ULONG
    
	printf("NumberOfPhysicalPages: %d\n", infoP->NumberOfPhysicalPages);  // ULONG
    
	printf("LowestPhysicalPage: %#010x\n", infoP->LowestPhysicalPage);  // ULONG
    printf("HighestPhysicalPage: %#010x\n", infoP->HighestPhysicalPage);  // ULONG
    
	printf("AllocationGranularity: %d\n", infoP->AllocationGranularity);  // ULONG
    
	printf("LowestUserAddress: %#010x\n", infoP->LowestUserAddress);  // ULONG_PTR
    printf("LowestUserAddress: %lu\n", infoP->LowestUserAddress);  // ULONG_PTR
	
	printf("HighestUserAddress: %#010x\n", infoP->HighestUserAddress);  // ULONG_PTR
	printf("HighestUserAddress: %lu\n", infoP->HighestUserAddress);  // ULONG_PTR
	
	printf("ActiveProcessors:\n");
	printBits(sizeof(infoP->ActiveProcessors), &infoP->ActiveProcessors);  // ULONG_PTR
	
	printf("NumberOfProcessors: %d\n", infoP->NumberOfProcessors);  // CCHAR
	
	HeapFree(hHeap, 0, pBuffer);
	
	system("pause");
	return 0;
}
