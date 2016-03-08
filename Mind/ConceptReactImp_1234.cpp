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

	vector<vector<ConceptReactImp::ConceptInfo>> ConceptReactImp_1234::ExtractConceptInfoSequence( const shared_ptr<NeuralNetwork::iDataArray> array )
	{
		vector<vector<ConceptInfo>> conceptInfoSequence;
		//依次获得1、2、3、4...所对应的Concept以及数值，如果有个序号没有所对应的Concept，那么迭代终止。
		//这样保证了这个Concept序列是和自然数对应的。
		int seqIndex=1;
		while(true)
		{
			double validRegion=0.5;
			double upVal=seqIndex+validRegion;
			double lowVal=seqIndex-validRegion;

			vector<ConceptInfo> conceptInfos=ExtractConceptInfo(array,upVal,lowVal);
			if(conceptInfos.empty())
			{
				break;
			}

			conceptInfoSequence.push_back(conceptInfos);
			++seqIndex;
		}

		return conceptInfoSequence;
	}

	vector<ConceptReactImp::ConceptInfo> ConceptReactImp_1234::ExtractConceptInfo( const shared_ptr<iDataArray> array, const double upVal,const double lowVal )
	{
		vector<ConceptInfo> res;

		for (unsigned int i=0;i<array->Dimension();++i)
		{
			double component=array->Get_ithVal(i);
			if(component>upVal || component<=lowVal) continue;//不考虑超出界限的成分。

			//根据array的编号来获得Concept，因为array的第i个成分对应于id等于i的BaseConcept。
			shared_ptr<Concept> base=_conceptSet->GetBaseConcept(i);

			ConceptInfo info;
			info.concept=base;
			info.arrayComponent=component;
			res.push_back(info);
		}

		return res;
	}

}

