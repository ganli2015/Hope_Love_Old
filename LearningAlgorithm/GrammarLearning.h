#pragma once
#include "InOut.h"

namespace DataCollection
{
	class Sentence;
}

class GrammarLearning
{
public:
	GrammarLearning(void);
	~GrammarLearning(void);

	static void AdjustGrammarPatternFrequency(const shared_ptr<DataCollection::Sentence> sentence);

private:
};

