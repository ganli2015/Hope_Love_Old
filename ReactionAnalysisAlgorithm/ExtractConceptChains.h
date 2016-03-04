#pragma once
#include "InOut.h"

namespace Mind
{
	class Concept;
	class ConceptChain;
	struct ConceptChainProperty;
}

class ExtractConceptChains
{
	typedef pair<shared_ptr<Mind::Concept>,shared_ptr<Mind::Concept>> ConceptPair;
	enum SearchDir
	{
		Forward,
		Backward
	};

	// 	static map<shared_ptr<Mind::Concept>,vector<shared_ptr<Mind::ConceptChain>>> _forwardTable;
	// 	static map<shared_ptr<Mind::Concept>,vector<shared_ptr<Mind::ConceptChain>>> _backwardTable;
public:
	//��ȡpairs�����е�Concept�������С�����ÿ���ڵ㣬ֻ���Ǿ�����������У��������������С�
	static vector<shared_ptr<Mind::ConceptChain>> Extract(const vector<ConceptPair>& pairs);

	//	static void ClearTable();
private:
	static void Recursive_Search(const SearchDir dir,
		const shared_ptr<Mind::Concept> curConcept, 
		const vector<ConceptPair>& pairs, 
		const shared_ptr<Mind::ConceptChain>& relatedChains,/*��¼���� curConcept��Chain���������ڵ�Concept�������ȥ�� */
		vector<shared_ptr<Mind::ConceptChain>>& chain )/*����Chains */;
	//��pairs�У��ҵ����е�һ��concept�������<concept>��ͬ�Ķԣ��������жԵĵڶ���concept��
	static vector<shared_ptr<Mind::Concept>> GetForwardAdjConcepts(const shared_ptr<Mind::Concept> concept,const vector<ConceptPair>& pairs);
	//��pairs�У��ҵ����еڶ���concept�������<concept>��ͬ�Ķԣ��������жԵĵ�һ��concept��
	static vector<shared_ptr<Mind::Concept>> GetBackwordAdjConcepts(const shared_ptr<Mind::Concept> concept,const vector<ConceptPair>& pairs);
	static shared_ptr<Mind::ConceptChain> AppendToChains( const shared_ptr<Mind::Concept> concept,const shared_ptr<Mind::ConceptChain>& chains ,const SearchDir dir);
	static bool HasSearched(const shared_ptr<Mind::Concept> concept,const SearchDir dir,vector<shared_ptr<Mind::ConceptChain>>& chains);
	static vector<shared_ptr<Mind::ConceptChain>> Merge(const vector<shared_ptr<Mind::ConceptChain>>& backChains,
		const vector<shared_ptr<Mind::ConceptChain>>& forwardChains);
};


