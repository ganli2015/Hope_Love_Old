#include "StdAfx.h"
#include "ConceptReactImp.h"
#include "ConceptSet.h"
#include "../MindElement/ConceptChain.h"
#include "../MindElement/BaseConcept.h"

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
		vector<shared_ptr<iConcept>> conceptVec;
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

	vector<vector<ConceptReactImp::ConceptInfo>> ConceptReactImp::ExtractConceptInfoSequence( const shared_ptr<NeuralNetwork::iDataArray> array )
	{
		vector<vector<ConceptInfo>> conceptInfoSequence;
		//���λ��1��2��3��4...����Ӧ��Concept�Լ���ֵ������и����û������Ӧ��Concept����ô������ֹ��
		//������֤�����Concept�����Ǻ���Ȼ����Ӧ�ġ�
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

	vector<ConceptReactImp::ConceptInfo> ConceptReactImp::ExtractConceptInfo( const shared_ptr<iDataArray> array, const double upVal,const double lowVal )
	{
		vector<ConceptInfo> res;

		for (unsigned int i=0;i<array->Dimension();++i)
		{
			double component=array->Get_ithVal(i);
			if(component>upVal || component<=lowVal) continue;//�����ǳ������޵ĳɷ֡�

			//����array�ı�������Concept����Ϊarray�ĵ�i���ɷֶ�Ӧ��id����i��BaseConcept��
			shared_ptr<Concept> base=_conceptSet->GetBaseConcept(i);

			ConceptInfo info;
			info.concept=base;
			info.arrayComponent=component;
			res.push_back(info);
		}

		return res;
	}
}

