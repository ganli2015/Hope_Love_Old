#pragma once
#include "InOut.h"
#include "MultilayerNetworkTrainImp.h"

namespace NeuralNetwork
{
	//最原始的反向传播的Multilayer network
	class MultiNet_Simple : public MultilayerNetworkTrainImp
	{
	public:
		MultiNet_Simple(void);
		~MultiNet_Simple(void);

		
		virtual void Train(const vector<shared_ptr<Network::MyData>> mydata,train_MultiNetwork& myTrain);


	};
}


