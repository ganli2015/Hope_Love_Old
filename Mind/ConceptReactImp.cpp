#include "StdAfx.h"
#include "ConceptReactImp.h"
#include "ConceptSet.h"
#include "ConceptChain.h"
#include "BaseConcept.h"

#include "../Neural Network Design/DataArray.h"

using namespace NeuralNetwork;

namespace Mind
{
	ConceptReactImp::ConceptReactImp(ConceptSet* conceptSet):_conceptSet(conceptSet)
	{
	}


	ConceptReactImp::~ConceptReactImp(void)
	{
	}

	

	void ConceptReactImp::GenerateChainProperties::operator()( const vector<ConceptInfo>& combination )
	{
		vector<shared_ptr<Concept>> conceptVec;
		conceptVec.reserve(combination.size());
		double variance=0.0;
		for (unsigned int i=0;i<combination.size();++i)
		{
			conceptVec.push_back(combination[i].concept);
			variance+=pow(combination[i].arrayComponent-(i+1),2);
		}

		ConceptChainProperty property;
		property.chain=shared_ptr<ConceptChain>(new ConceptChain(conceptVec));
		property.confidence=exp(-variance);
		_result.push_back(property);
	}

}

