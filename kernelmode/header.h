#pragma once
#include <ntdef.h>
#include <ntifs.h>
#include <ntddk.h>
#include <ntddk.h>


#define THREAD_POOL_TAG 'MyTh'

typedef unsigned long DWORD, * PDWORD, * LPDWORD;

DRIVER_INITIALIZE DriverEntry;
#pragma alloc_text(INIT, DriverEntry)

// API function from ntoskrnl.exe which we use
// to copy memory to and from an user process.
NTSTATUS NTAPI MmCopyVirtualMemory
(
	PEPROCESS SourceProcess,
	PVOID SourceAddress,
	PEPROCESS TargetProcess,
	PVOID TargetAddress,
	SIZE_T BufferSize,
	KPROCESSOR_MODE PreviousMode,
	PSIZE_T ReturnSize
);

NTKERNELAPI
NTSTATUS
PsLookupProcessByProcessId(
	_In_ HANDLE ProcessId,
	_Outptr_ PEPROCESS* Process
);


NTSTATUS KeReadProcessMemory(PEPROCESS Process, PVOID SourceAddress, PVOID TargetAddress, SIZE_T Size)
{
	// Since the process we are reading from is the input process, we set
	// the source process variable for that.
	PEPROCESS SourceProcess = Process;
	// Since the "process" we read the output to is this driver
	// we set the target process as the current module.
	PEPROCESS TargetProcess = PsGetCurrentProcess();
	SIZE_T Result;
	if (NT_SUCCESS(MmCopyVirtualMemory(SourceProcess, SourceAddress, TargetProcess, TargetAddress, Size, KernelMode, &Result)))
		return STATUS_SUCCESS; // operation was successful
	else
		return STATUS_ACCESS_DENIED;
}
NTSTATUS KeWriteProcessMemory(PEPROCESS Process, PVOID SourceAddress, PVOID TargetAddress, SIZE_T Size)
{       // This write func is just like the read func, except vice versa.

	// Since the process writing from is our module
	// change the source process variable for that.
	PEPROCESS SourceProcess = PsGetCurrentProcess();
	// Since the process we write to is the input process
	// we set the target process as the argument
	PEPROCESS TargetProcess = Process;
	SIZE_T Result;

	if (NT_SUCCESS(MmCopyVirtualMemory(SourceProcess, SourceAddress, TargetProcess, TargetAddress, Size, KernelMode, &Result)))
		return STATUS_SUCCESS; // operation was successful
	else
		return STATUS_ACCESS_DENIED;

}


void SleepTime()
{
	LARGE_INTEGER interval;
	interval.QuadPart = (1000 /*miliseconds*/ * -10000 /*keep as is*/); // 1 = 10 Nanoseconds 
	KeDelayExecutionThread(KernelMode, FALSE, &interval);
}

//edit if you meed to get through more
struct KBufferStruct
{
	int x;
};

//edit if you meed to pass through more
struct UBufferStruct
{
	int x;
};