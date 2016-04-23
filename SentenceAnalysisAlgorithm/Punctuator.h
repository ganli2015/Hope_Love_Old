#pragma once
#include "InOut.h"

namespace DataCollection
{
	class Sentence;
}

class _SENTENCEANALYSISALGORITHMINOUT Punctuator
{
	shared_ptr<DataCollection::Sentence> _unpunctuated;
public:
	Punctuator(std::string longSen);
	~Punctuator(void);
	
	bool Punctuate(shared_ptr<DataCollection::Sentence>& punctuated);

	//std::vector<shared_ptr<DataCollection::Sentence>> GetPunctuated() const {return _punctuated;}
};

