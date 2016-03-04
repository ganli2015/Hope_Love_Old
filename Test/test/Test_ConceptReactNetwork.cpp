#include "StdAfx.h"
#include "Test_ConceptReactNetwork.h"

#include "Vector.h"
#include "iMatrix.h"
#include "Neuron.h"
#include "TransferFunctions.h"
#include "Network.h"
#include "Perceptron.h"
#include "ADALINE.h"
#include "MultilayerNetwork.h"
#include "CompetitiveNetwork.h"
#include "Neuron_compet.h"

using namespace NeuralNetwork;

vector<string> Test_ConceptReactNetwork::_basis;

Test_ConceptReactNetwork::Test_ConceptReactNetwork(void)
{
}


Test_ConceptReactNetwork::~Test_ConceptReactNetwork(void)
{
}

void Test_ConceptReactNetwork::RunTest()
{
	Init();


}

void Test_ConceptReactNetwork::Init()
{
	string baseFile="E:\\Artificial Intelligence\\Project\\Hope_Love\\Mind\\HopeLove\\BaseConceptsString.txt";

	ifstream in(baseFile);
	_basis.clear();
	while(!in.eof())
	{
		string base;
		in>>base;
		_basis.push_back(base);
	}
}

shared_ptr<NeuralNetwork::iDataArray> Test_ConceptReactNetwork::PairToArray( const vector<string>& conceptChain )
{
	vector<double> resVec(_basis.size(),0);
	for (unsigned int i=0;i<conceptChain.size();++i)
	{
		vector<string>::const_iterator it=find(_basis.begin(),_basis.end(),conceptChain[i]);
		if(it==_basis.end())
		{
			return NULL;
		}
		int index=distance(_basis.cbegin(),it);
		resVec[index]=i+1;
	}

	shared_ptr<iDataArray> res(new DataArray(resVec));
	return res;
}
