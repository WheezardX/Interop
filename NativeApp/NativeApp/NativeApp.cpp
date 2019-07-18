// NativeApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <windows.h>
#include <thread>

#define FUNC_PTR(T) T F_##T = (T)GetProcAddress(dllLib, #T); 

typedef  bool(__stdcall * ValidateVersion)(float version);
typedef  float*(__stdcall * GetBuffer)(int index);
typedef  int(__stdcall * GetTestValue)(int index);


int main()
{
    std::cout << "Hello World!\n"; 

    HINSTANCE dllLib = LoadLibrary(TEXT("SharedMemory.dll"));
    if (dllLib == nullptr)
    {
        return -1;
    }

    FUNC_PTR(ValidateVersion);
    FUNC_PTR(GetBuffer);
    FUNC_PTR(GetTestValue);


    int sentinel = F_GetTestValue(0);
    int loopCount = 0;
    while (sentinel == 0)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(30));

        int bufferIndex = F_GetTestValue(1);
        float* buffer = F_GetBuffer(bufferIndex);
        for (int index = 0; index < 100; ++index)
        {
            buffer[index] = loopCount + index;
        }

        loopCount++;
        sentinel = F_GetTestValue(0);
    }

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
