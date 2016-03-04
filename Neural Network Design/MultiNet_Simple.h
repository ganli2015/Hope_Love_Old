#pragma once
#include "InOut.h"
#include "MultilayerNetworkTrainImp.h"

namespace NeuralNetwork
{
	//��ԭʼ�ķ��򴫲���Multilayer network
	class MultiNet_Simple : public MultilayerNetworkTrainImp
	{
	public:
		MultiNet_Simple(void);
		~MultiNet_Simple(void);

		
		virtual void Train(const vector<shared_ptr<Network::MyData>> mydata,train_MultiNetwork& myTrain);


	};
}


