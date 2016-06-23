#include "StdAfx.h"
#include "ExtractConceptChains.h"

#include "../Mind/CommonFunction.h"
#include "../MindElement/ConceptChain.h"
#include "../MindInterface/iConcept.h"
#include "../MindInterface/iConceptChain.h"
#include "../MindInterface/iMindElementCreator.h"

using namespace Mind;


int ExtractConceptChains::_recursiveCount=0;
const int ExtractConceptChains::_recursiveMaxCount=100;

vector<shared_ptr<Mind::iConceptChain>> ExtractConceptChains::Extract( const vector<ConceptPair>& pairs )
{
	vector<ConceptPair> pairs_copy=pairs;
	//Remove bad concept pairs as they will cause the following iteration divergent.
	RemoveBadPairs(pairs_copy);

	vector<shared_ptr<iConceptChain>> res;

	for (unsigned int i=0;i<pairs_copy.size();++i)
	{
		//For each pair containing two concepts , From and To,
		//search backward of From and get a chain whose tail is From.
		//Then search forward of To and get a chain whose head is To.
		//Lastly, merge back chains and forward chains considering all combinations.

		//Search backward.
		//Record the count of iterations to avoid endless loop.
		_recursiveCount=0;
		shared_ptr<iConceptChain> relatedChain_Back=iMindElementCreator::CreateConceptChain();
		relatedChain_Back->Push_Back(pairs_copy[i].first);
		vector<shared_ptr<iConceptChain>> backChains;
		Recursive_Search(Backward,pairs_copy[i].first,pairs_copy,relatedChain_Back,backChains);

		//Search forward.
		_recursiveCount = 0;
		shared_ptr<iConceptChain> relatedChain_Forward=iMindElementCreator::CreateConceptChain();
		relatedChain_Forward->Push_Back(pairs_copy[i].second);
		vector<shared_ptr<iConceptChain>> forwardChains;
		Recursive_Search(Forward,pairs_copy[i].second,pairs_copy,relatedChain_Forward,forwardChains);

		//Collect closed chains which will be appended to results 
		vector<shared_ptr<iConceptChain>> closedChain_back=CollectAndRemoveClosedChains(backChains);
		vector<shared_ptr<iConceptChain>> closedChain_for=CollectAndRemoveClosedChains(forwardChains);

		//Merge back chains and forward chains considering all combinations.
		//Each combination is a chain in <pairs>.
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
	const shared_ptr<Mind::iConceptChain>& relatedChain,
	vector<shared_ptr<Mind::iConceptChain>>& chains )
{
	_recursiveCount++;
	Check(_recursiveCount<=_recursiveMaxCount);

	if(relatedChain==NULL)
	{
		throw runtime_error("Error in Recursive_Search");
	}

	//Get adjacent concepts.
	//They will extend <relatedChain>.
	vector<shared_ptr<iConcept>> adjConcepts;
	if (dir==Forward)
	{
		adjConcepts=GetForwardAdjConcepts(curConcept,pairs);
	}
	else
	{
		adjConcepts=GetBackwordAdjConcepts(curConcept,pairs);
	}

	//If there is no adjacent concepts, then it indicates I search the end of the chain.
	//Recursion is end.
	if(adjConcepts.empty())
	{
		chains.push_back(relatedChain);
		return;
	}

	//<curChains> store chains containing <curConcept>.
	//They will be computed in the recursion of <curConcept>'s adjacent concepts, i.e,<adjConcepts>.
	//All <curChains> of <adjConcepts> construct <curChains> of <curConcept>.
	vector<shared_ptr<Mind::iConceptChain>> curChains;
	for (unsigned int i=0;i<adjConcepts.size();++i)
	{
		//Extend <relatedChain> with <adjConcepts[i]>.
		//<newRelatedChains> contributes to the NEW recursion in terms of <adjConcepts[i]>.
		shared_ptr<iConceptChain> newRelatedChains=AppendToChains(adjConcepts[i],relatedChain,dir);
		//If <relatedChain> is a closed chain, recursion is end.
		//Otherwise , it will become endless loop.
		if(relatedChain->Contain(adjConcepts[i]))
		{
			curChains.push_back(newRelatedChains);
		}
		else
			Recursive_Search(dir,adjConcepts[i],pairs,newRelatedChains,curChains);
	}

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


vector<shared_ptr<Mind::iConceptChain>> ExtractConceptChains::Merge( const vector<shared_ptr<Mind::iConceptChain>>& backChains,
	const vector<shared_ptr<Mind::iConceptChain>>& forwardChains )
{
	//Merge all combination of <backChains> and <forwardChains>.
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
	//Remove pairs whose first and second concepts are the same.
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

	//Remove duplicated pairs .
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
