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

		virtual vector<ConceptChainProperty> Perform(const shared_ptr<iConceptChain> chain);

	private:

		

	
	};
}


