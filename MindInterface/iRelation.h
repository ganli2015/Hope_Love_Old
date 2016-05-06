#pragma once
#include "InOut.h"
#include "PublicTypedef.h"

namespace Mind
{
	class iConcept;
	class iConceptInteractTable;
}

namespace LogicSystem
{
	class iExpression;
	template<class T>
	class iSymbol;
	class iRelationConstraint;

	///iRelation indicates the logic relationship between logic symbols.
	class _MINDINTERFACEINOUT iRelation
	{
	protected:
		struct PairInfo;
		typedef MindType::ConceptPair ConceptPair;
		typedef LogicType::ConSymbol ConSymbol;
		typedef LogicType::SymbolPair SymbolPair;
		typedef vector<iRelation::PairInfo> PairSequence;


		//Store concept pair and related symbol pair.
		struct PairInfo
		{
			ConceptPair cPair;
			SymbolPair sPair;
		};

	public:
		iRelation(void);
		virtual ~iRelation(void);

		virtual string GetString() const =0;
		///Check whether <expre> satisfy the relation <me>.
		virtual bool Satisfy(const shared_ptr<iExpression> expre) const =0;
		///Find match symbol and concept pairs in <conceptPairs>.
		virtual vector<PairSequence> FindMatchedPairSequence(const vector<ConceptPair>& conceptPairs) const =0;

	protected:
		virtual bool SatifyConstraint(const vector<PairInfo>& pairInfos,const vector<shared_ptr<iRelationConstraint>>& constraints) const;

		};

	///iRelationNode contains the several sub relations and their relationship is And or Or.
	class _MINDINTERFACEINOUT iRelationNode : public iRelation
	{
	public:
		enum State
		{
			And,
			Or
		};

	protected:
		State _state;
		vector<shared_ptr<iRelation>> _subRelations;

	public:
		iRelationNode(void);
		virtual ~iRelationNode(void);

		void SetState(const State s){_state=s;}
		void AddSubRelation(const shared_ptr<iRelation> condition){_subRelations.push_back(condition);}
		virtual void AddConstraint(const shared_ptr<iRelationConstraint> constraint) =0;

		virtual string GetString() const =0;
		virtual bool Satisfy(const shared_ptr<iExpression> expre) const =0;

	protected:
	};

	///An iRelationLeaf contains the relationship between several logic symbols.
	class _MINDINTERFACEINOUT iRelationLeaf : public iRelation
	{
	public:
		iRelationLeaf(void);
		virtual ~iRelationLeaf();

		///Add the relation of the two symbols to <me>.
		///<from> acts on <to>.
		virtual void AddRelation(const shared_ptr<ConSymbol> from,const shared_ptr<ConSymbol> to) =0;
		///Add Constraints to symbols.
		virtual void AddConstraint(const shared_ptr<iRelationConstraint> constraint) =0;
		virtual string GetString() const =0;
		virtual bool Satisfy(const shared_ptr<iExpression> expre) const =0;
	};


}

