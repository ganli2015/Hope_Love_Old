#pragma once
#include "InOut.h"

namespace DataCollection
{
	class Sentence;
}

///Algorithm of punctuating a sentence.
class _SENTENCEANALYSISALGORITHMINOUT Punctuator
{
	shared_ptr<DataCollection::Sentence> _unpunctuated;
public:
	Punctuator(std::string longSen);
	~Punctuator(void);
	
	///Punctuate the input sentence and the result will store in <punctuated> as several sub sentences.
	///The input sentence will be separated according to end-of-sentence punctures. 
	bool Punctuate(shared_ptr<DataCollection::Sentence>& punctuated);

	//std::vector<shared_ptr<DataCollection::Sentence>> GetPunctuated() const {return _punctuated;}
};

