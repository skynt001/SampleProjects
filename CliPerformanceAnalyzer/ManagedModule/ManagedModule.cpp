
#include "stdafx.h"

#include "ManagedModule.h"

#include <math.h>


using namespace ManagedModule;

// global
UINT g_uCounter = 0;
double g_sqrtResult = 0.0;
double g_dotproductResult = 0.0;

NativeWrapperCli::NativeWrapperCli()
	: m_isDisposed(false)
{
}

NativeWrapperCli::~NativeWrapperCli()
{
	if (m_isDisposed)
		return;

	// TODO: managed 자원 해제

	this->!NativeWrapperCli();
	m_isDisposed = true;

}

NativeWrapperCli::!NativeWrapperCli()
{
	// TODO: unmanaged 자원 해제
}


void NativeWrapperCli::IncrementCounter()
{
	::NATIVE_IncrementCounter();	// Native Call
}

double NativeWrapperCli::CalculateSquareRoot(double value)
{
	return ::NATIVE_CalculateSquareRoot(value);	// Native Call
}

double NativeWrapperCli::DotProduct(array<double>^ arrValue1, array<double>^ arrValue2)
{
	// Pin to managed array of double
	pin_ptr<double> p1(&arrValue1[0]);
	pin_ptr<double> p2(&arrValue2[0]);

	return ::NATIVE_DotProduct(p1, p2);	// Native Call
}

void NativeWrapperCli::IncrementCounterCli(UINT testCount)
{
	for (UINT i = 1; i <= testCount; ++i)
		++g_uCounter;
}

double NativeWrapperCli::CalculateSquareRootCli(UINT testCount, double value)
{
	for (UINT i = 1; i <= testCount; ++i)
		g_sqrtResult += ::sqrt(value);
	
	return g_sqrtResult;
}

double NativeWrapperCli::DotProductCli(UINT testCount, array<double>^ arrValue1, array<double>^ arrValue2)
{
	for (UINT i = 1; i <= testCount; ++i)
		g_dotproductResult += arrValue1[0] * arrValue2[0] + arrValue1[1] * arrValue2[1] + arrValue1[2] * arrValue2[2];
	
	return g_dotproductResult;
}
