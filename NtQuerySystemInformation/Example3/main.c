#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winternl.h>

// typedef unsigned long ULONG;

/*
#if !defined(_M_IX86)
 typedef unsigned __int64 ULONGLONG;
#else
 typedef double ULONGLONG;
#endif
*/

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
	
	ULONG cbBuffer = sizeof(SYSTEM_PERFORMANCE_INFORMATION);
	printf("cbBuffer = %d\n", cbBuffer);
	HANDLE hHeap = GetProcessHeap();
	PVOID pBuffer = HeapAlloc(hHeap, HEAP_ZERO_MEMORY, cbBuffer);
	ULONG Status = fpQSI(SystemPerformanceInformation, pBuffer, cbBuffer, &cbBuffer);
	
    PSYSTEM_PERFORMANCE_INFORMATION infoP = NULL;
	infoP = (PSYSTEM_PERFORMANCE_INFORMATION)pBuffer;

	// printf("IdleProcessTime = %lu\n", infoP->IdleProcessTime);  // LARGE_INTEGER
	// printf("IoReadTransferCount = %lu\n", infoP->IoReadTransferCount);  // LARGE_INTEGER
	// printf("IoWriteTransferCount = %lu\n", infoP->IoWriteTransferCount);  // LARGE_INTEGER
	// printf("IoOtherTransferCount = %lu\n", infoP->IoOtherTransferCount);  // LARGE_INTEGER
	// printf("IoReadOperationCount = %lu\n", infoP->IoReadOperationCount);  // ULONG
	// printf("IoWriteOperationCount = %lu\n", infoP->IoWriteOperationCount);  // ULONG
	// printf("IoOtherOperationCount = %lu\n", infoP->IoOtherOperationCount);  // ULONG
	printf("AvailablePages = %lu\n", infoP->AvailablePages);  // ULONG
	printf("CommittedPages = %lu\n", infoP->TotalCommittedPages);  // ULONG
	// printf("CommitLimit = %lu\n", infoP->CommitLimit);  // ULONG
	// printf("PeakCommitment = %lu\n", infoP->PeakCommitment);  // ULONG
	// printf("PageFaultCount = %lu\n", infoP->PageFaultCount);  // ULONG
	// printf("CopyOnWriteCount = %lu\n", infoP->CopyOnWriteCount);  // ULONG
	// printf("TransitionCount = %lu\n", infoP->TransitionCount);  // ULONG
	// printf("CacheTransitionCount = %lu\n", infoP->CacheTransitionCount);  // ULONG
	// printf("DemandZeroCount = %lu\n", infoP->DemandZeroCount);  // ULONG
	// printf("PageReadCount = %lu\n", infoP->PageReadCount);  // ULONG
	// printf("PageReadIoCount = %lu\n", infoP->PageReadIoCount);  // ULONG
	// printf("CacheReadCount = %lu\n", infoP->CacheReadCount);  // ULONG
	// printf("CacheIoCount = %lu\n", infoP->CacheIoCount);  // ULONG
	// printf("DirtyPagesWriteCount = %lu\n", infoP->DirtyPagesWriteCount);  // ULONG
	// printf("DirtyWriteIoCount = %lu\n", infoP->DirtyWriteIoCount);  // ULONG
	// printf("MappedPagesWriteCount = %lu\n", infoP->MappedPagesWriteCount);  // ULONG
	// printf("MappedWriteIoCount = %lu\n", infoP->MappedWriteIoCount);  // ULONG
	printf("PagedPoolPages = %lu\n", infoP->PagedPoolUsage);  // ULONG
	printf("NonPagedPoolPages = %lu\n", infoP->NonPagedPoolUsage);  // ULONG
	// printf("PagedPoolAllocs = %lu\n", infoP->PagedPoolAllocs);  // ULONG
	// printf("PagedPoolFrees = %lu\n", infoP->PagedPoolFrees);  // ULONG
	// printf("NonPagedPoolAllocs = %lu\n", infoP->NonPagedPoolAllocs);  // ULONG
	// printf("NonPagedPoolFrees = %lu\n", infoP->NonPagedPoolFrees);  // ULONG
	printf("FreeSystemPtes = %lu\n", infoP->TotalFreeSystemPtes);  // ULONG
	// printf("ResidentSystemCodePage = %lu\n", infoP->ResidentSystemCodePage);  // ULONG
	// printf("TotalSystemDriverPages = %lu\n", infoP->TotalSystemDriverPages);  // ULONG
	// printf("TotalSystemCodePages = %lu\n", infoP->TotalSystemCodePages);  // ULONG
	// printf("NonPagedPoolLookasideHits = %lu\n", infoP->NonPagedPoolLookasideHits);  // ULONG
	// printf("PagedPoolLookasideHits = %lu\n", infoP->PagedPoolLookasideHits);  // ULONG
	// printf("AvailablePagedPoolPages = %lu\n", infoP->AvailablePagedPoolPages);  // ULONG
	// printf("ResidentSystemCachePage = %lu\n", infoP->ResidentSystemCachePage);  // ULONG
	// printf("ResidentPagedPoolPage = %lu\n", infoP->ResidentPagedPoolPage);  // ULONG
	// printf("ResidentSystemDriverPage = %lu\n", infoP->ResidentSystemDriverPage);  // ULONG
	// printf("CcFastReadNoWait = %lu\n", infoP->CcFastReadNoWait);  // ULONG
	// printf("CcFastReadWait = %lu\n", infoP->CcFastReadWait);  // ULONG
	// printf("CcFastReadResourceMiss = %lu\n", infoP->CcFastReadResourceMiss);  // ULONG
	// printf("CcFastReadNotPossible = %lu\n", infoP->CcFastReadNotPossible);  // ULONG
	// printf("CcFastMdlReadNoWait = %lu\n", infoP->CcFastMdlReadNoWait);  // ULONG
	// printf("CcFastMdlReadWait = %lu\n", infoP->CcFastMdlReadWait);  // ULONG
	// printf("CcFastMdlReadResourceMiss = %lu\n", infoP->CcFastMdlReadResourceMiss);  // ULONG
	// printf("CcFastMdlReadNotPossible = %lu\n", infoP->CcFastMdlReadNotPossible);  // ULONG
	// printf("CcMapDataNoWait = %lu\n", infoP->CcMapDataNoWait);  // ULONG
	// printf("CcMapDataWait = %lu\n", infoP->CcMapDataWait);  // ULONG
	// printf("CcMapDataNoWaitMiss = %lu\n", infoP->CcMapDataNoWaitMiss);  // ULONG
	// printf("CcMapDataWaitMiss = %lu\n", infoP->CcMapDataWaitMiss);  // ULONG
	// printf("CcPinMappedDataCount = %lu\n", infoP->CcPinMappedDataCount);  // ULONG
	// printf("CcPinReadNoWait = %lu\n", infoP->CcPinReadNoWait);  // ULONG
	// printf("CcPinReadWait = %lu\n", infoP->CcPinReadWait);  // ULONG
	// printf("CcPinReadNoWaitMiss = %lu\n", infoP->CcPinReadNoWaitMiss);  // ULONG
	// printf("CcPinReadWaitMiss = %lu\n", infoP->CcPinReadWaitMiss);  // ULONG
	// printf("CcCopyReadNoWait = %lu\n", infoP->CcCopyReadNoWait);  // ULONG
	// printf("CcCopyReadWait = %lu\n", infoP->CcCopyReadWait);  // ULONG
	// printf("CcCopyReadNoWaitMiss = %lu\n", infoP->CcCopyReadNoWaitMiss);  // ULONG
	// printf("CcCopyReadWaitMiss = %lu\n", infoP->CcCopyReadWaitMiss);  // ULONG
	// printf("CcMdlReadNoWait = %lu\n", infoP->CcMdlReadNoWait);  // ULONG
	// printf("CcMdlReadWait = %lu\n", infoP->CcMdlReadWait);  // ULONG
	// printf("CcMdlReadNoWaitMiss = %lu\n", infoP->CcMdlReadNoWaitMiss);  // ULONG
	// printf("CcMdlReadWaitMiss = %lu\n", infoP->CcMdlReadWaitMiss);  // ULONG
	// printf("CcReadAheadIos = %lu\n", infoP->CcReadAheadIos);  // ULONG
	// printf("CcLazyWriteIos = %lu\n", infoP->CcLazyWriteIos);  // ULONG
	// printf("CcLazyWritePages = %lu\n", infoP->CcLazyWritePages);  // ULONG
	// printf("CcDataFlushes = %lu\n", infoP->CcDataFlushes);  // ULONG
	// printf("CcDataPages = %lu\n", infoP->CcDataPages);  // ULONG
	// printf("ContextSwitches = %lu\n", infoP->ContextSwitches);  // ULONG
	// printf("FirstLevelTbFills = %lu\n", infoP->FirstLevelTbFills);  // ULONG
	// printf("SecondLevelTbFills = %lu\n", infoP->SecondLevelTbFills);  // ULONG
	// printf("SystemCalls = %lu\n", infoP->SystemCalls);  // ULONG
	// printf("CcTotalDirtyPages = %lu\n", infoP->CcTotalDirtyPages);  // ULONGLONG
	// printf("CcDirtyPageThreshold = %lu\n", infoP->CcDirtyPageThreshold);  // ULONGLONG
	// printf("ResidentAvailablePages = %lu\n", infoP->ResidentAvailablePages);  // LONGLONG
	// printf("SharedCommittedPages = %lu\n", infoP->SharedCommittedPages);  // ULONGLONG

	HeapFree(hHeap, 0, pBuffer);

	system("pause");
	return 0;
}
