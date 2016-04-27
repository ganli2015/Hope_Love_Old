#pragma once
#include "InOut.h"
#include "iNeuron.h"
#include "Network.h"

namespace NeuralNetwork
{
	class train_MultiNetwork;
	class MyData;
	class _NEURALNETWORKDESIGNINOUT MultilayerNetworkTrainImp
	{
	protected:
		double _obj;
		int _iterCount;
		vector<double> _deviations;
		ofstream _out;

	public:
		MultilayerNetworkTrainImp(void);
		~MultilayerNetworkTrainImp(void);

		virtual void Train(const vector<shared_ptr<Network::MyData>> mydata,train_MultiNetwork& myTrain) =0;

		vector<double> GetSampleDeviations() const {return _deviations;}

	protected:
		void OutputDebugInfo();
	};
}


