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
		
		///<id> represents different concept with the same <str>.
		///However , currently I assume one concept for one POS of the word.
		///That is to say, id behaves same with POS.
		int id;

		Identity(){}
		Identity(string s, int i):str(s),id(i){}
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

		int _MINDINTERFACEINOUT IndexOf(const map<int,shared_ptr<iConcept>>& concepts,const shared_ptr<iConcept> concept);

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

