# memory-driver-communication

# This is not a finished repository as of 11-02-23

Communicating between Kernel Driver and user mode process using memory access functions.

outline for process logic:

usermode:
|===================|
| Usermode process  |
| ________ _________|
| Ubuffer | Kbuffer |
|===================|

---------------------------------------------------
kernel:
|===================|
| kernel driver     |
|MmCopyVirtualMemory|
|===================|

Kernel driver would use MmCopyVirtualMemory to read and write to a usermode process.
KBuffer->kernel driver
UBuffer<-kernel driver
