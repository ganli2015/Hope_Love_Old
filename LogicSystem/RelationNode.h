#pragma once
#include "InOut.h"
#include "../MindInterface/iRelation.h"

namespace Mind
{
	class iConceptInteractTable;
}

namespace LogicSystem
{
	class iRelationConstraint;

	class _LOGICSYSTEMINOUT RelationNode : public iRelationNode
	{
		const string _andTag;
		const string _orTag;

		vector<shared_ptr<iRelationConstraint>> _constraints;


		friend class Test_iRelation;
	public:
		RelationNode(void);
		~RelationNode(void);

		virtual string GetString() const ;
		virtual bool Satisfy(const shared_ptr<iExpression> expre) ;
		virtual void AddConstraint(const shared_ptr<iRelationConstraint> constraint) ;
		virtual shared_ptr<iRelation> GenerateSpecialRelation() const ;

	private:
		//If state is And, then any relation not satisfied will make its respective PairSequence vanish in result.
		//If state is Or, then only when all relations failing to satisfy will make its respective PairSequence vanish in result.
		virtual vector<iRelation::PairSequence> FindMatchedPairSequence(const vector<ConceptPair>& conceptPairs) const;
		bool InterTableSatisfyRelation( const shared_ptr<Mind::iConceptInteractTable> interTable );

		void Recursive_FindMatchedPairSequence(const vector<ConceptPair>& conceptPairs,
			const vector<shared_ptr<iRelation>>& relations,
			vector<PairSequence>& sequences) const;
		vector<iRelation::ConceptPair> ExcludeConceptPairsFromSequence(const vector<ConceptPair>& rawPairs,PairSequence sequence) const;
		bool ConceptPairInSequenceAndRemovePair(const ConceptPair& cPair,PairSequence& sequence) const ;
		vector<iRelation::PairSequence> CombineOneSeqWithManySeqs(const PairSequence& oneSeq,const vector<PairSequence>& manySeqs) const;
	
	};
}


