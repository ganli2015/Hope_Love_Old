#include "StdAfx.h"
#include "DeduceResult.h"

#include "../MindInterface/iRelation.h"

namespace LogicSystem
{
	DeduceResult::DeduceResult(void)
	{
	}

	DeduceResult::DeduceResult( const shared_ptr<iRelation> val )
	{
		_relation.push_back(val);
	}


	DeduceResult::~DeduceResult(void)
	{
	}

	double DeduceResult::Matching( const shared_ptr<iExpression> expre )
	{
		class FindMatchRelation
		{
			shared_ptr<iExpression> _expre;

		public:
			FindMatchRelation(const shared_ptr<iExpression> val):_expre(val){}
			~FindMatchRelation(){}

			bool operator()(const shared_ptr<iRelation> relation)
			{
				return relation->Satisfy(_expre);
			}
		};

		vector<shared_ptr<iRelation>>::iterator it=find_if(_relation.begin(),_relation.end(),FindMatchRelation(expre));

		if(it==_relation.end())
		{
			return 0.;
		}
		else
		{
			return 1.;
		}
	}

}

