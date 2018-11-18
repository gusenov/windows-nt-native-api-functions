#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winternl.h>

typedef NTSTATUS (NTAPI *NtAllocVirtualMemoryFunc) (
	HANDLE ProcessHandle, 
	PVOID *BaseAddress, 
	ULONG_PTR ZeroBits, 
	PSIZE_T RegionSize, 
	ULONG AllocationType, 
	ULONG Protect);

typedef NTSTATUS (NTAPI *NtFreeVirtualMemoryFunc) (
	HANDLE ProcessHandle, 
	PVOID *BaseAddress, 
	PSIZE_T RegionSize, 
	ULONG FreeType);

#define TARGET_PID 2656

int main(int argc, char *argv[]) {
	
	HMODULE ntdllHandle = GetModuleHandle("ntdll.dll");
	if (!ntdllHandle)
		return EXIT_FAILURE;
	
	NtAllocVirtualMemoryFunc NtAllocateVirtualMemory = (NtAllocVirtualMemoryFunc)GetProcAddress(ntdllHandle, "NtAllocateVirtualMemory");
	NtFreeVirtualMemoryFunc NtFreeVirtualMemory = (NtFreeVirtualMemoryFunc)GetProcAddress(ntdllHandle, "NtFreeVirtualMemory");
	
	HANDLE hProc = OpenProcess(
		PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_QUERY_INFORMATION | SYNCHRONIZE, 
		FALSE, 
		TARGET_PID);
		
	PVOID pMem = 0;
	SIZE_T memSize	= 100 * 1024 * 1024; 
		
	NTSTATUS status = NtAllocateVirtualMemory(
		hProc,  // Handle to Process Object opened with PROCESS_VM_OPERATION access.
		// A handle for the process for which the mapping should be done. 
		// Use the NtCurrentProcess macro, defined in Ntddk.h, to specify the current process.
		
		&pMem,  // If not zero, system tries to allocate virtual memory block on this virtual address. 
		// If BaseAddress is zero, system use first free virtual location.
		// A pointer to a variable that will receive the base address of the allocated region of pages. 
		// If the initial value of this parameter is non-NULL, the region is allocated starting at the specified virtual address rounded down to the next host page size address boundary. 
		// If the initial value of this parameter is NULL, the operating system will determine where to allocate the region.
		
		0,  // The number of high-order address bits that must be zero in the base address of the section view. 
		// Used only when the operating system determines where to allocate the region, as when BaseAddress is NULL. 
		// Note that when ZeroBits is larger than 32, it becomes a bitmask.
		
		&memSize, // A pointer to a variable that will receive the actual size, in bytes, of the allocated region of pages. 
		// The initial value of this parameter specifies the size, in bytes, of the region and is rounded up to the next host page size boundary. 
		// *RegionSize cannot be zero on input.
		
		MEM_COMMIT | MEM_RESERVE,  // Can be MEM_RESERVE or MEM_COMMIT.
		// A bitmask containing flags that specify the type of allocation to be performed.
		
		PAGE_EXECUTE_READ);  // One or combination of PAGE_*** attributes.
		// A bitmask containing page protection flags that specify the protection desired for the committed region of pages.
		
	if (NT_SUCCESS(status)) {
		printf("Succeeded!\n");
		system("pause");
		memSize = 0;
		status = NtFreeVirtualMemory(hProc, &pMem, &memSize, MEM_RELEASE);
		printf("NT status: 0x%08x\n", status);
	} else {
		printf("Failed!\nError code:  0x%08x (0x%08x)\n", status, GetLastError());
	}

	system("pause");
	return 0;
}

