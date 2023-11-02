# memory-driver-communication

# This is not a finished repository as of 11-02-23

Communicating between Kernel Driver and user mode process using memory access functions.

outline for process logic:

usermode: \n
|===================| \n
| Usermode process  | \n
| ________ _________| \n
| Ubuffer | Kbuffer | \n
|===================| \n

---------------------------------------------------
\n 
kernel: \n
|===================| \n
| kernel driver     | \n 
|MmCopyVirtualMemory| \n 
|===================| \n
\n
Kernel driver would use MmCopyVirtualMemory to read and write to a usermode process. \n
KBuffer->kernel driver \n
UBuffer<-kernel driver \n
