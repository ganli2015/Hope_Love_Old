#pragma once
#include "InOut.h"
#include "../MindInterface/iRelation.h"
#include "../MindInterface/PublicTypedef.h"

namespace Mind
{
	class iConceptInteractTable;
	class iConcept;
}

namespace LogicSystem
{
	template<class T>
	class Number;

	class _LOGICSYSTEMINOUT RelationLeaf :
		public iRelationLeaf
	{
		

		vector<SymbolPair> _relations;
		vector<shared_ptr<iRelationConstraint>> _constraints;


		const string _connectTag;
		const char _sepTag;

		friend class Test_iRelation;

	public:
		RelationLeaf(void);
		virtual ~RelationLeaf(void);

		virtual void AddRelation(const shared_ptr<ConSymbol> from,const shared_ptr<ConSymbol> to) ;
		virtual void AddRelation(const shared_ptr<ConSymbol> from,const shared_ptr<ConSymbol> to, const shared_ptr<Num> num) ;
		virtual void AddConstraint(const shared_ptr<iRelationConstraint> constraint) ;
		virtual string GetString() const ;

		virtual bool Satisfy(const shared_ptr<iExpression> expre,const bool exact=true) ;
		virtual bool Satisfy(const shared_ptr<Mind::iConceptInteractTable> conceptTable,const bool exact=true) ;

		virtual shared_ptr<iRelation> GenerateSpecialRelation() const ;
		virtual shared_ptr<Mind::iConceptInteractTable> GenerateConceptTable() const ;
	private:
		bool InterTableSatisfyRelation(const shared_ptr<Mind::iConceptInteractTable> interTable);
		void Recursive_FindMatchedPairSequence(const vector<SymbolPair>& sPairs,const vector<ConceptPair>& cPairs, vector<PairSequence>& sequence) const;
		virtual vector<iRelation::PairSequence> FindMatchedPairSequence(const vector<ConceptPair>& conceptPairs) const ;
		RelationLeaf::PairSequence CreateSequenceWithOneElem(const SymbolPair& sPair,const ConceptPair& cPair) const;
		
		//Generate new symbol pairs considering the repetition of the original pair.
		vector<SymbolPair> GeneratePairSequence(const SymbolPair& symbolPair) const;

	};
}


