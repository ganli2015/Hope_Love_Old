#include "StdAfx.h"
#include "Logic.h"
#include "ReduceResult.h"

#include "../MindInterface/iExpression.h"
#include "../MindInterface/iCerebrum.h"
#include "../MindInterface/iDeduceResult.h"
#include "../MindInterface/iConceptInteractTable.h"
#include "../MindInterface/PublicTypedef.h"
#include "../MindInterface/iMindElementCreator.h"
#include "../MindInterface/CommonFunction.h"
#include "../MindInterface/iConcept.h"

#include "../Mathmatic/MathTool.h"
#include "../Mathmatic/FindSequence.h"

using namespace Math;
using namespace Mind;

namespace LogicSystem
{
	Logic::Logic(void)
	{
	}


	Logic::~Logic(void)
	{
	}

	LogicSystem::LogicResult Logic::Determine( const shared_ptr<iExpression> condition,const shared_ptr<iExpression> conclusion ) const
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

	vector<shared_ptr<iDeduceResult>> Logic::Deduce( const shared_ptr<iExpression> condition ) const
	{
		Mind::iCerebrum* brain=Mind::iCerebrum::Instance();
		return brain->Deduce(condition);
	}

	vector<shared_ptr<iDeduceResult>> Logic::FinalDeduce( const shared_ptr<iExpression> condition ) const
	{
		return vector<shared_ptr<iDeduceResult>>();
	}

	vector<shared_ptr<iReduceResult>> Logic::Reduce( const shared_ptr<Mind::iConceptInteractTable> conceptTable ) const
	{
		vector<shared_ptr<iReduceResult>> res;

		Mind::iCerebrum* brain=Mind::iCerebrum::Instance();
		assert(brain!=NULL);
		if(brain==NULL) 
		{
			return res;
		}

		vector<ConceptPair> conceptPairs=conceptTable->GetAllRelations();
		//Get all sub sequence of <conceptPairs>.
		vector<vector<ConceptPair>> allSubConceptPairs=Math::GetAllSubSequence<ConceptPair>::Get(conceptPairs);
		for (unsigned int i=0;i<allSubConceptPairs.size();++i)
		{
			vector<ConceptPair> subPairs=allSubConceptPairs[i];
			vector<shared_ptr<iReduceResult>> reduceResult=ReduceConceptPairSequence(subPairs,conceptPairs,brain);
			res.insert(res.end(),reduceResult.begin(),reduceResult.end());
		}

		return res;
	}

	vector<shared_ptr<iReduceResult>> Logic::ReduceConceptPairSequence(const vector<ConceptPair>& subPairs,const vector<ConceptPair>& totalPairs,const iCerebrum* brain) const
	{
		vector<shared_ptr<iReduceResult>> res;

		//Convert to iConceptInteractTable.
		shared_ptr<iConceptInteractTable> table=iMindElementCreator::CreateConceptInteractTable(subPairs);
		//Find concepts matching with description <table>.
		vector<DescMatchedConceptInfo> matchedInfos;
		brain->FindConceptWithMatchedDisc(table,matchedInfos);

		vector<ConceptPair> remainingPairs=FilterPartialConceptPairs(totalPairs,subPairs);
		for (unsigned int j=0;j<matchedInfos.size();++j)
		{
			shared_ptr<iReduceResult> reduceResult=ReduceFromMatchedConcept(matchedInfos[j],subPairs,remainingPairs);
			if(reduceResult!=NULL)
			{
				res.push_back(reduceResult);
			}
		}

		return res;
	}

	shared_ptr<iReduceResult> Logic::ReduceFromMatchedConcept(const DescMatchedConceptInfo& matchedConceptInfo,
		const vector<ConceptPair>& subPairs,const vector<ConceptPair>& remainingPairs) const
	{
		shared_ptr<iReduceResult> res=NULL;

		//Get to concept of matched concept.
		shared_ptr<iConcept> toConcept=matchedConceptInfo.toConcept;
		//A ConceptPair that contains <toConcept>.
		ConceptPair toConceptPair;
		//Find <toConceptPair> in <subPairs>.
		if(FindPair_SameFirstConcept(subPairs,toConcept,toConceptPair))
		{
			//If <toConcept> is the first concept of <toConceptPair>,
			//then find the connected pair of remaining pairs,
			//i.e. find the pair whose first concept equals to the second concept of <toConceptPair>.
			if(FindPair_SameFirstConcept(remainingPairs,toConceptPair.second,ConceptPair()))
			{
				//If find the connected pair, then hold the concept connected to <matchedConcept>. 
				ConceptPair reducedPair(matchedConceptInfo.matchedConcept,toConceptPair.second);
				vector<ConceptPair> newPairs(remainingPairs);
				newPairs.push_back(reducedPair);
				shared_ptr<iConceptInteractTable> newTable=iMindElementCreator::CreateConceptInteractTable(newPairs);

				shared_ptr<ReduceResult> result(new ReduceResult(newTable));
				res=result;
			}
			else if(remainingPairs.empty()) //If not find the connected pair and there are no remaining pairs ,then output the matched single concept.
			{
				shared_ptr<ReduceResult_SingleConcept> result(new ReduceResult_SingleConcept(matchedConceptInfo.matchedConcept));
				res=result;
			}
		}
		else if(FindPair_SameSecondConcept(subPairs,toConcept,toConceptPair))
		{
			//Similar with the above.
			if(FindPair_SameSecondConcept(remainingPairs,toConceptPair.first,ConceptPair()))
			{
				ConceptPair reducedPair(toConceptPair.first,matchedConceptInfo.matchedConcept);
				vector<ConceptPair> newPairs(remainingPairs);
				newPairs.push_back(reducedPair);
				shared_ptr<iConceptInteractTable> newTable=iMindElementCreator::CreateConceptInteractTable(newPairs);

				shared_ptr<ReduceResult> result(new ReduceResult(newTable));
				res=result;
			}
			else if(remainingPairs.empty())
			{
				shared_ptr<ReduceResult_SingleConcept> result(new ReduceResult_SingleConcept(matchedConceptInfo.matchedConcept));
				res=result;
			}
		}

		return res;
	}

	vector<Logic::ConceptPair> Logic::FilterPartialConceptPairs( const vector<ConceptPair>& total, const vector<ConceptPair>& partial ) const
	{
		vector<Logic::ConceptPair> res(total);

		for (unsigned int i=0;i<partial.size();++i)
		{
			vector<ConceptPair>::iterator samePairIter=find_if(res.begin(),res.end(),CommonFunction::SameConceptPair(partial[i].first,partial[i].second));
			assert(samePairIter!=res.end());

			res.erase(samePairIter);
		}

		return res;
	}

	bool Logic::FindPair_SameFirstConcept( const vector<ConceptPair>& total,const shared_ptr<Mind::iConcept> concept,Logic::ConceptPair& resultPair ) const
	{
		class FindPair
		{
			shared_ptr<Mind::iConcept> _concept;
		public:
			FindPair(const shared_ptr<Mind::iConcept> concept):_concept(concept){}
			~FindPair(){}

			bool operator()(const ConceptPair& pair)
			{
				if(pair.first->Same(_concept))
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		};

		vector<ConceptPair>::const_iterator findePair=find_if(total.begin(),total.end(),FindPair(concept));
		if(findePair==total.end())
		{
			return false;
		}
		else
		{
			resultPair=*findePair;
			return true;
		}

	}

	bool Logic::FindPair_SameSecondConcept( const vector<ConceptPair>& total,const shared_ptr<Mind::iConcept> concept,Logic::ConceptPair& resultPair ) const
	{
		class FindPair
		{
			shared_ptr<Mind::iConcept> _concept;
		public:
			FindPair(const shared_ptr<Mind::iConcept> concept):_concept(concept){}
			~FindPair(){}

			bool operator()(const ConceptPair& pair)
			{
				if(pair.second->Same(_concept))
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		};

		vector<ConceptPair>::const_iterator findePair=find_if(total.begin(),total.end(),FindPair(concept));
		if(findePair==total.end())
		{
			return false;
		}
		else
		{
			resultPair=*findePair;
			return true;
		}
	}

}

