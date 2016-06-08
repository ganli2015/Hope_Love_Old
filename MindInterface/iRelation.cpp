#include "StdAfx.h"
#include "iRelation.h"

#include "iSymbol.h"
#include "iRelationConstraint.h"
#include "iConcept.h"


using namespace Mind;

namespace LogicSystem
{
	iRelation::iRelation(void)
	{
	}


	iRelation::~iRelation(void)
	{
	}

	bool iRelation::SatifyConstraint(const vector<PairInfo>& pairInfos,const vector<shared_ptr<iRelationConstraint>>& constraints) const
	{
		class CheckSatify
		{
			bool _satisfied;
			vector<shared_ptr<iRelationConstraint>> _constraints;
		public:
			CheckSatify(const vector<shared_ptr<iRelationConstraint>>& constraints):_satisfied(false),_constraints(constraints){}
			~CheckSatify(){}

			void Do()
			{
				for (unsigned int i=0;i<_constraints.size();++i)
				{
					if(!_constraints[i]->Satisfy())
					{
						_satisfied= false;
						return;
					}
				}
				_satisfied=true;
			}

			bool Satisfied() const {return _satisfied;}
		};

		CheckSatify check(constraints);
		SymbolBindAndRelease(pairInfos,check);

		return check.Satisfied();
	}

	void iRelation::RemoveSequencesUnsatifyConstraints( const vector<shared_ptr<iRelationConstraint>>& constraints,vector<iRelation::PairSequence>& sequences ) const
	{
		for (vector<iRelation::PairSequence>::iterator it=sequences.begin();it!=sequences.end();)
		{
			if(!SatifyConstraint(*it,constraints))
			{
				it=sequences.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	void iRelation::BindObjects( const  PairSequence& pairInfos ) const
	{
		class BindEachObject
		{

		public:
			BindEachObject(){}
			~BindEachObject(){}

			void operator()(const PairInfo& info)
			{
				//Bind each symbol with related concept.
				info.sPair.First()->BindReferredObject(info.cPair.first);
				info.sPair.Second()->BindReferredObject(info.cPair.second);

			}
		};

		for_each(pairInfos.begin(),pairInfos.end(),BindEachObject());
	}

	void iRelation::ReleaseObjects( const PairSequence& pairInfos ) const
	{
		class BindEachNull
		{
		public:
			void operator()(const PairInfo& info)
			{
				//Bind each symbol with related concept.
				info.sPair.First()->BindReferredObject(NULL);
				info.sPair.Second()->BindReferredObject(NULL);
			}
		};

		for_each(pairInfos.begin(),pairInfos.end(),BindEachNull());
	}

	shared_ptr<iRelation> iRelation::SymbolResonance( const shared_ptr<iRelation> relation ) const
	{
		class GenerateRelation
		{
			shared_ptr<iRelation> _relation;
			shared_ptr<iRelation> _res;

		public:
			GenerateRelation(const shared_ptr<iRelation> relation):_relation(relation){}
			~GenerateRelation(){}

			void Do()
			{
				_res=_relation->GenerateSpecialRelation();
			}

			shared_ptr<iRelation> GetTable() const {return _res;}
		};

		if(_satisfiedSequence.empty()) return NULL;

		GenerateRelation generateTable(relation);
		SymbolBindAndRelease(_satisfiedSequence,generateTable);

		return generateTable.GetTable();
	}

	iRelationNode::iRelationNode( void )
	{

	}

	iRelationNode::~iRelationNode( void )
	{

	}


	iRelationLeaf::iRelationLeaf( void )
	{

	}

	iRelationLeaf::~iRelationLeaf()
	{

	}

}

