#pragma once
#include "header.h"

VOID MyThreadFunction(PVOID StartContext) {
	UNREFERENCED_PARAMETER(StartContext);

	//hardcoded, fix later
	PVOID KBufferAddr = (PVOID)0x00000060964FFE20;
	PVOID UBufferAddr = (PVOID)0x00000060964FFE24;
	int PID = 16108;

	int KBuffer;		//read
	int UBuffer;		//write

	PEPROCESS Process; // our target process
	PsLookupProcessByProcessId(PID, &Process); //lookup the process by it's id;

	//used for debug
	int myNum = 1;
	while (TRUE) {
		SleepTime();
		myNum++;
		//DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "looping %d\n", myNum);

		//read from usermode
		KeReadProcessMemory(Process, KBufferAddr, &KBuffer, sizeof(__int32));
		DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "(R) Value read: %d\n", KBuffer);

		////proves we are recviving from usermode
		UBuffer = KBuffer + 1;

		//write to usermode
		KeWriteProcessMemory(Process, &UBuffer, UBufferAddr, sizeof(__int32));
		DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "(W) Value written: %d\n", UBuffer);

	}
}

