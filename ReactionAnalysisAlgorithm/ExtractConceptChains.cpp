#include "StdAfx.h"
#include "ExtractConceptChains.h"

#include "../Mind/Concept.h"
#include "../Mind/ConceptChain.h"
#include "../Mind/CommonFunction.h"

using namespace Mind;

// map<shared_ptr<Mind::Concept>,vector<shared_ptr<Mind::ConceptChain>>> ExtractConceptChains::_forwardTable;
// map<shared_ptr<Mind::Concept>,vector<shared_ptr<Mind::ConceptChain>>> ExtractConceptChains::_backwardTable;

int ExtractConceptChains::_recursiveCount=0;
const int ExtractConceptChains::_recursiveMaxCount=100;

vector<shared_ptr<Mind::ConceptChain>> ExtractConceptChains::Extract( const vector<ConceptPair>& pairs )
{
	vector<ConceptPair> pairs_copy=pairs;
	RemoveBadPairs(pairs_copy);

	vector<shared_ptr<ConceptChain>> res;

	for (unsigned int i=0;i<pairs_copy.size();++i)
	{
		_recursiveCount=0;
		shared_ptr<ConceptChain> relatedChain_Back(new ConceptChain());
		relatedChain_Back->Push_Back(pairs_copy[i].first);
		vector<shared_ptr<ConceptChain>> backChains;
		Recursive_Search(Backward,pairs_copy[i].first,pairs_copy,relatedChain_Back,backChains);

		_recursiveCount=0;
		shared_ptr<ConceptChain> relatedChain_Forward(new ConceptChain());
		relatedChain_Forward->Push_Back(pairs_copy[i].second);
		vector<shared_ptr<ConceptChain>> forwardChains;
		Recursive_Search(Forward,pairs_copy[i].second,pairs_copy,relatedChain_Forward,forwardChains);

		//�ϲ�������������Ϸ�ʽ��
		vector<shared_ptr<ConceptChain>> curChains=Merge(backChains,forwardChains);
		res.insert(res.end(),curChains.begin(),curChains.end());
	}

	return res;
}

void ExtractConceptChains::Recursive_Search(const SearchDir dir,
	const shared_ptr<Mind::Concept> curConcept,
	const vector<ConceptPair>& pairs,
	const shared_ptr<Mind::ConceptChain>& relatedChain,//��¼�������ڽڵ�ǰ�İ��� curConcept��Chain���������ڵ�Concept�������ȥ��
	vector<shared_ptr<Mind::ConceptChain>>& chains )//����Chains
{
	// 	if(HasSearched(curConcept,dir,chains))//����Ѿ��ݹ�������curConcept����ôֱ�Ӵӱ�����ȡ��
	// 	{
	// 		return;
	// 	}
	_recursiveCount++;
	Check(_recursiveCount<=_recursiveMaxCount);

	if(relatedChain==NULL)
	{
		throw runtime_error("Error in Recursive_Search");
	}

	//������ڵ�Concept
	vector<shared_ptr<Concept>> adjConcepts;
	if (dir==Forward)
	{
		adjConcepts=GetForwardAdjConcepts(curConcept,pairs);
	}
	else
	{
		adjConcepts=GetBackwordAdjConcepts(curConcept,pairs);
	}

	if(adjConcepts.empty())//���û�����ڵ�Concept����ô�Ѻ�curConcept��ص�Chain���浽<chain>���ֹͣ�ݹ顣
	{
		chains.push_back(relatedChain);
		return;
	}

	vector<shared_ptr<Mind::ConceptChain>> curChains;//�洢�������ڽڵ�֮�����curConcept�����е�chain
	for (unsigned int i=0;i<adjConcepts.size();++i)
	{
		//��<relatedChains>���䣬��������forwardConcepts[i]��Chains��
		shared_ptr<ConceptChain> newRelatedChains=AppendToChains(adjConcepts[i],relatedChain,dir);
		if(relatedChain->Contain(adjConcepts[i]))//������Ǹ��ջ�����ô������ݹ���ȥ����������ջ��ᱻ����������
		{
			curChains.push_back(newRelatedChains);
		}
		else
			Recursive_Search(dir,adjConcepts[i],pairs,newRelatedChains,curChains);
	}

	//��¼curConcept����Ӧ��chains�������Ժ�ʹ�á�
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

vector<shared_ptr<Mind::Concept>> ExtractConceptChains::GetForwardAdjConcepts(const shared_ptr<Mind::Concept> concept, const vector<ConceptPair>& pairs )
{
	vector<shared_ptr<Mind::Concept>> res;
	for (unsigned int i=0;i<pairs.size();++i)
	{
		if(concept->Same(pairs[i].first))
		{
			res.push_back(pairs[i].second);
		}
	}

	return res;
}

vector<shared_ptr<Mind::Concept>> ExtractConceptChains::GetBackwordAdjConcepts( const shared_ptr<Mind::Concept> concept,const vector<ConceptPair>& pairs )
{
	vector<shared_ptr<Mind::Concept>> res;
	for (unsigned int i=0;i<pairs.size();++i)
	{
		if(concept->Same(pairs[i].second))
		{
			res.push_back(pairs[i].first);
		}
	}

	return res;
}

shared_ptr<Mind::ConceptChain> ExtractConceptChains::AppendToChains( const shared_ptr<Concept> concept,const shared_ptr<Mind::ConceptChain>& chains ,const SearchDir dir)
{
	shared_ptr<Mind::ConceptChain> res(new ConceptChain(chains->GetConceptVec()));
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

// bool ExtractConceptChains::HasSearched( const shared_ptr<Mind::Concept> concept,const SearchDir dir,vector<shared_ptr<Mind::ConceptChain>>& chains )
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

vector<shared_ptr<Mind::ConceptChain>> ExtractConceptChains::Merge( const vector<shared_ptr<Mind::ConceptChain>>& backChains,
	const vector<shared_ptr<Mind::ConceptChain>>& forwardChains )
{
	vector<shared_ptr<Mind::ConceptChain>> res;
	res.reserve(backChains.size()*forwardChains.size());
	for (unsigned int i=0;i<backChains.size();++i)
	{		
		for (unsigned int j=0;j<forwardChains.size();++j)
		{
			shared_ptr<ConceptChain> newChain=backChains[i]->Copy();
			//newChain->Reverse();
			newChain->Append(forwardChains[j]);
			res.push_back(newChain);
		}
	}

	return res;
}

void ExtractConceptChains::RemoveBadPairs( vector<ConceptPair>& pairs )
{
	//ȥ��������ͬConcept��pair
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

	//ȥ����ͬ��pair
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

// void ExtractConceptChains::ClearTable()
// {
// 	_backwardTable.clear();
// 	_forwardTable.clear();
// }

