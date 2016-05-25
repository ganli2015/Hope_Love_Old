#pragma once
#include "InOut.h"
#include "../MindInterface/iRelation.h"
#include "../MindInterface/PublicTypedef.h"

namespace Mind
{
	class iConceptInteractTable;
}

namespace LogicSystem
{
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
		virtual void AddConstraint(const shared_ptr<iRelationConstraint> constraint) ;
		virtual string GetString() const ;
		virtual bool Satisfy(const shared_ptr<iExpression> expre) ;
		virtual shared_ptr<iRelation> GenerateSpecialRelation() const ;
	private:
		bool InterTableSatisfyRelation(const shared_ptr<Mind::iConceptInteractTable> interTable);
		static vector<RelationLeaf::ConceptPair> FindMatchedPairs(const SymbolPair& symbolPair,const vector<ConceptPair>& cPairs);
		static vector<vector<RelationLeaf::PairInfo>> FindMatchedPairSequence(const vector<SymbolPair>& sPairs,const vector<ConceptPair>& cPairs);

		virtual vector<iRelation::PairSequence> FindMatchedPairSequence(const vector<ConceptPair>& conceptPairs) const ;
	};
}


