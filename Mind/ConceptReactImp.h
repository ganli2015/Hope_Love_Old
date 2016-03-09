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
			//����������ת�����������������Ŷ�Ӧ��Concept��
			shared_ptr<Concept> concept;
			//����������ת�����������������Ŷ�Ӧ����ֵ��
			double arrayComponent;
		};

		ConceptSet* _conceptSet;

	public:
		ConceptReactImp(ConceptSet* conceptSet);
		virtual ~ConceptReactImp(void);

		virtual vector<ConceptChainProperty> Perform (const shared_ptr<ConceptChain> chain)=0;

	protected:

		vector<vector<ConceptReactImp::ConceptInfo>> ExtractConceptInfoSequence(const shared_ptr<NeuralNetwork::iDataArray> array);
		//�ҳ�array��С�ڵ���upValͬʱ���ڵ���lowVal����ֵ�����Ҹ��ݸ���ֵ����Ų�����Ӧ��Concept
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


