#pragma once
#include "ConceptReactImp.h"

namespace NeuralNetwork
{
	class Network;
	class iDataArray;
}

namespace Mind
{
	//����������������������{1,2,3}����ֱ�����{1,2,0}��{0,1,2}���ٶ��������
	class ConceptReactImp_1212: public ConceptReactImp
	{
		shared_ptr<NeuralNetwork::Network> _network;

	public:
		ConceptReactImp_1212(const shared_ptr<NeuralNetwork::Network> network,ConceptSet* conceptSet);
		~ConceptReactImp_1212(void);

		virtual vector<ConceptChainProperty> Perform(const shared_ptr<iConceptChain> chain);

	private:
		vector<shared_ptr<NeuralNetwork::iDataArray>> SplitTo1212(const shared_ptr<NeuralNetwork::iDataArray> input) const;
		void ConceptReactImp_1212::ResetArrayComponent(vector<vector<ConceptInfo>>& infoSequence);
	};
}


