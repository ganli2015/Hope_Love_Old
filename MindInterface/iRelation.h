#pragma once
#include "InOut.h"
#include "PublicTypedef.h"

namespace Mind
{
	class iConcept;
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

	public:
		iRelation(void);
		virtual ~iRelation(void);

		virtual string GetString() const =0;
		///Check whether <expre> satisfy the relation <me>.
		virtual bool Satisfy(const shared_ptr<iExpression> expre) const =0;
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

		virtual string GetString() const =0;
		virtual bool Satisfy(const shared_ptr<iExpression> expre) const =0;
	};

	///An iRelationLeaf contains the relationship between several logic symbols.
	class _MINDINTERFACEINOUT iRelationLeaf : public iRelation
	{
		typedef LogicType::ConSymbol ConSymbol;
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

