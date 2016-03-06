#include "StdAfx.h"
#include "SentenceParser.h"
#include "SentenceAnalyzer.h"

#include "../DataCollection/Word.h"

#include "../Mind/Cerebrum.h"

using namespace std;
using namespace DataCollection;
SentenceParser::SentenceParser(void)
{
}

SentenceParser::SentenceParser(const std::string sen):_sentence(sen)
{

}

SentenceParser::~SentenceParser(void)
{
}

void SentenceParser::Execute()
{
	Mind::Cerebrum* brain=Mind::Cerebrum::Instance();
	brain->ClearConceptInteractTable();

	shared_ptr<SentenceAnalyzer> sentenceAnalyzer(new SentenceAnalyzer(_sentence));
	sentenceAnalyzer->Analyze();
	//vector<shared_ptr<Word>> unknownWords=sentenceAnalyzer->GetUnknownWords();

	_parsedSentence=sentenceAnalyzer->GetAnalyzedSentences();
}
