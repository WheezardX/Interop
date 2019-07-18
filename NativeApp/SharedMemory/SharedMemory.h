#pragma once


#ifdef SHAREDMEMORY_EXPORTS
#define EXPERIMENTS_API __declspec(dllexport)
#else
#define EXPERIMENTS_API __declspec(dllimport)
#endif


extern "C" EXPERIMENTS_API bool ValidateVersion(float version);

extern "C" EXPERIMENTS_API float* GetBuffer(int index);
extern "C" EXPERIMENTS_API int GetTestValue(int index);

extern "C" EXPERIMENTS_API void SetTestValue(int index, int value);
