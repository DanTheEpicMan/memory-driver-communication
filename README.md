# memory-driver-communication

# Project is not closed to finished as of 11-02-23

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

# Why use this communication method?
When manually mapping a kernel driver with a program like KDMapper, the cache of the driver is erased, leaving IOCTL communication impossible and causing the computer to crash whenever an attempt is made to use IOCTL on a driver that was manually mapped with KDMapper.
