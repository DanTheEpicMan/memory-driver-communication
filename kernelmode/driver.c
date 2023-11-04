#include "header.h"
#include "loop.c"

NTSTATUS DriverEntry(
	_In_ PDRIVER_OBJECT DriverObject,
	_In_ PUNICODE_STRING RegistryPath
) {
	UNREFERENCED_PARAMETER(DriverObject);
	UNREFERENCED_PARAMETER(RegistryPath);

	DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "entered\n");

	//makes handle
	HANDLE hThread;
	NTSTATUS status = PsCreateSystemThread(&hThread, THREAD_ALL_ACCESS, NULL, NULL, NULL, MyThreadFunction, NULL);
	if (!NT_SUCCESS(status)) { //checks if handle was created
		DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "failed\n");
		return status;
	}

	//closes the handle
	ObReferenceObjectByHandle(hThread, THREAD_ALL_ACCESS, NULL, KernelMode, &hThread, NULL);
	ZwClose(hThread);

	return STATUS_SUCCESS;
}



