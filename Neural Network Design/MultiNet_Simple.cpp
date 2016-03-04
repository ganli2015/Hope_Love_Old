#include "StdAfx.h"
#include "MultiNet_Simple.h"

#include "MultilayerNetwork.h"

namespace NeuralNetwork
{
	MultiNet_Simple::MultiNet_Simple(void)/*:_myNeurons(myNeuron)*/
	{
		
	}


	MultiNet_Simple::~MultiNet_Simple(void)
	{
	}

	void MultiNet_Simple::Train( const vector<shared_ptr<Network::MyData>> mydata,train_MultiNetwork& myTrain )
	{
		myTrain=for_each(mydata.begin(),mydata.end(),myTrain);
	}

}

