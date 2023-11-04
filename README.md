# memory-driver-communication

# This Project is semi-operational

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
<br />
This driver is loaded with KDMapper and then creates a thread that then lives on and lets main finish.

# Why use this communication method?
When manually mapping a kernel driver with a program like KDMapper, the cache of the driver is erased, leaving IOCTL communication impossible and causing the computer to crash whenever an attempt is made to use IOCTL on a driver that was manually mapped with KDMapper.

# ToDo
Get rid of the hardcoded values for the address and the PID or make the program retive these hardcoded files in a different manor that just hardcoding them
