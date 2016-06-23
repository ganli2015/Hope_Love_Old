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

	///Generate concept chains for reaction according to the interaction table <interactTable>.
	///Use <GetReactChains> after <Generate>.
	///These concept chains are experimental to AI and are derived from the experience of previous conversations or their innate mind.
	void Generate(const shared_ptr<Mind::iConceptInteractTable> interactTable) ;
	vector<Mind::ConceptChainProperty> GetReactChains() const {return _reactChains;};

private:
	///Compute react chains from input <chains>.
	vector<Mind::ConceptChainProperty> ChainReact(const vector<shared_ptr<Mind::iConceptChain>>& chains) const;
	///Select concept chains according to confidence of <chainProperties>.
	///Some of <chainProperties> will be rejected if they have low confidence.
	vector<shared_ptr<Mind::iConceptChain>> RandomSelectChains(const vector<Mind::ConceptChainProperty>& chainProperties) const;

	void DisplayChains(const vector<shared_ptr<Mind::iConceptChain>>& chains) const;
	///Check whether their is duplicated concept chain in <chains>.
	void CheckDuplicatedConceptInChains(const vector<shared_ptr<Mind::iConceptChain>>& chains) const;
	void OutputChainProperty(const shared_ptr<Mind::iConceptChain> chain,const vector<Mind::ConceptChainProperty>& properties,ofstream& out) const;
};

