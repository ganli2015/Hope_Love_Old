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
	///Identity is a unique identity of iConcept.
	struct Identity
	{
		///The string of the word of the concept.
		string str;
		
		///<id> represents different concept with the same <str>.
		///So concepts of different words may have the same id 
		///and concepts of the same word have different ids.
		///However , currently I assume one concept for one POS of the word.
		///That is to say, id behaves same with POS.
		int id;

		Identity(){}
		Identity(string s, int i):str(s),id(i){}

		friend bool operator==(const Identity& left,const Identity& right)
		{
			return left.id==right.id && left.str==right.str;
		}

		///If <str> of <left> is smaller than one of <right>, then return true.
		///If the same, then compare id .
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
		//////////////////////////////////////////////////////////////////////////
		///Append all combinations of interactions between <from> and <me> to <table>.
		//////////////////////////////////////////////////////////////////////////
		void _MINDINTERFACEINOUT AppendToInteractTable(const vector<shared_ptr<iConcept>>& from,const vector<shared_ptr<iConcept>>& to,shared_ptr<iConceptInteractTable> table);

		//////////////////////////////////////////////////////////////////////////
		///Append concept pairs <pairs> to <table>.
		//////////////////////////////////////////////////////////////////////////
		void _MINDINTERFACEINOUT AppendToInteractTable(const vector<MindType::ConceptPair>& pairs, shared_ptr<iConceptInteractTable> table);

		//////////////////////////////////////////////////////////////////////////
		///Find the same concept with <concept> in <concepts>
		///and return the index.
		///If not find, return -1.
		//////////////////////////////////////////////////////////////////////////
		int _MINDINTERFACEINOUT IndexOf(const vector<shared_ptr<iConcept>>& concepts,const shared_ptr<iConcept> concept);
		//////////////////////////////////////////////////////////////////////////
		///Find the same concept with <concept> in <concepts>
		///and return the index.
		///If not find, return -1.
		//////////////////////////////////////////////////////////////////////////
		int _MINDINTERFACEINOUT IndexOf(const map<int,shared_ptr<iConcept>>& concepts,const shared_ptr<iConcept> concept);
		//////////////////////////////////////////////////////////////////////////
		///Find the same concept with <concept> in <concepts>
		///and return the index.
		///If not find, return -1.
		//////////////////////////////////////////////////////////////////////////
		int _MINDINTERFACEINOUT IndexOf(const map<int,weak_ptr<iConcept>>& concepts,const shared_ptr<iConcept> concept);

		//////////////////////////////////////////////////////////////////////////
		///Check whether <left> and <right> are the same.
		//////////////////////////////////////////////////////////////////////////
		bool _MINDINTERFACEINOUT IsSameConcept(const shared_ptr<iConcept> left,const shared_ptr<iConcept> right);

		//////////////////////////////////////////////////////////////////////////
		///Convert <vec> to string and write to <out>.
		//////////////////////////////////////////////////////////////////////////
		void _MINDINTERFACEINOUT WriteConcepts(const vector<shared_ptr<iConcept>>& vec,ofstream& out);

		//////////////////////////////////////////////////////////////////////////
		///Remove duplicated concept chains in <chains>.
		//////////////////////////////////////////////////////////////////////////
		void _MINDINTERFACEINOUT RemoveSameChain( vector<shared_ptr<iConceptChain>>& chains ) ;

		void _MINDINTERFACEINOUT OutputConceptPairs(const vector<MindType::ConceptPair>& pairs,ostream& out);

		//////////////////////////////////////////////////////////////////////////
		///Get the concept that represents an integer from <conceptVec>.
		//////////////////////////////////////////////////////////////////////////
		shared_ptr<Mind::iConcept> _MINDINTERFACEINOUT FindIntegerConcept(const vector<shared_ptr<Mind::iConcept>>& conceptVec);

		//////////////////////////////////////////////////////////////////////////
		///Filter <total> with <partial> and return the remaining.
		//////////////////////////////////////////////////////////////////////////
		vector<MindType::ConceptPair> _MINDINTERFACEINOUT FilterPartialConceptPairs(const vector<MindType::ConceptPair>& total, const vector<MindType::ConceptPair>& partial);

		//////////////////////////////////////////////////////////////////////////
		///Remove duplicated concept tables in <tables>.
		//////////////////////////////////////////////////////////////////////////
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

