
#pragma once

#include "..\NativeModule\NativeModule.h"


using namespace System;

namespace ManagedModule {

	public ref class NativeWrapperCli
	{
	public:
		NativeWrapperCli();
		~NativeWrapperCli();
		!NativeWrapperCli();

		// CLI proxy
		void IncrementCounter();
		double CalculateSquareRoot(double value);
		double DotProduct(array<double>^ arrValue1, array<double>^ arrValue2);
		
		// CLI logic
		void IncrementCounterCli(UINT testCount);
		double CalculateSquareRootCli(UINT testCount, double value);
		double DotProductCli(UINT testCount, array<double>^ arrValue1, array<double>^ arrValue2);
	
	private:
		bool m_isDisposed;

	};

}
