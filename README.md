# memory-driver-communication

# This is not a finished repository as of 11-02-23

Communicating between Kernel Driver and user mode process using memory access functions.

outline for process logic:

<pre>
usermode:  
|===================| 
| Usermode process  |
| ________ _________| 
| Ubuffer | Kbuffer | 
|===================| 

===============kerel boundary================
 

kernel: 
|===================| 
| kernel driver     |  
|MmCopyVirtualMemory| 
|===================| 
</pre>

Kernel driver would use MmCopyVirtualMemory to read and write to a usermode process. <br />
KBuffer->kernel driver <br />
UBuffer<-kernel driver <br />
