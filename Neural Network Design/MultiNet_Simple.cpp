#include "StdAfx.h"
#include "MultiNet_Simple.h"

#include "MultilayerNetwork.h"

namespace NeuralNetwork
{
	MultiNet_Simple::MultiNet_Simple(void)/*:_myNeurons(myNeuron)*/
	{
		_obj=-1;
		_iterCount=0;
	}


	MultiNet_Simple::~MultiNet_Simple(void)
	{
	}

	void MultiNet_Simple::Train( const vector<shared_ptr<Network::MyData>> mydata,train_MultiNetwork& myTrain )
	{
		++_iterCount;
		myTrain.SetNeuronState(false);
		myTrain.ClearDeviations();
		myTrain=for_each(mydata.begin(),mydata.end(),myTrain);
		_deviations=myTrain.GetSampleDeviations();
	}

}

