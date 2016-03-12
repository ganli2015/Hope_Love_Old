#include "StdAfx.h"
#include "SpeakCommand.h"

#include "../DataCollection/Sentence.h"

#include "../DataWrapperCPP/DataWrapper.h"

#include "../ReactionList/SpeakCommand.h"

#include "../SentenceAnalysisAlgorithm/SentenceParser.h"

using namespace std;
SpeakCommand::SpeakCommand(void)
{
}


SpeakCommand::~SpeakCommand(void)
{
}

SpeakCommand::SpeakCommand(DataWrapperCPP::DataWrapper_Sentence* datawrapper)
{
	_datawrapper=datawrapper;
}

void SpeakCommand::Update()
{
	string sentence=_datawrapper->GetInputSentence();
	if(sentence=="") return;

	shared_ptr<SentenceParser> sentenceParser(new SentenceParser(sentence));
	sentenceParser->Execute();

	vector<shared_ptr<DataCollection::Sentence>> parsedSentence=sentenceParser->GetParsedSentence();
	_datawrapper->AddParsedInputSentence(parsedSentence);

	shared_ptr<SpeakReaction> reaction(new SpeakReaction());
	reaction->React();
	string reactStr=reaction->GetReactSentence()->GetString();

	_datawrapper->AddOutputSentence(reactStr);
}
