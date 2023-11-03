#include <iostream>
#include <Windows.h>

int main()
{
    //Buffer to be passed to kernel
    int KBuffer = 100;
    //BUffer written to by kernel
    int UBuffer = 200;

    //memory address of both of these buffers
    const auto KBufferAddr = &KBuffer;
    const auto UBufferAddr = &UBuffer;

    //prints out PID of this process
    DWORD pid = GetCurrentProcessId();
    std::cout << "PID: " << pid << std::endl;

    while (true) 
    {
        //prints out the address of these buffers to terminal
        std::cout << "KBuffer Address: " << KBufferAddr << std::endl;
        std::cout << "UBuffer Address: " << UBufferAddr << std::endl;

        //allows us to change the KBuffer to send new values to driver
        int response;
        std::cout << "Input new value for KBuffer (0 to keep the same): ";
        std::cin >> response;
        if (response != 0)
        {
            response = KBuffer;
        }

    }

    
}
