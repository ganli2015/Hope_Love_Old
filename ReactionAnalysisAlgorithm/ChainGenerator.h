#pragma once
#include "InOut.h"

namespace Mind
{
	class iConcept;
	class iConceptChain;
	class iCerebrum;
	struct ConceptChainProperty;
	class iConceptInteractTable;
}

class ChainGenerator
{
	typedef pair<shared_ptr<Mind::iConcept>,shared_ptr<Mind::iConcept>> ConceptPair;

	Mind::iCerebrum* _brain;

	vector<Mind::ConceptChainProperty> _reactChains;
public:
	ChainGenerator(void);
	~ChainGenerator(void);

	void Generate(const shared_ptr<Mind::iConceptInteractTable> interactTable) ;
	vector<Mind::ConceptChainProperty> GetReactChains() const {return _reactChains;};

private:
	void RemoveSameChain(vector<shared_ptr<Mind::iConceptChain>>& chains) const;
	vector<Mind::ConceptChainProperty> ChainReact(const vector<shared_ptr<Mind::iConceptChain>>& chains) const;
	vector<shared_ptr<Mind::iConceptChain>> RandomSelectChains(const vector<Mind::ConceptChainProperty>& chainProperties) const;

	void DisplayChains(const vector<shared_ptr<Mind::iConceptChain>>& chains) const;
	//检查是否每个iConceptChain里的Concept是否有重复。
	void CheckDuplicatedConceptInChains(const vector<shared_ptr<Mind::iConceptChain>>& chains) const;
	void OutputChainProperty(const shared_ptr<Mind::iConceptChain> chain,const vector<Mind::ConceptChainProperty>& properties,ofstream& out) const;
};

