#pragma once
#include "InOut.h"
#include "iConcept.h"

#include <list>

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

		friend bool operator==(const Identity& left,const Identity& right)
		{
			return left.id==right.id && left.str==right.str;
		}

		friend bool operator<(const Identity& left, const Identity& right)
		{
			if(left.str<right.str)
			{
				return true;
			}
			else if (left.str == right.str && left.id < right.id)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	};

	class iConcept;
	class iConceptInteractTable;
	class iConceptChain;
	namespace CommonFunction
	{
		//把<from>和<to>的所有相互作用都添加到table
		void _MINDINTERFACEINOUT AppendToInteractTable(const vector<shared_ptr<iConcept>>& from,const vector<shared_ptr<iConcept>>& to,shared_ptr<iConceptInteractTable> table);

		//如果没有找到，则返回-1.
		int _MINDINTERFACEINOUT IndexOf(const vector<shared_ptr<iConcept>>& concepts,const shared_ptr<iConcept> concept);

		int _MINDINTERFACEINOUT IndexOf(const map<int,shared_ptr<iConcept>>& concepts,const shared_ptr<iConcept> concept);

		int _MINDINTERFACEINOUT IndexOf(const map<int,weak_ptr<iConcept>>& concepts,const shared_ptr<iConcept> concept);

		bool _MINDINTERFACEINOUT IsSameConcept(const shared_ptr<iConcept> left,const shared_ptr<iConcept> right);

		void _MINDINTERFACEINOUT WriteConcepts(const vector<shared_ptr<iConcept>>& vec,ofstream& out);

		void _MINDINTERFACEINOUT RemoveSameChain( vector<shared_ptr<iConceptChain>>& chains ) ;

		double _MINDINTERFACEINOUT ComputeP_GrammarLocalAnalysis(const DataCollection::GrammarPattern& pattern);

		//计算<curPos>的置信度，假设其相邻两个词性是<forwardPos>和<backwardPos>.
		double _MINDINTERFACEINOUT ComputeP_GrammarLocal(const DataCollection::PartOfSpeech& curPos,const DataCollection::PartOfSpeech& forwardPos,const DataCollection::PartOfSpeech& backwardPos);

		void _MINDINTERFACEINOUT OutputConceptPairs(const vector<MindType::ConceptPair>& pairs,ostream& out);

		///Get the concept that represents an integer from <conceptVec>.
		shared_ptr<Mind::iConcept> _MINDINTERFACEINOUT FindIntegerConcept(const vector<shared_ptr<Mind::iConcept>>& conceptVec);

		///Filter <total> with <partial> and return the remaining.
		vector<MindType::ConceptPair> _MINDINTERFACEINOUT FilterPartialConceptPairs(const vector<MindType::ConceptPair>& total, const vector<MindType::ConceptPair>& partial);

		void _MINDINTERFACEINOUT RemoveDuplicated(list<shared_ptr<iConceptInteractTable>>& tables);

		class _MINDINTERFACEINOUT SameConcept
		{
			shared_ptr<iConcept> _me;
		public:
			SameConcept(const shared_ptr<iConcept> val):_me(val){}
			~SameConcept(){}

			bool operator()(const shared_ptr<iConcept> val);
		};

		class _MINDINTERFACEINOUT SameConceptPair
		{
			shared_ptr<iConcept> _from;
			shared_ptr<iConcept> _to;
		public:
			SameConceptPair(const shared_ptr<iConcept> from,const shared_ptr<iConcept> to):_from(from),_to(to){}
			~SameConceptPair(){}

			bool operator()(const pair<shared_ptr<iConcept>,shared_ptr<iConcept>> val);
		};

		class _MINDINTERFACEINOUT SameConceptPair_Identity
		{
			Identity _from;
			Identity _to;
		public:
			SameConceptPair_Identity(const Identity from, const Identity to) :_from(from), _to(to) {}
			~SameConceptPair_Identity() {}

			bool operator()(const pair<shared_ptr<iConcept>, shared_ptr<iConcept>> val);
		};

		class _MINDINTERFACEINOUT SameConceptTable
		{
			shared_ptr<iConceptInteractTable> _me;
		public:
			SameConceptTable(const shared_ptr<iConceptInteractTable> val) :_me(val) {}
			~SameConceptTable() {}

			bool operator()(const shared_ptr<iConceptInteractTable> val);
		};
	}
}

