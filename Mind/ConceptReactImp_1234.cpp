#include "StdAfx.h"
#include "ConceptReactImp_1234.h"
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
	ConceptReactImp_1234::ConceptReactImp_1234(const shared_ptr<NeuralNetwork::Network> network,ConceptSet* conceptSet):_network(network),ConceptReactImp(conceptSet)
	{
	}


	ConceptReactImp_1234::~ConceptReactImp_1234(void)
	{
	}

	vector<ConceptChainProperty> ConceptReactImp_1234::Perform(const shared_ptr<ConceptChain> chain)
	{
		if(_network==NULL) return vector<ConceptChainProperty>();

		shared_ptr<iDataArray> input=CommonFunction::ToDataArray(chain,_conceptSet);
		shared_ptr<iDataArray> output=_network->GetResult(input);

		vector<vector<ConceptInfo>> conceptInfoSequence=ExtractConceptInfoSequence(output);
		//获得所有Concept序列的排列组合，每个组合的元素个数是相同的！
		vector<vector<ConceptInfo>> chainCombinations=GetAllCombinations<ConceptInfo>::Get(conceptInfoSequence);
		GenerateChainProperties generateResult;
		generateResult=for_each(chainCombinations.begin(),chainCombinations.end(),generateResult);

		vector<ConceptChainProperty> res= generateResult.GetResult();
		//NormalizeConfidence(res);

		return res;
	}

	

}

