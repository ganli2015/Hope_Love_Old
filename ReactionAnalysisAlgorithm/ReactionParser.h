#pragma once
#include "InOut.h"

namespace DataCollection
{
	class Sentence;
}

namespace Mind
{
	class ConceptChain;
	struct ConceptChainProperty;
}

class _REACTIONANALYSISALGORITHMINOUT ReactionParser
{
	vector<shared_ptr<DataCollection::Sentence>> _sentence;

public:
	ReactionParser(void);
	~ReactionParser(void);
	ReactionParser(const vector<shared_ptr<DataCollection::Sentence>> sentence);

	void Execute();
private:
	void DisplayChain( const shared_ptr<Mind::ConceptChain>& chain ) const;
	void DisplayReactChains( const vector<Mind::ConceptChainProperty>& chains ) const;
	void DisplayHyperChains( const vector<shared_ptr<Mind::ConceptChain>>& chains ) const;
};

