#include <ntdef.h>
#include <ntifs.h>


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


NTSTATUS DriverEntry(
	_In_  struct _DRIVER_OBJECT* DriverObject,
	_In_  PUNICODE_STRING RegistryPath
)
{
	DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "Entered\n");

	//hardcoded, fix later
	PVOID KBufferAddr = (PVOID)0x000000541CCFF820;
	PVOID UBufferAddr = (PVOID)0x000000541CCFF824;
	int PID = 7004;

	int KBuffer;		//read
	int UBuffer = 55;	//write

	PEPROCESS Process; // our target process
	PsLookupProcessByProcessId(PID, &Process); //lookup the process by it's id;


	//read from usermode
	KeReadProcessMemory(Process, KBufferAddr, &KBuffer, sizeof(__int32));
	DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "(R) Value read: %d\n", KBuffer);

	////proves we are recviving from usermode
	//UBuffer = KBuffer + 1;

	//write to usermode
	KeWriteProcessMemory(Process, &UBuffer, UBufferAddr, sizeof(__int32));
	DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "(W) Value written: %d\n", UBuffer);


	return STATUS_SUCCESS;
}
