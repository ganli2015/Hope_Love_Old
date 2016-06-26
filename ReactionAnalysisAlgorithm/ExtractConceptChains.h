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
	///Search direction in the concept table.
	///For a pair "A-B",  Forward means searching pairs connect to "B"
	///and Backward means searching pairs connect to "A".s
	enum SearchDir
	{
		Forward,
		Backward
	};

	static int _recursiveCount;
	const static int _recursiveMaxCount;
public:
	///Extract all sequential concept chains in <pairs>.
	///The chains are continuous and each of them is the longest one.
	static vector<shared_ptr<Mind::iConceptChain>> Extract(const vector<ConceptPair>& pairs);

private:
	///Search concept chains in <pairs>.
	///<curConcept> is the current search node which is recorded in <relatedChains> step by step.
	///Thus <relatedChains> means previous concept chains that contain <curConcept>.
	///<chain> are output concept chains.
	static void Recursive_Search(const SearchDir dir,
		const shared_ptr<Mind::iConcept> curConcept, 
		const vector<ConceptPair>& pairs, 
		const shared_ptr<Mind::iConceptChain>& relatedChains,
		vector<shared_ptr<Mind::iConceptChain>>& chain );

	///Get adjacent Forward or Backward concepts of <concept> according to the direction <dir>.
	static vector<shared_ptr<Mind::iConcept>> GetAdjacentConcepts(const SearchDir dir, const shared_ptr<Mind::iConcept> concept, const vector<ConceptPair>& pairs);

	///Find all pairs whose first concepts are the same with <concept>
	///and output second concepts of those pairs.
	static vector<shared_ptr<Mind::iConcept>> GetForwardAdjConcepts(const shared_ptr<Mind::iConcept> concept,const vector<ConceptPair>& pairs);
	
	///Find all pairs whose second concepts are the same with <concept>
	///and output first concepts of those pairs.	
	static vector<shared_ptr<Mind::iConcept>> GetBackwordAdjConcepts(const shared_ptr<Mind::iConcept> concept,const vector<ConceptPair>& pairs);

	///Append <concept> to <chains>.
	///If <dir> is Forward, push back to <chains> . Otherwise push front to <chains>.
	static shared_ptr<Mind::iConceptChain> AppendToChains( const shared_ptr<Mind::iConcept> concept,const shared_ptr<Mind::iConceptChain>& chains ,const SearchDir dir);

	///Merge <backChains> and <forwardChains>.
	///Tails of <backChains> connect to heads of <forwardChains>.	
	static vector<shared_ptr<Mind::iConceptChain>> Merge(const vector<shared_ptr<Mind::iConceptChain>>& backChains,
		const vector<shared_ptr<Mind::iConceptChain>>& forwardChains);
	
	///Remove pairs whose first and second concepts are the same.
	///Remove duplicated pairs .
	static void RemoveBadPairs(vector<ConceptPair>& pairs);

	///Remove pairs whose first and second concepts are the same.
	static void RemovePairsWithSameConcepts(vector<ConceptPair>& pairs);
	static void RemoveDuplicatedPairs(vector<ConceptPair>& pairs);

	///Check whether <chain> is closed.
	static bool IsClosedChain(const shared_ptr<Mind::iConceptChain> chain);

	//Remove closed chains from <inputChains> and return them.
	static vector<shared_ptr<Mind::iConceptChain>> CollectAndRemoveClosedChains(vector<shared_ptr<Mind::iConceptChain>>& inputChains);
};


