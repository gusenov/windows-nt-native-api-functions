#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winternl.h>

#define STATUS_INFO_LENGTH_MISMATCH 0xc0000004

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
	
    ULONG cbBuffer = 0;
    PVOID pBuffer = NULL;
    NTSTATUS Status = STATUS_INFO_LENGTH_MISMATCH;
    HANDLE hHeap = GetProcessHeap();
    
    if (fpQSI(SystemProcessInformation, pBuffer, cbBuffer, &cbBuffer) == STATUS_INFO_LENGTH_MISMATCH) {
    	if (cbBuffer) {
	        pBuffer = HeapAlloc(hHeap, HEAP_ZERO_MEMORY, cbBuffer);
	        if (pBuffer == NULL) {
	            return 0;
	        }
		}
	}
    

    Status = fpQSI(SystemProcessInformation, pBuffer, cbBuffer, &cbBuffer);
    if (!NT_SUCCESS(Status)) {
        HeapFree(hHeap, 0, pBuffer);
        return 0;
    }
    else {
        PSYSTEM_PROCESS_INFORMATION infoP = NULL;
        infoP = (PSYSTEM_PROCESS_INFORMATION)pBuffer;

        while (infoP) {
            printf("Process ID: %d\n", infoP->UniqueProcessId);
            printf("Inherited From ID: %d\n", infoP->InheritedFromUniqueProcessId);
            printf("Pagefile Usage: %d\n", infoP->VirtualMemoryCounters.PagefileUsage);
            printf("Working SetSize: %d\n ", infoP->VirtualMemoryCounters.WorkingSetSize);
            printf("PageFault Count: %d\n", infoP->VirtualMemoryCounters.PageFaultCount);
            printf("QuadPart (User): %d\n", ((double)infoP->UserTime.QuadPart) / 1e7);
            printf("QuadPart (Kernal): %d\n", ((double)infoP->KernelTime.QuadPart) / 1e7);
            printf("VirtualMemoryCounters.VirtualSize: %lu\n", (unsigned long)infoP->VirtualMemoryCounters.VirtualSize);
            printf("VirtualMemoryCounters.WorkingSetSize: %lu\n", (unsigned long)infoP->VirtualMemoryCounters.WorkingSetSize);

            switch (infoP->BasePriority){
            case 4:
                printf("Base Priority: %s\n", "Idle");
                break;
            case 8:
                printf("Base Priority: %s\n", "Normal");
                break;
            case 13:
                printf("Base Priority: %s\n", "High");
                break;
            case 24:
                printf("Base Priority: %s\n", "Realtime");
                break;
            }

            char pName[256];
            memset(pName, 0, sizeof(pName));
            WideCharToMultiByte(CP_ACP, 0, infoP->ImageName.Buffer, infoP->ImageName.Length, pName, sizeof(pName), NULL, NULL);
            printf("%s\n\n", pName);
            
            if (!infoP->NextEntryOffset) break;
            infoP = (PSYSTEM_PROCESS_INFORMATION)(((LPBYTE)infoP) + infoP->NextEntryOffset);

        }
        if (pBuffer) HeapFree(GetProcessHeap(), 0, pBuffer);
    }
	
	system("pause");
	return 0;
}
