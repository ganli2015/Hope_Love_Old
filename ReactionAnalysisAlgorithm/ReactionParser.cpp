#include "StdAfx.h"
#include "ReactionParser.h"
#include "GrammarPatternSelector.h"
#include "ChainGenerator.h"
#include "ChainAnalyzer.h"
#include "SentenceGenerator.h"
#include "AskAboutUnknownWords.h"

#include "../DataCollection/GrammaPattern.h"
#include "../DataCollection/Sentence.h"

#include "../MindElement/Concept.h"
#include "../MindElement/ConceptChain.h"
#include "../Mind/Cerebrum.h"

#include <iostream>

using namespace DataCollection;
using namespace Mind;

ReactionParser::ReactionParser(void)
{
}


ReactionParser::~ReactionParser(void)
{
}

ReactionParser::ReactionParser(const vector<shared_ptr<DataCollection::Sentence>> sentence,const shared_ptr<Mind::ConceptInteractTable> interactTable):_sentence_input(sentence),_interactTable(interactTable)
{

}

void ReactionParser::Execute()
{
// 	GrammarPatternSelector grammarPatternSelector;
// 	GrammarPattern selectedPattern=grammarPatternSelector.SelectReactPattern(_sentence[0]);

	vector<shared_ptr<DataCollection::Word>> unknownWords=CountUnknownWords(_sentence_input);
	if(unknownWords.empty())
	{
		_sentence_output=GenerateByConceptChainAnalysis();
	}
	else
	{
		AskAboutUnknownWords askAboutUnknownWords(unknownWords);
		_sentence_output.push_back(askAboutUnknownWords.GenerateReactSentence());
	}
}

void ReactionParser::DisplayReactChains( const vector<ConceptChainProperty>& chains ) const
{
	cout<<"React Chains:"<<endl;
	for (unsigned int i=0;i<chains.size();++i)
	{
		DisplayChain(chains[i].chain);
	}

	cout<<endl;
}

void ReactionParser::DisplayChain( const shared_ptr<Mind::ConceptChain>& chain ) const
{
	vector<shared_ptr<Concept> > concepts=chain->GetConceptVec();
	for (unsigned int j=0;j<concepts.size();++j)
	{
		cout<<concepts[j]->GetString()<<" ";
	}
	cout<<endl;
}

void ReactionParser::DisplayHyperChains( const vector<shared_ptr<Mind::ConceptChain>>& chains ) const
{
	cout<<"Hyper Chains:"<<endl;
	for (unsigned int i=0;i<chains.size();++i)
	{
		DisplayChain(chains[i]);
	}

	cout<<endl;
}

shared_ptr<DataCollection::Sentence> ReactionParser::GetReactSentence() const
{
	if(_sentence_output.empty())
	{
		return NULL;
	}

	return _sentence_output.back();
}

vector<shared_ptr<DataCollection::Word>> ReactionParser::CountUnknownWords( const vector<shared_ptr<DataCollection::Sentence>>& sentences ) const
{
	Mind::Cerebrum* brain=Mind::Cerebrum::Instance();

	vector<shared_ptr<DataCollection::Word>> res;

	for (unsigned int i=0;i<sentences.size();++i)
	{
		vector<shared_ptr<Word>> words=sentences[i]->GetGrammard(0);
		for (unsigned int j=0;j<words.size();++j)
		{
			if(!brain->IsInMind(words[j]))
			{
				res.push_back(words[j]);
			}
		}
	}

	return res;
}

vector<shared_ptr<DataCollection::Sentence>> ReactionParser::GenerateByConceptChainAnalysis() const
{
	vector<shared_ptr<DataCollection::Sentence>> res;

	ChainGenerator chainGenerator;
	chainGenerator.Generate(_interactTable);
	vector<Mind::ConceptChainProperty> reactChains=chainGenerator.GetReactChains();

#ifdef _DEBUG
	DisplayReactChains(reactChains);
#endif // _DEBUG

	ChainAnalyzer chainAnalyzer;
	chainAnalyzer.Analyze(reactChains);
	vector<shared_ptr<Mind::ConceptChain>> hyperChains=chainAnalyzer.GetHyperChains();

#ifdef _DEBUG
	DisplayHyperChains(hyperChains);
#endif // _DEBUG

	SentenceGenerator sentenceGenerator;
	sentenceGenerator.Generate(hyperChains);
	res.push_back(sentenceGenerator.GetSentence());

	return res;
}
