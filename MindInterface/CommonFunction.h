#pragma once
#include "InOut.h"

namespace DataCollection
{
	class GrammarPattern;
	enum PartOfSpeech;
}

namespace Mind
{
	struct Identity
	{
		string str;
		//��ʾͬһ��string����Ӧ�Ĳ�ͬ��concept�������ʵ�id����-1��
		//Ŀǰͬһ�����ʵ�ͬһ������ֻ��Ӧ��һ��id��
		//Ҳ����˵���id��ʱ�𲻵����ã�
		int id;
	};

	class iConcept;
	class iConceptInteractTable;
	class iConceptChain;
	namespace CommonFunction
	{
		//��<from>��<to>�������໥���ö���ӵ�table
		void _MINDINTERFACEINOUT AppendToInteractTable(const vector<shared_ptr<iConcept>>& from,const vector<shared_ptr<iConcept>>& to,shared_ptr<iConceptInteractTable> table);

		//���û���ҵ����򷵻�-1.
		int _MINDINTERFACEINOUT IndexOf(const vector<shared_ptr<iConcept>>& concepts,const shared_ptr<iConcept> concept);

		bool _MINDINTERFACEINOUT IsSameConcept(const shared_ptr<iConcept> left,const shared_ptr<iConcept> right);

		void _MINDINTERFACEINOUT WriteConcepts(const vector<shared_ptr<iConcept>>& vec,ofstream& out);

		void _MINDINTERFACEINOUT RemoveSameChain( vector<shared_ptr<iConceptChain>>& chains ) ;

		double _MINDINTERFACEINOUT ComputeP_GrammarLocalAnalysis(const DataCollection::GrammarPattern& pattern);

		//����<curPos>�����Ŷȣ���������������������<forwardPos>��<backwardPos>.
		double _MINDINTERFACEINOUT ComputeP_GrammarLocal(const DataCollection::PartOfSpeech& curPos,const DataCollection::PartOfSpeech& forwardPos,const DataCollection::PartOfSpeech& backwardPos);

		void _MINDINTERFACEINOUT OutputConceptPairs(const vector<MindType::ConceptPair>& pairs,ostream& out);

		class _MINDINTERFACEINOUT SameConcept
		{
			shared_ptr<iConcept> _me;
		public:
			SameConcept(const shared_ptr<iConcept> val):_me(val){}
			~SameConcept(){}

			bool operator()(const shared_ptr<iConcept> val);
		};
	}
}

