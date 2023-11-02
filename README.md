# memory-driver-communication

# This is not a finished repository as of 11-02-23

Communicating between Kernel Driver and user mode process using memory access functions.

outline for process logic:

usermode:  <br />
|===================| <br />
| Usermode process  | <br />
| ________ _________| <br />
| Ubuffer | Kbuffer | <br />
|===================| <br /> 
 <br />
===============kerel boundary================
 <br />
<br />
kernel: <br />
|===================| <br />
| kernel driver     | <br /> 
|MmCopyVirtualMemory| <br /> 
|===================| <br />
<br />
Kernel driver would use MmCopyVirtualMemory to read and write to a usermode process. <br />
KBuffer->kernel driver <br />
UBuffer<-kernel driver <br />
