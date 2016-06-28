#pragma once
#include "InOut.h"
#include "../MindInterface/iLogicElementCreator.h"

namespace LogicSystem
{
	class _LOGICSYSTEMINOUT LogicElementCreator : public iLogicElementCreatorImp
	{
		class iSpecialSymbolCreator;
		class iBinaryConstraintCreator;

		///Restore special symbol creators
		map<SymbolType,iSpecialSymbolCreator*> _spSym;
		///Restore binary constraint creators
		map<ConstraintType,iBinaryConstraintCreator*> _biContr;

		typedef LogicType::ConSymbol ConSymbol;

	public:
		LogicElementCreator(void);
		~LogicElementCreator(void);

		virtual shared_ptr<iExpression> CreateExpression(const string str) const ;
		virtual shared_ptr<iExpression> CreateExpression(const vector<string> str) const ;
		virtual shared_ptr<iExpression> CreateExpression(const shared_ptr<DataCollection::Sentence> val) const ;
		virtual shared_ptr<iExpression> CreateExpression(const vector<shared_ptr<DataCollection::Sentence>> val) const ;

		virtual shared_ptr<iLogicStatement> CreateLogicStatement(const shared_ptr<iRelation> condition,const shared_ptr<iRelation> result) const ;

		virtual shared_ptr<iRelationLeaf> CreateRelationLeaf() const ;
		virtual shared_ptr<iRelationNode> CreateRelationNode() const ;
		virtual shared_ptr<iRelationSingleNode> CreateRelationSingleNode() const;

		virtual shared_ptr<iRelationConstraint> CreateBinaryConstraint(const ConstraintType type,const shared_ptr<LogicType::ConSymbol> s1,const shared_ptr<LogicType::ConSymbol> s2) const ;

		virtual shared_ptr<iLogic> CreateLogic() const ;

		virtual shared_ptr<LogicType::ConSymbol> CreateConceptSymbol(const shared_ptr<Mind::iConcept> con) const;
		virtual shared_ptr<LogicType::ConSymbol> CreateSpecialSymbol(const SymbolType type) const ;


	private:

		///For creating special symbols.
		class iSpecialSymbolCreator
		{
		public:
			virtual shared_ptr<LogicType::ConSymbol> Create()=0;
		};

		template<class T>
		class SpecialSymbolCreator : public iSpecialSymbolCreator
		{
		public:
			SpecialSymbolCreator(){}
			shared_ptr<LogicType::ConSymbol> Create(){return T::Create();}
		};

		///For creating binary constraints.
		class iBinaryConstraintCreator
		{
		public:
			virtual shared_ptr<iRelationConstraint> Create(const shared_ptr<ConSymbol> s1,const shared_ptr<ConSymbol> s2)=0;
		};

		template<class T>
		class BinaryConstraintCreator : public iBinaryConstraintCreator
		{
		public:
			BinaryConstraintCreator(){}
			shared_ptr<iRelationConstraint> Create(const shared_ptr<ConSymbol> s1,const shared_ptr<ConSymbol> s2){return T::Create(s1,s2);}
		};

	private:

		void Init();
	};
}


