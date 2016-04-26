#pragma once
#include "InOut.h"

namespace Mind
{
	class iConcept;
	class ConceptChain;
	struct ConceptChainProperty;
}

class ExtractConceptChains
{
	typedef pair<shared_ptr<Mind::iConcept>,shared_ptr<Mind::iConcept>> ConceptPair;
	enum SearchDir
	{
		Forward,
		Backward
	};

	static int _recursiveCount;
	const static int _recursiveMaxCount;
	// 	static map<shared_ptr<Mind::iConcept>,vector<shared_ptr<Mind::ConceptChain>>> _forwardTable;
	// 	static map<shared_ptr<Mind::iConcept>,vector<shared_ptr<Mind::ConceptChain>>> _backwardTable;
public:
	//��ȡpairs�����е�iConcept�������С�����ÿ���ڵ㣬ֻ���Ǿ�����������У��������������С�
	static vector<shared_ptr<Mind::ConceptChain>> Extract(const vector<ConceptPair>& pairs);

	//	static void ClearTable();
private:
	static void Recursive_Search(const SearchDir dir,
		const shared_ptr<Mind::iConcept> curConcept, 
		const vector<ConceptPair>& pairs, 
		const shared_ptr<Mind::ConceptChain>& relatedChains,/*��¼���� curConcept��Chain���������ڵ�iConcept�������ȥ�� */
		vector<shared_ptr<Mind::ConceptChain>>& chain )/*����Chains */;
	//��pairs�У��ҵ����е�һ��concept�������<concept>��ͬ�Ķԣ��������жԵĵڶ���concept��
	static vector<shared_ptr<Mind::iConcept>> GetForwardAdjConcepts(const shared_ptr<Mind::iConcept> concept,const vector<ConceptPair>& pairs);
	//��pairs�У��ҵ����еڶ���concept�������<concept>��ͬ�Ķԣ��������жԵĵ�һ��concept��
	static vector<shared_ptr<Mind::iConcept>> GetBackwordAdjConcepts(const shared_ptr<Mind::iConcept> concept,const vector<ConceptPair>& pairs);
	static shared_ptr<Mind::ConceptChain> AppendToChains( const shared_ptr<Mind::iConcept> concept,const shared_ptr<Mind::ConceptChain>& chains ,const SearchDir dir);
	static bool HasSearched(const shared_ptr<Mind::iConcept> concept,const SearchDir dir,vector<shared_ptr<Mind::ConceptChain>>& chains);
	static vector<shared_ptr<Mind::ConceptChain>> Merge(const vector<shared_ptr<Mind::ConceptChain>>& backChains,
		const vector<shared_ptr<Mind::ConceptChain>>& forwardChains);
	static void RemoveBadPairs(vector<ConceptPair>& pairs);
};


