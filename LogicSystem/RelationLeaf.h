#pragma once
#include "InOut.h"
#include "../MindInterface/iRelation.h"
#include "../MindInterface/PublicTypedef.h"


namespace LogicSystem
{
	class _LOGICSYSTEMINOUT RelationLeaf :
		public iRelationLeaf
	{
		typedef MindType::ConceptPair ConceptPair;
		typedef LogicType::ConSymbol ConSymbol;
		typedef LogicType::SymbolPair SymbolPair;

		//Store concept pair and related symbol pair.
		struct PairInfo
		{
			ConceptPair cPair;
			SymbolPair sPair;
		};

		vector<SymbolPair> _relations;
		vector<shared_ptr<iRelationConstraint>> _constraints;

		const string _connectTag;
		const char _sepTag;
	public:
		RelationLeaf(void);
		virtual ~RelationLeaf(void);

		virtual void AddRelation(const shared_ptr<ConSymbol> from,const shared_ptr<ConSymbol> to) ;
		virtual void AddConstraint(const shared_ptr<iRelationConstraint> constraint) ;
		virtual string GetString() const ;
		virtual bool Satisfy(const shared_ptr<iExpression> expre) const ;

	private:
		static vector<RelationLeaf::ConceptPair> FindMatchedPairs(const SymbolPair& symbolPair,const vector<ConceptPair>& cPairs);
		static vector<vector<RelationLeaf::PairInfo>> FindMatchedPairSequence(const vector<SymbolPair>& sPairs,const vector<ConceptPair>& cPairs);
		bool SatifyConstraint(const vector<PairInfo>& pairInfos) const;
	};
}


