#include "StdAfx.h"
#include "AskAboutUnknownWords.h"

#include "../DataCollection/Word.h"
#include "../DataCollection/Sentence.h"

using namespace DataCollection;

AskAboutUnknownWords::AskAboutUnknownWords(const vector<shared_ptr<DataCollection::Word>>& val):_unknownWords(val)
{
}


AskAboutUnknownWords::~AskAboutUnknownWords(void)
{
}

shared_ptr<DataCollection::Sentence> AskAboutUnknownWords::GenerateReactSentence() const
{
	if(_unknownWords.empty()) return NULL;

	string firstUnknown=_unknownWords.front()->GetString();
	string other="是什么意思？";

	shared_ptr<DataCollection::Sentence> res(new Sentence(firstUnknown+other));

	return res;
}
