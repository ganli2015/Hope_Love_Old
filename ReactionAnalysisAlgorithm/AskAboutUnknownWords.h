#pragma once
#include "InOut.h"

namespace DataCollection
{
	class Sentence;
	class Word;
}

class AskAboutUnknownWords
{
	vector<shared_ptr<DataCollection::Word>> _unknownWords;

public:
	AskAboutUnknownWords(const vector<shared_ptr<DataCollection::Word>>& val);
	~AskAboutUnknownWords(void);

	shared_ptr<DataCollection::Sentence> GenerateReactSentence() const;
};

