#include "StdAfx.h"
#include "DeduceResult.h"

#include "../MindInterface/iRelation.h"
#include "../MindInterface/iConceptInteractTable.h"

namespace LogicSystem
{
	DeduceResult::DeduceResult(void)
	{
	}

	DeduceResult::DeduceResult( const shared_ptr<iRelation> val )
	{
		Set(val);
	}


	DeduceResult::~DeduceResult(void)
	{
	}

	double DeduceResult::Matching( const shared_ptr<iExpression> expre )
	{
// 		class FindMatchRelation
// 		{
// 			shared_ptr<iExpression> _expre;
// 
// 		public:
// 			FindMatchRelation(const shared_ptr<iExpression> val):_expre(val){}
// 			~FindMatchRelation(){}
// 
// 			bool operator()(const ResultInfo& relation)
// 			{
// 				return relation.result->Satisfy(_expre);
// 			}
// 		};
// 
// 		vector<ResultInfo>::iterator it=find_if(_relation.begin(),_relation.end(),FindMatchRelation(expre));

		if(!_result->Satisfy(expre))
		{
			return 0.;
		}
		else
		{
			return _confidence;
		}
	}

	void DeduceResult::Set( const shared_ptr<iRelation> val ,const double confidence)
	{
		_result=val;
		_confidence=confidence;
	}

	shared_ptr<Mind::iConceptInteractTable> DeduceResult::GetConceptTable() const
	{
		if(_result==NULL) 
		{
			return NULL;
		}
		else
			return _result->GenerateConceptTable();
	}

}

