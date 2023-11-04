#include <iostream>
#include <Windows.h>

//edit if you need to pass through more
struct KBufferStruct
{
    int x;
};

//edit if you meed to get through more
struct UBufferStruct
{
    int x;
};

int main()
{
    //Buffer to be passed to kernel
    KBufferStruct KBuffer;
    KBuffer.x = 1234;

    //BUffer written to by kernel
    UBufferStruct UBuffer;
    UBuffer.x = 4321;

    //memory address of both of these buffers
    const auto KBufferAddr = &KBuffer;
    const auto UBufferAddr = &UBuffer;

    //prints out PID of this process as well as addresses of KBuffer and UBuffer
    DWORD pid = GetCurrentProcessId();
    std::cout << "PID: " << pid << std::endl;
    std::cout << "KBuffer Address: " << KBufferAddr << std::endl;
    std::cout << "UBuffer Address: " << UBufferAddr << std::endl;

    while (true) 
    {
        //prints out the value of these buffers to terminal
        std::cout << "KBuffer Address: " << KBuffer.x << std::endl;
        std::cout << "UBuffer Address: " << UBuffer.x << std::endl;

        //allows us to change the KBuffer to send new values to driver
        int response;
        std::cout << "Input new value for KBuffer (0 to keep the same): ";
        std::cin >> response;
        if (response != 0)
        {
            KBuffer.x = response;
        }

    }

    
}

