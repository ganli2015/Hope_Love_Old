#include "StdAfx.h"
#include "LogicStatement.h"
#include "DeduceResult.h"

#include "../MindInterface/iRelation.h"
#include "../MindInterface/iConceptInteractTable.h"
#include "../MindInterface/iMindElementCreator.h"
#include "../MindInterface/CommonFunction.h"
#include "../MindInterface/iExpression.h"

#include "../Mathmatic/FindSequence.h"

using namespace Mind;

namespace LogicSystem
{
	LogicStatement::LogicStatement(const shared_ptr<iRelation> condition,const shared_ptr<iRelation> result):_relationPair(make_pair(condition,result))
	{
	}


	LogicStatement::~LogicStatement(void)
	{
	}

	shared_ptr<iDeduceResult> LogicStatement::Deduce( const shared_ptr<iExpression> condition ) const
	{
		shared_ptr<Mind::iConceptInteractTable> conditionTable=condition->GetProtoInteractTable();
		if(condition==NULL) return NULL;

		return Deduce(conditionTable);
	}

	shared_ptr<iDeduceResult> LogicStatement::Deduce( const shared_ptr<Mind::iConceptInteractTable> condition ) const
	{
		vector<MindType::ConceptPair> totalPairs=condition->GetAllRelations();
		//Get all sub pairs of condition.
		vector<vector<MindType::ConceptPair>> subConceptPairs=Math::GetAllSubSequence<MindType::ConceptPair>::Get(totalPairs);
		//Search a sub pair sequence that satisfied the relation.
		for (unsigned int i=0;i<subConceptPairs.size();++i)
		{
			//Divide the raw concept pairs into two part one of which for deduction.
			//If satisfy, then connect with the other part.
			//In this way, sub part of <condition> is deduced and lose no information of the other part.

			shared_ptr<iConceptInteractTable> subTable=iMindElementCreator::CreateConceptInteractTable(subConceptPairs[i]);

			if(_relationPair.first->Satisfy(subTable))
			{
				//Append the other part of pairs to the result.
				vector<MindType::ConceptPair> remainPairs=CommonFunction::FilterPartialConceptPairs(totalPairs,subConceptPairs[i]);
				shared_ptr<iRelation> result=_relationPair.first->SymbolResonance(_relationPair.second);
				shared_ptr<iConceptInteractTable> deduceTable=result->GenerateConceptTable();

				for (unsigned int j=0;j<remainPairs.size();++j)
				{
					deduceTable->Add(remainPairs[j].first,remainPairs[j].second);
				}

				return shared_ptr<iDeduceResult>(new DeduceResult<iConceptInteractTable>(deduceTable));	
			}
		}

		return NULL;
	}

	shared_ptr<iDeduceResult> LogicStatement::GenerateResult(const shared_ptr<iRelation> conditionRelation, const shared_ptr<iRelation> resultRelation)
	{
		shared_ptr<iRelation> result=conditionRelation->SymbolResonance(resultRelation);

		if(result!=NULL)
		{
			return shared_ptr<iDeduceResult>(new DeduceResult<iRelation>(result));		
		}
		else
		{
			return NULL;
		}
	}

}

