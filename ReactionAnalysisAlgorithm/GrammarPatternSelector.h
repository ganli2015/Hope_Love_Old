#pragma once
#include "InOut.h"


namespace DataCollection
{
	class Sentence;
	class GrammarPattern;
}

class GrammarPatternSelector
{
public:
	GrammarPatternSelector(void);
	~GrammarPatternSelector(void);

	DataCollection::GrammarPattern SelectReactPattern(const shared_ptr<DataCollection::Sentence> sen);

private:
	vector<DataCollection::GrammarPattern> GetParentPatterns(const vector<DataCollection::GrammarPattern>& patterns);
	vector<double> GetPatternFrequency(const vector<DataCollection::GrammarPattern>& patterns);
};

