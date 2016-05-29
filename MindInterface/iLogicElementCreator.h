#pragma once
#include "InOut.h"
#include "PublicTypedef.h"

namespace DataCollection
{
	class Sentence;
}

namespace Mind
{
	class iConcept;
}

namespace LogicSystem
{
	class iExpression;
	class iLogicStatement;
	class iRelation;
	class iRelationNode;
	class iRelationLeaf;
	class iRelationConstraint;
	template<class T>
	class iSymbol;
	class iLogic;

	class iLogicElementCreatorImp;

	class _MINDINTERFACEINOUT iLogicElementCreator
	{
		static shared_ptr<iLogicElementCreatorImp> _imp;

	public:
		///The type for special symbols.
		enum SymbolType
		{
			Arb,
			Num,
			Verb
		};

		enum ConstraintType
		{
			Eq,
			Ineq
		};

	public:
		iLogicElementCreator(void);
		~iLogicElementCreator(void);

		static void SetImp(const shared_ptr<iLogicElementCreatorImp> imp);

		static shared_ptr<iExpression> CreateExpression(const string str) ;
		static shared_ptr<iExpression> CreateExpression(const vector<string> str);
		static shared_ptr<iExpression> CreateExpression(const shared_ptr<DataCollection::Sentence> val) ;
		static shared_ptr<iExpression> CreateExpression(const vector<shared_ptr<DataCollection::Sentence>> val) ;

		static shared_ptr<iLogicStatement> CreateLogicStatement(const shared_ptr<iRelation> condition,const shared_ptr<iRelation> result) ;

		static shared_ptr<iRelationLeaf> CreateRelationLeaf() ;
		static shared_ptr<iRelationNode> CreateRelationNode() ;

		static shared_ptr<iLogic> CreateLogic() ;

		static shared_ptr<LogicType::ConSymbol> CreateConceptSymbol(const shared_ptr<Mind::iConcept> con) ;
		static shared_ptr<LogicType::ConSymbol> CreateSpecialSymbol(const SymbolType type) ;

		static shared_ptr<iRelationConstraint> CreateBinaryConstraint(const ConstraintType type,const shared_ptr<LogicType::ConSymbol> s1,const shared_ptr<LogicType::ConSymbol> s2) ;
	};

	class _MINDINTERFACEINOUT iLogicElementCreatorImp
	{
	protected:
		typedef iLogicElementCreator Host;
		typedef Host::SymbolType SymbolType;
		typedef Host::ConstraintType ConstraintType;

	public:
		iLogicElementCreatorImp(){}
		virtual ~iLogicElementCreatorImp(){}

		virtual shared_ptr<iExpression> CreateExpression(const string str) const =0;
		virtual shared_ptr<iExpression> CreateExpression(const vector<string> str) const =0;
		virtual shared_ptr<iExpression> CreateExpression(const shared_ptr<DataCollection::Sentence> val) const =0;
		virtual shared_ptr<iExpression> CreateExpression(const vector<shared_ptr<DataCollection::Sentence>> val) const =0;

		virtual shared_ptr<iLogicStatement> CreateLogicStatement(const shared_ptr<iRelation> condition,const shared_ptr<iRelation> result) const =0;

		virtual shared_ptr<iRelationLeaf> CreateRelationLeaf() const =0;
		virtual shared_ptr<iRelationNode> CreateRelationNode() const =0;

 		virtual shared_ptr<iRelationConstraint> CreateBinaryConstraint(const ConstraintType type,const shared_ptr<LogicType::ConSymbol> s1,const shared_ptr<LogicType::ConSymbol> s2) const =0;
 
 		virtual shared_ptr<LogicType::ConSymbol> CreateSpecialSymbol(const SymbolType type) const =0;
		virtual shared_ptr<LogicType::ConSymbol> CreateConceptSymbol(const shared_ptr<Mind::iConcept> con) const =0;

		virtual shared_ptr<iLogic> CreateLogic() const =0;
	};
}


