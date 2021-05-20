// NativeModule.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
//

#include "stdafx.h"

#include "NativeModule.h"

#include <math.h>
#include <tchar.h>

// global
UINT g_uCounter = 0;
double g_sqrtResult = 0.0;
double g_dotproductResult = 0.0;

NATIVE_API void __stdcall NATIVE_IncrementCounter()
{
	++g_uCounter;
}


NATIVE_API double __stdcall NATIVE_CalculateSquareRoot(double dValue)
{
	g_sqrtResult += ::sqrt(dValue);
	return g_sqrtResult;
}


NATIVE_API double __stdcall NATIVE_DotProduct(double arrVale1[], double arrVale2[])
{
	g_dotproductResult += arrVale1[0] * arrVale2[0] + arrVale1[1] * arrVale2[1] + arrVale1[2] * arrVale2[2];
	return g_dotproductResult;
}


NATIVE_API void __stdcall NATIVE_Test1(UINT nTestCount)
{
	for (UINT i = 1; i <= nTestCount; ++i)
		NATIVE_IncrementCounter();
}


NATIVE_API void __stdcall NATIVE_Test2(UINT nTestCount)
{
	for (UINT i = 1; i <= nTestCount; ++i)
		double result = NATIVE_CalculateSquareRoot((double)i);
}


NATIVE_API void __stdcall NATIVE_Test3(UINT nTestCount)
{
	for (UINT i = 1; i <= nTestCount; ++i)
	{
		double arrVale1[3] = { (double)i, (double)i, (double)i };
		double arrVale2[3] = { (double)i, (double)i, (double)i };
		double result = NATIVE_DotProduct(arrVale1, arrVale2);
	}
}
