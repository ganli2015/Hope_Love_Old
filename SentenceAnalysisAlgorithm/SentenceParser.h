#pragma once
#include "InOut.h"

namespace DataCollection
{
	class Sentence;
}

class _SENTENCEANALYSISALGORITHMINOUT SentenceParser
{
	std::string _sentence;
	vector<shared_ptr<DataCollection::Sentence>> _parsedSentence;
public:
	SentenceParser(void);
	~SentenceParser(void);
	SentenceParser(std::string sen);

	void Execute();
	vector<shared_ptr<DataCollection::Sentence>> GetParsedSentence() const {return _parsedSentence;}
};

