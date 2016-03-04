#pragma once
#include "InOut.h"
#include "iNeuron.h"
#include "Network.h"

namespace NeuralNetwork
{
	class train_MultiNetwork;
	class MyData;
	class MultilayerNetworkTrainImp
	{

	public:
		MultilayerNetworkTrainImp(void);
		~MultilayerNetworkTrainImp(void);

		virtual void Train(const vector<shared_ptr<Network::MyData>> mydata,train_MultiNetwork& myTrain) =0;
	};
}


