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

#include "../CommonTools/LogWriter.h"

#include <set>

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

	vector<shared_ptr<iDeduceResult>> Logic::Deduce( const shared_ptr<Mind::iConceptInteractTable> condition ) const
	{
		Mind::iCerebrum* brain=Mind::iCerebrum::Instance();
		return brain->Deduce(condition);
	}

	vector<shared_ptr<iDeduceResult>> Logic::FinalDeduce( const shared_ptr<iExpression> condition ) const
	{
		vector<shared_ptr<iDeduceResult>> res;
		shared_ptr<iConceptInteractTable> conditionTable=condition->GetProtoInteractTable();
		Mind::iCerebrum* brain=Mind::iCerebrum::Instance();
		if(brain==NULL) return res;
		
		//Generate initial deduction results.
		//If they are not empty, it indicate that the <condition> can at least deduce something 
		//and the following iteration is based on <initDeduceResults>.
		vector<shared_ptr<iDeduceResult>> initDeduceResults=brain->Deduce(conditionTable);
		if(initDeduceResults.empty()) return res;		

		//A table list for iteration.Each table of it needs to be reduced and deduced.
		list<shared_ptr<iConceptInteractTable>> curDeduceTables=ToConceptTable(initDeduceResults);	
		LOG_DESC("Initial Deduced Tables: ",curDeduceTables);

		ConceptList conceptResults;
		TableList finalDeduceTables;
		do 
		{
			//<reducedTables> contains the tables reduced from <curDeduceTables>.
			//If one table reduces to nothing, it will not appear in <reducedTables>.
			TableList reducedTables;
			TableList noChangedTables;
			ReduceTableList(curDeduceTables,reducedTables,noChangedTables,conceptResults);
			LOG_DESC("Reduced Tables after reduction: ",reducedTables);

			curDeduceTables.clear();		
			DeduceTableList(reducedTables,noChangedTables,curDeduceTables);
			LOG_DESC("Deduced Tables after deduction: ",curDeduceTables);

			//<noChangedTables> contains table with no reduction and deduction during current iteration,
			//and they will be kicked out from iteration and become the final results.
			finalDeduceTables.insert(finalDeduceTables.end(),noChangedTables.begin(),noChangedTables.end());

		} while (!curDeduceTables.empty());

		return AssembleDeduceResults(conceptResults,finalDeduceTables);
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
		return CommonFunction::FilterPartialConceptPairs(total,partial);
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

	list<shared_ptr<Mind::iConceptInteractTable>> Logic::ToConceptTable( const vector<shared_ptr<iDeduceResult>>& deduceResults )const
	{
		list<shared_ptr<Mind::iConceptInteractTable>> res;

		for (unsigned int i=0;i<deduceResults.size();++i)
		{
			shared_ptr<iConceptInteractTable> table=deduceResults[i]->GetConceptTable();
			assert(table!=NULL);

			res.push_back(table);
		}

		return res;
	}

	list<shared_ptr<Mind::iConceptInteractTable>> Logic::ToConceptTable( const vector<shared_ptr<iReduceResult>>& reduceResults )const
	{
		list<shared_ptr<Mind::iConceptInteractTable>> res;

		for (unsigned int i=0;i<reduceResults.size();++i)
		{
			shared_ptr<iConceptInteractTable> table=reduceResults[i]->GetConceptTable();
			if(table!=NULL)
			{
				res.push_back(table);
			}
		}

		return res;
	}

	list<shared_ptr<Mind::iConcept>> Logic::ToConceptList( const vector<shared_ptr<iReduceResult>>& reduceResults )const
	{
		list<shared_ptr<Mind::iConcept>> res;

		for (unsigned int i=0;i<reduceResults.size();++i)
		{
			shared_ptr<iConcept> con=reduceResults[i]->GetSingleConcept();
			if(con!=NULL)
			{
				res.push_back(con);
			}
		}

		return res;
	}

	void Logic::ReduceTableList( const TableList& tableList,
		TableList& reducedTables,TableList& noChangedTables,ConceptList& conceptResults )const
	{
		for (TableIterConst table=tableList.begin();table!=tableList.end();++table)
		{
			vector<shared_ptr<iReduceResult>> reduceRes=Reduce(*table);
			TableList reduceTables=ToConceptTable(reduceRes);
			//If there are some iReduceResult, then replace the current table with new reduced tables.
			//The current table will not appear in the next iteration.
			if(!reduceTables.empty())
			{
				reducedTables.insert(reducedTables.end(),reduceTables.begin(),reduceTables.end());
			}

			//Get concept list.
			//If it is not empty, the list will be appended to the final result and the current table will not appear in the next iteration.
			ConceptList reduceConcepts=ToConceptList(reduceRes);
			conceptResults.insert(conceptResults.end(),reduceConcepts.begin(),reduceConcepts.end());

			if(reduceTables.empty() && reduceConcepts.empty())
			{
				noChangedTables.push_back(*table);
			}
		}
	}

	void Logic::DeduceTableList( const TableList& reducedTables,
		TableList& noChangedTables,
		TableList& tableForIter ) const
	{
		for (TableIterConst table=reducedTables.begin();table!=reducedTables.end();++table)
		{
			vector<shared_ptr<iDeduceResult>> deduceRes=Deduce(*table);
			TableList deduceTable=ToConceptTable(deduceRes);
			//Deduce from the results from reduction.
			//If there is any iDeduceResult, it will replace the current table.
			//Otherwise ,the current table will be hold.
			if(!deduceTable.empty())
			{
				tableForIter.insert(tableForIter.end(),deduceTable.begin(),deduceTable.end());
			}
			else
			{
				tableForIter.push_back(*table);
			}
		}

		iCerebrum* brain=iCerebrum::Instance();
		for (TableIterConst table=noChangedTables.begin();table!=noChangedTables.end();)
		{
			vector<shared_ptr<iDeduceResult>> deduceRes=Deduce(*table);
			TableList deduceTable=ToConceptTable(deduceRes);
			//If we can deduce something from <noChangedTables>, the current table will be kicked out from <noChangedTables>.
			//Otherwise, the current table will stay in <noChangedTables>.
			if(!deduceTable.empty())
			{
				tableForIter.insert(tableForIter.end(),deduceTable.begin(),deduceTable.end());
				table=noChangedTables.erase(table);
			}
			else
			{
				++table;
			}
		}
	}

	vector<shared_ptr<iDeduceResult>> Logic::AssembleDeduceResults( const ConceptList& conceptResults, const TableList& finalDeduceTables )  const
	{
		set<shared_ptr<iConcept>> conceptResultsSet(conceptResults.begin(),conceptResults.end());
		set<shared_ptr<iConceptInteractTable>> finalDeduceTablesSet(finalDeduceTables.begin(),finalDeduceTables.end());

		vector<shared_ptr<iDeduceResult>> res(conceptResultsSet.size()+finalDeduceTablesSet.size());

		transform(conceptResultsSet.begin(),conceptResultsSet.end(),res.begin(),ToDeduceResult<iConcept>());
		transform(finalDeduceTablesSet.begin(),finalDeduceTablesSet.end(),res.begin()+conceptResultsSet.size(),ToDeduceResult<iConceptInteractTable>());

		return res;
	}

}

