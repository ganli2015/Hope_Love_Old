#pragma once
#include "PublicHeader.h"

namespace NeuralNetwork
{
	class iDataArray;
	class MultilayerNetwork;
}


class Test_NeuralNetworkDesign
{
public:
	Test_NeuralNetworkDesign(void);
	~Test_NeuralNetworkDesign(void);

	static void RunTest();

private:
	static void RunTest_PerceptronNetwork();
	static void RunTest_ADALINENetwork();
	static void RunTest_MultiNetwork();
	static void RunTest_CompetitiveNetwork();

	static void RunTest_Connectivity();

	static void RunTest_MOBP();
	static void RunTest_MOBP_SearchingParameter();

	static double ComputeDeviation(const shared_ptr<NeuralNetwork::iDataArray> array1,const shared_ptr<NeuralNetwork::iDataArray> array2);

	static shared_ptr<NeuralNetwork::iDataArray> ToDataArray(const double val[], const int n);
};

