#pragma once
#include "ConceptReactImp.h"

namespace NeuralNetwork
{
	class Network;
}

namespace Mind
{
	//假设对神经网络输入的序列是{1,2,3}，则直接按该序列输入
	class ConceptReactImp_1234: public ConceptReactImp
	{
		shared_ptr<NeuralNetwork::Network> _network;

	public:
		ConceptReactImp_1234(const shared_ptr<NeuralNetwork::Network> network,ConceptSet* conceptSet);
		virtual ~ConceptReactImp_1234(void);

		virtual vector<ConceptChainProperty> Perform(const shared_ptr<ConceptChain> chain);

	private:
		vector<vector<ConceptReactImp::ConceptInfo>> ExtractConceptInfoSequence(const shared_ptr<NeuralNetwork::iDataArray> array);

		//找出array中小于等于upVal同时大于等于lowVal的数值，并且根据该数值的序号查找相应的Concept
		vector<ConceptReactImp::ConceptInfo> ExtractConceptInfo(const shared_ptr<NeuralNetwork::iDataArray> array,
			const double upVal,const double lowVal);

	
	};
}


