#include "StdAfx.h"
#include "ConceptReactImp_1212.h"
#include "Concept.h"
#include "ConceptSet.h"
#include "ConceptChain.h"
#include "Cerebrum.h"
#include "BaseConcept.h"
#include "CommonFunction.h"

#include "../Mathmatic/FindSequence.h"

#include "../Neural Network Design/DataArray.h"
#include "../Neural Network Design/Network.h"

using namespace NeuralNetwork;
using namespace Math;

namespace Mind
{
	ConceptReactImp_1212::ConceptReactImp_1212(const shared_ptr<NeuralNetwork::Network> network,ConceptSet* conceptSet):_network(network),ConceptReactImp(conceptSet)
	{
	}


	ConceptReactImp_1212::~ConceptReactImp_1212(void)
	{
	}

	vector<ConceptChainProperty> ConceptReactImp_1212::Perform( const shared_ptr<ConceptChain> chain )
	{
		if(_network==NULL) return vector<ConceptChainProperty>();

		shared_ptr<iDataArray> input=CommonFunction::ToDataArray(chain,_conceptSet);
	}

}

