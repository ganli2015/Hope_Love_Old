#pragma once
#include "InOut.h"

namespace Mind
{
	class Concept;
	class ConceptChain;
	class Cerebrum;
	struct ConceptChainProperty;
	class ConceptInteractTable;
}

class ChainGenerator
{
	typedef pair<shared_ptr<Mind::Concept>,shared_ptr<Mind::Concept>> ConceptPair;

	Mind::Cerebrum* _brain;

	vector<Mind::ConceptChainProperty> _reactChains;
public:
	ChainGenerator(void);
	~ChainGenerator(void);

	void Generate(const shared_ptr<Mind::ConceptInteractTable> interactTable) ;
	vector<Mind::ConceptChainProperty> GetReactChains() const {return _reactChains;};

private:
	void RemoveSameChain(vector<shared_ptr<Mind::ConceptChain>>& chains) const;
	vector<Mind::ConceptChainProperty> ChainReact(const vector<shared_ptr<Mind::ConceptChain>>& chains) const;
	vector<shared_ptr<Mind::ConceptChain>> RandomSelectChains(const vector<Mind::ConceptChainProperty>& chainProperties) const;

	void DisplayChains(const vector<shared_ptr<Mind::ConceptChain>>& chains) const;
	//检查是否每个ConceptChain里的Concept是否有重复。
	void CheckDuplicatedConceptInChains(const vector<shared_ptr<Mind::ConceptChain>>& chains) const;
	void OutputChainProperty(const shared_ptr<Mind::ConceptChain> chain,const vector<Mind::ConceptChainProperty>& properties,ofstream& out) const;
};

