#pragma once
#include "InOut.h"
#include "../MindInterface/iRelation.h"

namespace LogicSystem
{
	class _LOGICSYSTEMINOUT RelationSingleNode : public iRelationSingleNode
	{
		shared_ptr<ConSymbol> _symbol;

		vector<shared_ptr<iRelationConstraint>> _constraints;

	public:
		RelationSingleNode();
		~RelationSingleNode();

		virtual void SetSymbol(const shared_ptr<ConSymbol> symbol) { _symbol = symbol; }

		virtual void AddConstraint(const shared_ptr<iRelationConstraint> constraint) { _constraints.push_back(constraint); }

		virtual string GetString() const ;

		///<exact> does not work.
		///Only if there is one concept in <expre> and it matches symbol in <me> will return true.
		virtual bool Satisfy(const shared_ptr<iExpression> expre, const bool exact = true) ;
		///Currently always return false.
		///Only one single concept is taken into consideration.
		virtual bool Satisfy(const shared_ptr<Mind::iConceptInteractTable> expre, const bool exact = true) ;

		///Currently always return false.
		virtual vector<PairSequence> FindMatchedPairSequence(const vector<ConceptPair>& conceptPairs) const ;

		virtual shared_ptr<iRelation> GenerateSpecialRelation() const ;

		///Always return null.
		virtual shared_ptr<Mind::iConceptInteractTable> GenerateConceptTable() const ;

		virtual shared_ptr<Mind::iConcept> GenerateSingleConcept() const;
	};
}


