#pragma once
#include "InOut.h"

namespace DataCollection
{
	class Sentence;
}

class _SENTENCEANALYSISALGORITHMINOUT Punctuator
{
	shared_ptr<DataCollection::Sentence> _unpunctuated;
    std::vector<shared_ptr<DataCollection::Sentence>> _punctuated;
public:
	Punctuator(std::string longSen);
	~Punctuator(void);
	
	bool Punctuate(std::vector<shared_ptr<DataCollection::Sentence>>& punctuated);

	//std::vector<shared_ptr<DataCollection::Sentence>> GetPunctuated() const {return _punctuated;}
};

