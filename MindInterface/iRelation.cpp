#include "StdAfx.h"
#include "iRelation.h"

#include "iSymbol.h"
#include "iRelationConstraint.h"
#include "iConcept.h"


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
		class BindEachObject
		{

		public:
			BindEachObject(){}
			~BindEachObject(){}

			void operator()(const PairInfo& info)
			{
				//Bind each symbol with related concept.
				info.sPair.first->BindReferredObject(info.cPair.first);
				info.sPair.second->BindReferredObject(info.cPair.second);

			}
		};
		class BindEachNull
		{
		public:
			void operator()(const PairInfo& info)
			{
				//Bind each symbol with related concept.
				info.sPair.first->BindReferredObject(NULL);
				info.sPair.second->BindReferredObject(NULL);
			}
		};


		for_each(pairInfos.begin(),pairInfos.end(),BindEachObject());
		for (unsigned int i=0;i<constraints.size();++i)
		{
			if(!constraints[i]->Satisfy())
			{
				for_each(pairInfos.begin(),pairInfos.end(),BindEachNull());
				return false;
			}
		}

		for_each(pairInfos.begin(),pairInfos.end(),BindEachNull());
		return true;
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

