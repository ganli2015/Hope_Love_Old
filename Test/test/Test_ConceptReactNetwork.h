#pragma once
#include "stdafx.h"

namespace NeuralNetwork
{
	class iDataArray;
}

class Test_ConceptReactNetwork
{
	static vector<string> _basis;

public:
	Test_ConceptReactNetwork(void);
	~Test_ConceptReactNetwork(void);

	static void RunTest(); 

private:
	static void Init();

	static shared_ptr<NeuralNetwork::iDataArray> PairToArray(const vector<string>& conceptChain);
};

