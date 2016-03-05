#pragma once
#include "InOut.h"
#include "MultilayerNetworkTrainImp.h"
//#include "TestClass.h"

namespace Math
{
	class Matrix;
	class Vector;
}

namespace NeuralNetwork
{
	//Network of the momentum modification to back propagation
	class MultiNet_MOBP : public MultilayerNetworkTrainImp
	{
		double _momentumCoefficient;
		vector<Math::Vector> _prevDeltaBias;
		vector<Math::Matrix> _prevDeltaMat;

		friend class TestClass;
	public:
		MultiNet_MOBP(void);
		~MultiNet_MOBP(void);

		virtual void Train(const vector<shared_ptr<Network::MyData>> mydata,train_MultiNetwork& myTrain);

	private:
		//计算所有样本对所有neuron的修正.
		void ComputeNeuronCorrection(const vector<shared_ptr<Network::MyData>> mydata,
			train_MultiNetwork& myTrain,
			vector<vector<Math::Matrix>>& deltaMat_Samples,
			vector<vector<Math::Vector>>& deltaBias_Samples);
		void ComputeMomentumCorrection(const vector<Math::Matrix>& curDeltaMat,
			const vector<Math::Vector>& curDeltaBias,
			const vector<Math::Matrix>& prevDeltaMat,
			const vector<Math::Vector>& prevDeltaBias,
			vector<Math::Matrix>& filteredDeltaMat,
			vector<Math::Vector>& filteredDeltaBias);

		//输入为每个样本对每个neuron的修正,每个元素是一个样本对所有neuron的修正。输出为每个neuron的平均修正.
		vector<Math::Matrix> ComputeDeltaMatForLayers(const vector<vector<Math::Matrix>>& deltaMats) const;
		vector<Math::Vector> ComputeDeltaBiasForLayers(const vector<vector<Math::Vector>>& deltaBiases) const;

		void SetMomentumCoefficient(const double val){_momentumCoefficient=val;}
	};
}


