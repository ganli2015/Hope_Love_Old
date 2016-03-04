#include "StdAfx.h"
#include "SpeakCommand.h"

#include "../ReactionAnalysisAlgorithm/ReactionParser.h"

SpeakReaction::SpeakReaction(void)
{
}


SpeakReaction::~SpeakReaction(void)
{
}

SpeakReaction::SpeakReaction(const vector<shared_ptr<DataCollection::Sentence>> sentence):_sentence(sentence)
{

}

void SpeakReaction::React()
{
	ReactionParser reactionParser(_sentence);
	reactionParser.Execute();
}
