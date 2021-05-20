
#pragma once


#ifdef NATIVEMODULE_EXPORTS
#define NATIVE_API extern "C" __declspec(dllexport) 
#else
#define NATIVE_API extern "C" __declspec(dllimport)
#endif


#include <Windows.h>

// ++
NATIVE_API void __stdcall NATIVE_IncrementCounter();

// sqrt
NATIVE_API double __stdcall NATIVE_CalculateSquareRoot(double dValue);

// array marshalling
NATIVE_API double __stdcall NATIVE_DotProduct(double arrValue1[], double arrValue2[]);

// Run test
NATIVE_API void __stdcall NATIVE_Test1(UINT nTestCount);
NATIVE_API void __stdcall NATIVE_Test2(UINT nTestCount);
NATIVE_API void __stdcall NATIVE_Test3(UINT nTestCount);
