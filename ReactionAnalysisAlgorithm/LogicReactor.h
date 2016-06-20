#pragma once
#include "InOut.h"


namespace LogicSystem
{
	class iExpression;
}

namespace DataCollection
{
	class Sentence;
	class Word;
}

namespace Mind
{
	class iConceptChain;
}

///It is designed for temporary.
///Check sentence to analyze its logic component and make some reaction.
class _REACTIONANALYSISALGORITHMINOUT LogicReactor
{
public:
	LogicReactor(void);
	~LogicReactor(void);

	shared_ptr<DataCollection::Sentence> Analyze(const shared_ptr<DataCollection::Sentence> sen) const;

private:
	///Convert sentence to the concept chain and get all sub chains.
	vector<shared_ptr<Mind::iConceptChain>> ConvertToSubChains(const shared_ptr<DataCollection::Sentence> sen) const;

};

