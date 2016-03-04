#pragma once
#include "InOut.h"

namespace NeuralNetwork
{
	class iDataArray;
	class TestClass
	{
	public:
		TestClass(void);
		~TestClass(void);

		static void RunTest();

	private:
		static void RunTest_PerceptronNetwork();
		static void RunTest_ADALINENetwork();
		static void RunTest_MultiNetwork();
		static void RunTest_CompetitiveNetwork();

		static void RunTest_Connectivity();

		static double ComputeDeviation(const shared_ptr<iDataArray> array1,const shared_ptr<iDataArray> array2);

		static shared_ptr<iDataArray> ToDataArray(const double val[], const int n);
	};
}


