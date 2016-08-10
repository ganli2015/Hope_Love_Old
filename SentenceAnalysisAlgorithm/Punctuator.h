#pragma once
#include "InOut.h"

namespace DataCollection
{
	class Sentence;
	class Character;
}

///Algorithm of punctuating a sentence.
class _SENTENCEANALYSISALGORITHMINOUT Punctuator
{
	shared_ptr<DataCollection::Sentence> _unpunctuated;
public:
	Punctuator(std::string longSen);
	~Punctuator(void);
	
	///Punctuate the input sentence and the result will store in <punctuated> as several sub sentences.
	///The input sentence will be separated according to end-of-sentence punctuations. 
	bool Punctuate(shared_ptr<DataCollection::Sentence>& punctuated);


private:
	///Compute sub sentence from <unpun>.
	///<sen_it> denotes the start of the sub sentence and <chara_it> the end of the sub sentence.
	///After getting sub sentence, <sen_it> and <chara_it> will refresh.
	vector<shared_ptr<DataCollection::Character>> ComputeSubSentence(const vector<shared_ptr<DataCollection::Character>>& unpun, vector<shared_ptr<DataCollection::Character>>::iterator& sen_it, 
		vector<shared_ptr<DataCollection::Character>>::iterator& chara_it);
};

