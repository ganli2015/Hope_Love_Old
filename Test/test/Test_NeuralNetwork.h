#pragma once
class Test_NeuralNetwork
{
public:
	Test_NeuralNetwork(void);
	~Test_NeuralNetwork(void);

	static void RunTest(); 

private:
	static void RunTest_PerceptronNetwork();
	static void RunTest_ADALINENetwork();
	static void RunTest_MultiNetwork();
	static void RunTest_CompetitiveNetwork();
};

