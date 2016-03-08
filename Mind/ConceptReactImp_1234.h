#pragma once
#include "ConceptReactImp.h"

namespace NeuralNetwork
{
	class Network;
}

namespace Mind
{
	//����������������������{1,2,3}����ֱ�Ӱ�����������
	class ConceptReactImp_1234: public ConceptReactImp
	{
		shared_ptr<NeuralNetwork::Network> _network;

	public:
		ConceptReactImp_1234(const shared_ptr<NeuralNetwork::Network> network,ConceptSet* conceptSet);
		virtual ~ConceptReactImp_1234(void);

		virtual vector<ConceptChainProperty> Perform(const shared_ptr<ConceptChain> chain);

	private:
		vector<vector<ConceptReactImp::ConceptInfo>> ExtractConceptInfoSequence(const shared_ptr<NeuralNetwork::iDataArray> array);

		//�ҳ�array��С�ڵ���upValͬʱ���ڵ���lowVal����ֵ�����Ҹ��ݸ���ֵ����Ų�����Ӧ��Concept
		vector<ConceptReactImp::ConceptInfo> ExtractConceptInfo(const shared_ptr<NeuralNetwork::iDataArray> array,
			const double upVal,const double lowVal);

	
	};
}


