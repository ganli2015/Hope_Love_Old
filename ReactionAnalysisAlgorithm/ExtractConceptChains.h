#pragma once
#include "InOut.h"

namespace Mind
{
	class iConcept;
	class iConceptChain;
	struct ConceptChainProperty;
}

class _REACTIONANALYSISALGORITHMINOUT ExtractConceptChains
{
	typedef pair<shared_ptr<Mind::iConcept>,shared_ptr<Mind::iConcept>> ConceptPair;
	enum SearchDir
	{
		Forward,
		Backward
	};

	static int _recursiveCount;
	const static int _recursiveMaxCount;
	// 	static map<shared_ptr<Mind::iConcept>,vector<shared_ptr<Mind::iConceptChain>>> _forwardTable;
	// 	static map<shared_ptr<Mind::iConcept>,vector<shared_ptr<Mind::iConceptChain>>> _backwardTable;
public:
	//提取pairs里所有的iConcept有序序列。对于每个节点，只考虑经过它的最长序列，而不考虑子序列。
	static vector<shared_ptr<Mind::iConceptChain>> Extract(const vector<ConceptPair>& pairs);

	//	static void ClearTable();
private:
	static void Recursive_Search(const SearchDir dir,
		const shared_ptr<Mind::iConcept> curConcept, 
		const vector<ConceptPair>& pairs, 
		const shared_ptr<Mind::iConceptChain>& relatedChains,/*记录包含 curConcept的Chain，便于相邻的iConcept能添加上去。 */
		vector<shared_ptr<Mind::iConceptChain>>& chain )/*所有Chains */;
	//在pairs中，找到所有第一个concept与输入的<concept>相同的对，返回所有对的第二个concept。
	static vector<shared_ptr<Mind::iConcept>> GetForwardAdjConcepts(const shared_ptr<Mind::iConcept> concept,const vector<ConceptPair>& pairs);
	//在pairs中，找到所有第二个concept与输入的<concept>相同的对，返回所有对的第一个concept。
	static vector<shared_ptr<Mind::iConcept>> GetBackwordAdjConcepts(const shared_ptr<Mind::iConcept> concept,const vector<ConceptPair>& pairs);
	static shared_ptr<Mind::iConceptChain> AppendToChains( const shared_ptr<Mind::iConcept> concept,const shared_ptr<Mind::iConceptChain>& chains ,const SearchDir dir);
	static bool HasSearched(const shared_ptr<Mind::iConcept> concept,const SearchDir dir,vector<shared_ptr<Mind::iConceptChain>>& chains);
	static vector<shared_ptr<Mind::iConceptChain>> Merge(const vector<shared_ptr<Mind::iConceptChain>>& backChains,
		const vector<shared_ptr<Mind::iConceptChain>>& forwardChains);
	static void RemoveBadPairs(vector<ConceptPair>& pairs);
};


