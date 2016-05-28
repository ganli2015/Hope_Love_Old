#include "StdAfx.h"
#include "ExtractConceptChains.h"

#include "../Mind/CommonFunction.h"
#include "../MindElement/ConceptChain.h"
#include "../MindInterface/iConcept.h"
#include "../MindInterface/iConceptChain.h"
#include "../MindInterface/iMindElementCreator.h"

using namespace Mind;

// map<shared_ptr<Mind::iConcept>,vector<shared_ptr<Mind::iConceptChain>>> ExtractConceptChains::_forwardTable;
// map<shared_ptr<Mind::iConcept>,vector<shared_ptr<Mind::iConceptChain>>> ExtractConceptChains::_backwardTable;

int ExtractConceptChains::_recursiveCount=0;
const int ExtractConceptChains::_recursiveMaxCount=100;

vector<shared_ptr<Mind::iConceptChain>> ExtractConceptChains::Extract( const vector<ConceptPair>& pairs )
{
	vector<ConceptPair> pairs_copy=pairs;
	RemoveBadPairs(pairs_copy);

	vector<shared_ptr<iConceptChain>> res;

	for (unsigned int i=0;i<pairs_copy.size();++i)
	{
		_recursiveCount=0;
		shared_ptr<iConceptChain> relatedChain_Back=iMindElementCreator::CreateConceptChain();
		relatedChain_Back->Push_Back(pairs_copy[i].first);
		vector<shared_ptr<iConceptChain>> backChains;
		Recursive_Search(Backward,pairs_copy[i].first,pairs_copy,relatedChain_Back,backChains);

		_recursiveCount=0;
		shared_ptr<iConceptChain> relatedChain_Forward=iMindElementCreator::CreateConceptChain();
		relatedChain_Forward->Push_Back(pairs_copy[i].second);
		vector<shared_ptr<iConceptChain>> forwardChains;
		Recursive_Search(Forward,pairs_copy[i].second,pairs_copy,relatedChain_Forward,forwardChains);

		vector<shared_ptr<iConceptChain>> closedChain_back=CollectAndRemoveClosedChains(backChains);
		vector<shared_ptr<iConceptChain>> closedChain_for=CollectAndRemoveClosedChains(forwardChains);

		//合并，遍历所有组合方式。
		vector<shared_ptr<iConceptChain>> curChains=Merge(backChains,forwardChains);
		res.insert(res.end(),curChains.begin(),curChains.end());
		res.insert(res.end(),closedChain_back.begin(),closedChain_back.end());
		res.insert(res.end(),closedChain_for.begin(),closedChain_for.end());
	}

	return res;
}

void ExtractConceptChains::Recursive_Search(const SearchDir dir,
	const shared_ptr<Mind::iConcept> curConcept,
	const vector<ConceptPair>& pairs,
	const shared_ptr<Mind::iConceptChain>& relatedChain,//记录遍历相邻节点前的包含 curConcept的Chain，便于相邻的iConcept能添加上去。
	vector<shared_ptr<Mind::iConceptChain>>& chains )//所有Chains
{
	// 	if(HasSearched(curConcept,dir,chains))//如果已经递归搜索过curConcept，那么直接从表格里读取。
	// 	{
	// 		return;
	// 	}
	_recursiveCount++;
	Check(_recursiveCount<=_recursiveMaxCount);

	if(relatedChain==NULL)
	{
		throw runtime_error("Error in Recursive_Search");
	}

	//获得相邻的iConcept
	vector<shared_ptr<iConcept>> adjConcepts;
	if (dir==Forward)
	{
		adjConcepts=GetForwardAdjConcepts(curConcept,pairs);
	}
	else
	{
		adjConcepts=GetBackwordAdjConcepts(curConcept,pairs);
	}

	if(adjConcepts.empty())//如果没有相邻的iConcept，那么把和curConcept相关的Chain都存到<chain>里，并停止递归。
	{
		chains.push_back(relatedChain);
		return;
	}

	vector<shared_ptr<Mind::iConceptChain>> curChains;//存储遍历相邻节点之后包含curConcept的所有的chain
	for (unsigned int i=0;i<adjConcepts.size();++i)
	{
		//对<relatedChains>补充，建立包含forwardConcepts[i]的Chains。
		shared_ptr<iConceptChain> newRelatedChains=AppendToChains(adjConcepts[i],relatedChain,dir);
		if(relatedChain->Contain(adjConcepts[i]))//如果这是个闭环，那么就无需递归下去，但是这个闭环会被保留下来。
		{
			curChains.push_back(newRelatedChains);
		}
		else
			Recursive_Search(dir,adjConcepts[i],pairs,newRelatedChains,curChains);
	}

	//记录curConcept所对应的chains，便于以后使用。
	// 	if (dir==Forward)
	// 	{
	// 		_forwardTable[curConcept]=curChains;
	// 	}
	// 	else
	// 	{
	// 		_backwardTable[curConcept]=curChains;
	// 	}

	chains.insert(chains.end(),curChains.begin(),curChains.end());
}

vector<shared_ptr<Mind::iConcept>> ExtractConceptChains::GetForwardAdjConcepts(const shared_ptr<Mind::iConcept> concept, const vector<ConceptPair>& pairs )
{
	vector<shared_ptr<Mind::iConcept>> res;
	for (unsigned int i=0;i<pairs.size();++i)
	{
		if(concept->Same(pairs[i].first))
		{
			res.push_back(pairs[i].second);
		}
	}

	return res;
}

vector<shared_ptr<Mind::iConcept>> ExtractConceptChains::GetBackwordAdjConcepts( const shared_ptr<Mind::iConcept> concept,const vector<ConceptPair>& pairs )
{
	vector<shared_ptr<Mind::iConcept>> res;
	for (unsigned int i=0;i<pairs.size();++i)
	{
		if(concept->Same(pairs[i].second))
		{
			res.push_back(pairs[i].first);
		}
	}

	return res;
}

shared_ptr<Mind::iConceptChain> ExtractConceptChains::AppendToChains( const shared_ptr<iConcept> concept,const shared_ptr<Mind::iConceptChain>& chains ,const SearchDir dir)
{
	shared_ptr<Mind::iConceptChain> res=iMindElementCreator::CreateConceptChain(chains->GetConceptVec());
	if(dir==Forward)
	{
		res->Push_Back(concept);
	}
	else
	{
		res->Push_Front(concept);
	}

	return res;
}

// bool ExtractConceptChains::HasSearched( const shared_ptr<Mind::iConcept> concept,const SearchDir dir,vector<shared_ptr<Mind::iConceptChain>>& chains )
// {
// 	if(dir==Forward)
// 	{
// 		if(_forwardTable.find(concept)!=_forwardTable.end())
// 		{
// 			chains=_forwardTable[concept];
// 			return true;
// 		}
// 		else
// 		{
// 			return false;
// 		}
// 	}
// 	else
// 	{
// 		if(_backwardTable.find(concept)!=_backwardTable.end())
// 		{
// 			chains=_backwardTable[concept];
// 			return true;
// 		}
// 		else
// 		{
// 			return false;
// 		}
// 	}
// }

vector<shared_ptr<Mind::iConceptChain>> ExtractConceptChains::Merge( const vector<shared_ptr<Mind::iConceptChain>>& backChains,
	const vector<shared_ptr<Mind::iConceptChain>>& forwardChains )
{
	vector<shared_ptr<Mind::iConceptChain>> res;
	res.reserve(backChains.size()*forwardChains.size());
	for (unsigned int i=0;i<backChains.size();++i)
	{		
		for (unsigned int j=0;j<forwardChains.size();++j)
		{
			shared_ptr<iConceptChain> newChain=backChains[i]->Copy();
			//newChain->Reverse();
			newChain->Append(forwardChains[j]);
			res.push_back(newChain);
		}
	}

	return res;
}

void ExtractConceptChains::RemoveBadPairs( vector<ConceptPair>& pairs )
{
	//去掉含有相同iConcept的pair
	for (vector<ConceptPair>::iterator it=pairs.begin();it!=pairs.end();)
	{
		if(it->first->Same(it->second))
		{
			it=pairs.erase(it);
		}
		else
		{
			++it;
		}
	}


	class SameConceptPair
	{
		const ConceptPair _val;
	public:
		SameConceptPair(const ConceptPair& val):_val(val){}
		~SameConceptPair(){}

		bool operator()(const ConceptPair& right)
		{
			if(!_val.first->Same(right.first))
			{
				return false;
			}
			if(!_val.second->Same(right.second))
			{
				return false;
			}

			return true;
		}
	};

	//去掉相同的pair
	for (vector<ConceptPair>::iterator it=pairs.begin();it!=pairs.end();)
	{
		vector<ConceptPair>::iterator findIt=find_if(it+1,pairs.end(),SameConceptPair(*it));
		if(findIt!=pairs.end())
		{
			it=pairs.erase(it);
		}
		else
		{
			++it;
		}
	}
}

bool ExtractConceptChains::IsClosedChain( const shared_ptr<iConceptChain> chain )
{
	if(chain->Size()==0 || chain->Size()==1)
	{
		return false;
	}

	if(chain->Front()->Same(chain->Back()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

vector<shared_ptr<Mind::iConceptChain>> ExtractConceptChains::CollectAndRemoveClosedChains( vector<shared_ptr<iConceptChain>>& inputChains )
{
	vector<shared_ptr<Mind::iConceptChain>> res;
	for (vector<shared_ptr<iConceptChain>>::iterator it=inputChains.begin();it!=inputChains.end();)
	{
		if(IsClosedChain(*it))
		{
			res.push_back(*it);
			it=inputChains.erase(it);
		}
		else
		{
			++it;
		}
	}

	return res;
}

// void ExtractConceptChains::ClearTable()
// {
// 	_backwardTable.clear();
// 	_forwardTable.clear();
// }

