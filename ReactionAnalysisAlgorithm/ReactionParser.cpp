#include "StdAfx.h"
#include "ReactionParser.h"
#include "GrammarPatternSelector.h"
#include "ChainGenerator.h"
#include "ChainAnalyzer.h"

#include "../DataCollection/GrammaPattern.h"

#include "../Mind/Concept.h"
#include "../Mind/ConceptChain.h"

#include <iostream>

using namespace DataCollection;
using namespace Mind;

ReactionParser::ReactionParser(void)
{
}


ReactionParser::~ReactionParser(void)
{
}

ReactionParser::ReactionParser(const vector<shared_ptr<DataCollection::Sentence>> sentence):_sentence(sentence)
{

}

void ReactionParser::Execute()
{
// 	GrammarPatternSelector grammarPatternSelector;
// 	GrammarPattern selectedPattern=grammarPatternSelector.SelectReactPattern(_sentence[0]);

	ChainGenerator chainGenerator;
	chainGenerator.Generate();
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
