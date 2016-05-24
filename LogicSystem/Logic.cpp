#include "StdAfx.h"
#include "Logic.h"

#include "../MindInterface/iExpression.h"
#include "../MindInterface/iCerebrum.h"
#include "../MindInterface/iDeduceResult.h"

#include "../Mathmatic/MathTool.h"

using namespace Math;

namespace LogicSystem
{
	Logic::Logic(void)
	{
	}


	Logic::~Logic(void)
	{
	}

	LogicSystem::LogicResult Logic::Determine( const shared_ptr<iExpression> condition,const shared_ptr<iExpression> conclusion )
	{
		class FindMatchRelation
		{
			shared_ptr<iExpression> _expre;

		public:
			FindMatchRelation(const shared_ptr<iExpression> val):_expre(val){}
			~FindMatchRelation(){}

			bool operator()(const shared_ptr<iDeduceResult> relation)
			{
				if(DoubleCompare(relation->Matching(_expre),1)==0)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		};

		Mind::iCerebrum* brain=Mind::iCerebrum::Instance();
		vector<shared_ptr<iDeduceResult>> results=brain->Deduce(condition);
		vector<shared_ptr<iDeduceResult>>::iterator it=find_if(results.begin(),results.end(),FindMatchRelation(conclusion));

		if(it==results.end())
		{
			return False;
		}
		else
		{
			return True;
		}

	}

	vector<shared_ptr<iDeduceResult>> Logic::Deduce( const shared_ptr<iExpression> condition )
	{
		Mind::iCerebrum* brain=Mind::iCerebrum::Instance();
		return brain->Deduce(condition);
	}

}

