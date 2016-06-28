#include "StdAfx.h"
#include "LogicStatement.h"
#include "DeduceResult.h"

#include "../MindInterface/iRelation.h"
#include "../MindInterface/iConceptInteractTable.h"
#include "../MindInterface/iMindElementCreator.h"
#include "../MindInterface/CommonFunction.h"
#include "../MindInterface/iExpression.h"

#include "../Mathmatic/FindSequence.h"

#include "../CommonTools/GeneralFunctor.h"

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
				//Compute the other part of pairs to the result.
				vector<MindType::ConceptPair> remainPairs=CommonFunction::FilterPartialConceptPairs(totalPairs,subConceptPairs[i]);
				shared_ptr<iRelation> result=_relationPair.first->SymbolResonance(_relationPair.second);
				
				//Generate result according to concept table or single concept in iDeduceResult.
				//Only one of them can be valid and may generate a result.
				//If either of iDeduceResult is not null, return it.
				shared_ptr<iDeduceResult> deduceResult = GenerateConceptTableResult(result, remainPairs);
				if(deduceResult ==NULL)
				{
					deduceResult = GenerateSingleConceptResult(result, subConceptPairs[i], remainPairs);				
				}
				if (deduceResult != NULL)
				{
					return deduceResult;
				}
			}
		}

		return NULL;
	}

	shared_ptr<iDeduceResult> LogicStatement::GenerateConceptTableResult(const shared_ptr<iRelation> resultRelation,const vector<MindType::ConceptPair>& remainPairs) const
	{
		shared_ptr<iConceptInteractTable> deduceTable = resultRelation->GenerateConceptTable();
		if (deduceTable==NULL)
		{
			return NULL;
		}

		CommonFunction::AppendToInteractTable(remainPairs, deduceTable);

		return shared_ptr<iDeduceResult>(new DeduceResult<iConceptInteractTable>(deduceTable));
	}

	shared_ptr<iDeduceResult> LogicStatement::GenerateSingleConceptResult(const shared_ptr<iRelation> resultRelation, 
		const vector<MindType::ConceptPair>& subPairs, const vector<MindType::ConceptPair>& remainPairs) const
	{
		shared_ptr<iConcept> deduceConcept = resultRelation->GenerateSingleConcept();
		if(deduceConcept==NULL)
		{
			return NULL;
		}

		//If there is no <remainPairs>, directly append one single concept to iDeduceResult.
		if (remainPairs.empty())
		{
			return shared_ptr<iDeduceResult>(new DeduceResult<iConcept>(deduceConcept));
		}

		//If there are <remainPairs>, then one single concept cannot live with concept pairs in iDeduceResult.
		//Then I try to transform the single concept to a concept pair as follows:

		//Find a concept pair of <subPairs> whose second concept or first concept connects to <remainPairs>.
		//Then connect the single concept with its second concept and make it a concept pair.
		//Note!! Currently only find one concept pair!!
		//The new created concept pair reserves information of how <subPairs> connect to <remainPairs> and the connection is retained.
		MindType::ConceptPair newConceptPair;
		if (TransformConceptToConceptPair(deduceConcept, subPairs, remainPairs, newConceptPair))
		{
			shared_ptr<iConceptInteractTable> resultTable = iMindElementCreator::CreateConceptInteractTable();
			resultTable->Add(newConceptPair.first, newConceptPair.second);
			CommonFunction::AppendToInteractTable(remainPairs, resultTable);

			return shared_ptr<iDeduceResult>(new DeduceResult<iConceptInteractTable>(resultTable));
		}
		else
		{
			return NULL;
		}
		
	}

	bool LogicStatement::TransformConceptToConceptPair(const shared_ptr<iConcept> concept, 
		const vector<MindType::ConceptPair>& subPairs, const vector<MindType::ConceptPair>& remainPairs,
		MindType::ConceptPair& newConceptPair) const
	{
		//Find a concept pair of <subPairs> whose SECOND concept connects to <remainPairs>.
		CREATE_FUNCTOR_IR(FindForwardConnection, vector<MindType::ConceptPair>, MindType::ConceptPair, bool,
			if (LogicStatement::HasForwardConnection(input, _init))
			{
				return true;
			}
			else
			{
				return false;
			}
		);
		vector<MindType::ConceptPair>::const_iterator findForwardIter = find_if(subPairs.begin(), subPairs.end(), FindForwardConnection(remainPairs));
		if (findForwardIter != subPairs.end())
		{
			newConceptPair = make_pair(concept, findForwardIter->second);
			return true;
		}

		//If not find above concept pair, then find a concept pair of <subPairs> whose FIRST concept connects to <remainPairs>.
		CREATE_FUNCTOR_IR(FindBackwardConnection, vector<MindType::ConceptPair>, MindType::ConceptPair, bool,
			if (LogicStatement::HasBackwardConnection(input, _init))
			{
				return true;
			}
			else
			{
				return false;
			}
		);
		vector<MindType::ConceptPair>::const_iterator findBackwardIter = find_if(subPairs.begin(), subPairs.end(), FindBackwardConnection(remainPairs));
		if (findBackwardIter != subPairs.end())
		{
			newConceptPair = make_pair(findBackwardIter->second,concept);
			return true;
		}

		//If both failed, then fail to transform concept to concept pair.
		return false;
	}

	bool LogicStatement::HasForwardConnection(const MindType::ConceptPair& pair, const vector<MindType::ConceptPair>& remainPairs)
	{
		CREATE_FUNCTOR_IR(SameWithFirstConcept,shared_ptr<iConcept>,MindType::ConceptPair,bool,
			if (input.first->Same(_init))
			{
				return true;
			}
			else
			{
				return false;
			}
		);

		vector<MindType::ConceptPair>::const_iterator findIter = find_if(remainPairs.begin(), remainPairs.end(), SameWithFirstConcept(pair.second));
		if(findIter!=remainPairs.end())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool LogicStatement::HasBackwardConnection(const MindType::ConceptPair& pair, const vector<MindType::ConceptPair>& remainPairs)
	{
		CREATE_FUNCTOR_IR(SameWithSecondConcept, shared_ptr<iConcept>, MindType::ConceptPair, bool,
			if (input.second->Same(_init))
			{
				return true;
			}
			else
			{
				return false;
			}
		);

		vector<MindType::ConceptPair>::const_iterator findIter = find_if(remainPairs.begin(), remainPairs.end(), SameWithSecondConcept(pair.first));
		if (findIter != remainPairs.end())
		{
			return true;
		}
		else
		{
			return false;
		}
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

