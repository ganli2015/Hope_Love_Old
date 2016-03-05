#include "StdAfx.h"
#include "SpeakCommand.h"

#include "../ReactionAnalysisAlgorithm/ReactionParser.h"

#include "../DataCollection/Sentence.h"

SpeakReaction::SpeakReaction(void)
{
}


SpeakReaction::~SpeakReaction(void)
{
}

SpeakReaction::SpeakReaction(const vector<shared_ptr<DataCollection::Sentence>> sentence):_sentence_input(sentence)
{

}

void SpeakReaction::React()
{
	ReactionParser reactionParser(_sentence_input);
	reactionParser.Execute();
	_sentence_output.push_back(reactionParser.GetReactSentence());
}

shared_ptr<DataCollection::Sentence> SpeakReaction::GetReactSentence() const
{
	if(_sentence_output.empty())
	{
		return NULL;
	}

	return _sentence_output.back();
}
