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
	//提取pairs里所有的Concept有序序列。对于每个节点，只考虑经过它的最长序列，而不考虑子序列。
	static vector<shared_ptr<Mind::ConceptChain>> Extract(const vector<ConceptPair>& pairs);

	//	static void ClearTable();
private:
	static void Recursive_Search(const SearchDir dir,
		const shared_ptr<Mind::Concept> curConcept, 
		const vector<ConceptPair>& pairs, 
		const shared_ptr<Mind::ConceptChain>& relatedChains,/*记录包含 curConcept的Chain，便于相邻的Concept能添加上去。 */
		vector<shared_ptr<Mind::ConceptChain>>& chain )/*所有Chains */;
	//在pairs中，找到所有第一个concept与输入的<concept>相同的对，返回所有对的第二个concept。
	static vector<shared_ptr<Mind::Concept>> GetForwardAdjConcepts(const shared_ptr<Mind::Concept> concept,const vector<ConceptPair>& pairs);
	//在pairs中，找到所有第二个concept与输入的<concept>相同的对，返回所有对的第一个concept。
	static vector<shared_ptr<Mind::Concept>> GetBackwordAdjConcepts(const shared_ptr<Mind::Concept> concept,const vector<ConceptPair>& pairs);
	static shared_ptr<Mind::ConceptChain> AppendToChains( const shared_ptr<Mind::Concept> concept,const shared_ptr<Mind::ConceptChain>& chains ,const SearchDir dir);
	static bool HasSearched(const shared_ptr<Mind::Concept> concept,const SearchDir dir,vector<shared_ptr<Mind::ConceptChain>>& chains);
	static vector<shared_ptr<Mind::ConceptChain>> Merge(const vector<shared_ptr<Mind::ConceptChain>>& backChains,
		const vector<shared_ptr<Mind::ConceptChain>>& forwardChains);
};


