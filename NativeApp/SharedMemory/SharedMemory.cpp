// SharedMemory.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"


static float kVersion = 1.0f;

const int kImageSize = 1024 * 1024 * sizeof(float) * 3;
struct DeviceImage
{
    int index;
    bool isWriting;
    bool isReading;
    float data[kImageSize];
};



#pragma comment(linker, "/SECTION:.shared,RWS")
#pragma data_seg(".shared")
float imgData[kImageSize];
DeviceImage image;

int testValues[] = { 0, 0, 0, 0 };

#pragma data_seg()



bool ValidateVersion(float version)
{
    return version == kVersion;
}


float* GetBuffer(int index)
{
    if (index == 0)
    {
        return imgData;
    }
    else
    {
        return image.data;
    }
}

int GetTestValue(int index)
{
    if (index < 4)
    {
        return testValues[index];
    }
    return -1;
}

void SetTestValue(int index, int value)
{
    testValues[index] = value;
}