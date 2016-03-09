#include "StdAfx.h"
#include "ConceptReactImp_1212.h"
#include "Concept.h"
#include "ConceptSet.h"
#include "ConceptChain.h"
#include "Cerebrum.h"
#include "BaseConcept.h"
#include "CommonFunction.h"

#include "../Mathmatic/FindSequence.h"
#include "../Mathmatic/MathTool.h"

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
		vector<shared_ptr<iDataArray>> splitArray=SplitTo1212(input);
		vector<shared_ptr<iDataArray>> outArray;
		for (unsigned int i=0;i<splitArray.size();++i)
		{
			outArray.push_back(_network->GetResult(splitArray[i]));
		}

		vector<vector<ConceptInfo>> conceptInfoSequence;
		for (unsigned int i=0;i<outArray.size();++i)
		{
			vector<vector<ConceptInfo>> tmpInfoSequence=ExtractConceptInfoSequence(outArray[i]);
			if(tmpInfoSequence.empty()) continue;

			conceptInfoSequence.insert(conceptInfoSequence.end(),tmpInfoSequence.begin(),tmpInfoSequence.end()-1);//�����н�β���¸����еĿ�ͷ���ظ��ġ�
		
			if(i==outArray.size()-1)
			{
				conceptInfoSequence.push_back(tmpInfoSequence.back());
			}
		}
		ResetArrayComponent(conceptInfoSequence);

		//�������Concept���е�������ϣ�ÿ����ϵ�Ԫ�ظ�������ͬ�ģ�
		vector<vector<ConceptInfo>> chainCombinations=GetAllCombinations<ConceptInfo>::Get(conceptInfoSequence);
		GenerateChainProperties generateResult;
		generateResult=for_each(chainCombinations.begin(),chainCombinations.end(),generateResult);

		vector<ConceptChainProperty> res= generateResult.GetResult();
		//NormalizeConfidence(res);

		return res;
	}

	void ConceptReactImp_1212::ResetArrayComponent(vector<vector<ConceptInfo>>& infoSequence)
	{
		for (unsigned int i=0;i<infoSequence.size();++i)
		{
			vector<ConceptInfo> &seq=infoSequence[i];
			for (unsigned int j=0;j<seq.size();++j)
			{
				seq[j].arrayComponent=i+1;
			}
		}
	}

	vector<shared_ptr<NeuralNetwork::iDataArray>> ConceptReactImp_1212::SplitTo1212( const shared_ptr<NeuralNetwork::iDataArray> input ) const
	{
		//key��input��ĳ��Ԫ��ֵ��value�Ǹ�Ԫ�ص���š�Ҫ��key��1��2��3...����Ȼ��
		map<int,int> indexMap;
		for (unsigned int i=0;i<input->Dimension();++i)
		{
			double val=input->Get_ithVal(i);
			int val_round=(int)Round(val);
			if(val_round==0) continue;

			Check(indexMap.count(val_round)==0);
			indexMap[val_round]=i;
		}
		Check(indexMap.size()==indexMap.rbegin()->first);

		vector<shared_ptr<iDataArray>> res;
		for (unsigned int i=1;i<indexMap.size();++i)
		{
			shared_ptr<iDataArray> newArray(new DataArray(input->Dimension()));
			newArray->Set_ithVal(indexMap[i],1.);
			newArray->Set_ithVal(indexMap[i+1],2.);
			res.push_back(newArray);
		}
		
		return res;
	}

}

