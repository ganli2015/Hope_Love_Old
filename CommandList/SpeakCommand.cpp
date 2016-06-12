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

	shared_ptr<DataCollection::Sentence> parsedSentence=sentenceParser->GetParsedSentence();
	shared_ptr<Mind::iConceptInteractTable> interactTable=sentenceParser->GetInteractTable();
	_datawrapper->AddParsedInputSentence(parsedSentence);

	vector<shared_ptr<DataCollection::Sentence>> reactInputSentence;
	reactInputSentence.push_back(parsedSentence);
	shared_ptr<SpeakReaction> reaction(new SpeakReaction(reactInputSentence,interactTable));
	reaction->React();
	shared_ptr<DataCollection::Sentence> reactSentence=reaction->GetReactSentence();
	if(reactSentence==NULL)
	{
		return;
	}
	string reactStr=reactSentence->GetString();

	_datawrapper->AddOutputSentence(reactStr);
}
