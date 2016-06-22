#pragma once
#include "InOut.h"

namespace DataCollection
{
	class Sentence;
	class Word;
}

///A simple class which get a sentence to ask the meaning of the unknown words.
class AskAboutUnknownWords
{
	vector<shared_ptr<DataCollection::Word>> _unknownWords;

public:
	///Input unknown words.
	AskAboutUnknownWords(const vector<shared_ptr<DataCollection::Word>>& val);
	~AskAboutUnknownWords(void);

	shared_ptr<DataCollection::Sentence> GenerateReactSentence() const;
};

