#pragma once
#include "InOut.h"

namespace NeuralNetwork
{
	class iDataArray;
}

namespace Mind
{
	struct ConceptChainProperty;
	class ConceptChain;
	class Concept;
	class ConceptSet;

	class ConceptReactImp
	{
	protected:
		struct ConceptInfo
		{
			//根据神经网络转化计算出来的向量序号对应的Concept。
			shared_ptr<Concept> concept;
			//根据神经网络转化计算出来的向量序号对应的数值。
			double arrayComponent;
		};

		ConceptSet* _conceptSet;

	public:
		ConceptReactImp(ConceptSet* conceptSet);
		virtual ~ConceptReactImp(void);

		virtual vector<ConceptChainProperty> Perform (const shared_ptr<ConceptChain> chain)=0;

	protected:

		vector<vector<ConceptReactImp::ConceptInfo>> ExtractConceptInfoSequence(const shared_ptr<NeuralNetwork::iDataArray> array);
		//找出array中小于等于upVal同时大于等于lowVal的数值，并且根据该数值的序号查找相应的Concept
		vector<ConceptReactImp::ConceptInfo> ExtractConceptInfo(const shared_ptr<NeuralNetwork::iDataArray> array,
			const double upVal,const double lowVal);

		class GenerateChainProperties
		{
			vector<ConceptChainProperty> _result;
		public:
			void operator()(const vector<ConceptInfo>& combination);
			vector<ConceptChainProperty> GetResult(){return _result;}
		};
	};
}


