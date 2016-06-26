#include "StdAfx.h"
#include "ReactionParser.h"
#include "GrammarPatternSelector.h"
#include "ChainGenerator.h"
#include "ChainAnalyzer.h"
#include "SentenceGenerator.h"
#include "AskAboutUnknownWords.h"
#include "LogicReactor.h"
#include "SentenceTypeDetermination.h"

#include "../DataCollection/GrammaPattern.h"
#include "../DataCollection/Sentence.h"

#include "../MindElement/Concept.h"
#include "../MindInterface/iConceptChain.h"
#include "../MindInterface/iCerebrum.h"

#include "../CommonTools/LogWriter.h"


#include <iostream>

using namespace DataCollection;
using namespace Mind;

ReactionParser::ReactionParser(void)
{
}


ReactionParser::~ReactionParser(void)
{
}

ReactionParser::ReactionParser(const vector<shared_ptr<DataCollection::Sentence>> sentence,const shared_ptr<Mind::iConceptInteractTable> interactTable):_sentence_input(sentence),_interactTable(interactTable)
{

}

void ReactionParser::Execute()
{
	LOG("ReactionParser: Begin");

	//Check how many unknown words there are.
	//Once there is one unknown, AI will ask about it.
	//AI cannot deduce the meaning of it and cannot cope with the sentence with unknown words.
	vector<shared_ptr<DataCollection::Word>> unknownWords=CountUnknownWords(_sentence_input);
	if(!unknownWords.empty())
	{
		AskAboutUnknownWords askAboutUnknownWords(unknownWords);
		_sentence_output.push_back(askAboutUnknownWords.GenerateReactSentence());
		LOG("AskAboutUnknownWords");
		return;
	}
	
	//Deduce the type of sentence.
	//Only if AI knows the type of sentence, she can answer or ask or behave accordingly.
	SentenceTypeDetermination typeDetermine;
	SentenceTypeDetermination::Type type=typeDetermine.Determine(_sentence_input.front());//Cope with the first sentence!
	LOG("SentenceTypeDetermination");
	if (type == SentenceTypeDetermination::Interrogative)
	{
		shared_ptr<Sentence> questionPart = typeDetermine.GetQuestionPart();
		assert(questionPart != NULL);
		_sentence_output = GenerateByLogicAnalysis(questionPart);
		LOG("GenerateByLogicAnalysis");

		//If AI don't know the result, then she said "不知道".
		//The sentence does not need to be analyzed by <GenerateByConceptChainAnalysis>
		//as it is an interrogative sentence.If you don't know you say I don't know.
		if (_sentence_output.empty())
		{
			_sentence_output.push_back(shared_ptr<Sentence>(new Sentence("不知道")));
		}
	}

	//If there is null result of Logic Analysis or the sentence is declarative, 
	//then generate the result sentence by concept chain Analysis.
	if(_sentence_output.empty())
	{
		_sentence_output=GenerateByConceptChainAnalysis();		
		LOG("GenerateByConceptChainAnalysis");
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

void ReactionParser::DisplayChain( const shared_ptr<Mind::iConceptChain>& chain ) const
{
	vector<shared_ptr<iConcept> > concepts=chain->GetConceptVec();
	for (unsigned int j=0;j<concepts.size();++j)
	{
		cout<<concepts[j]->GetString()<<" ";
	}
	cout<<endl;
}

void ReactionParser::DisplayHyperChains( const vector<shared_ptr<Mind::iConceptChain>>& chains ) const
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
	Mind::iCerebrum* brain=Mind::iCerebrum::Instance();

	vector<shared_ptr<DataCollection::Word>> res;

	for (unsigned int i=0;i<sentences.size();++i)
	{
		vector<shared_ptr<Word>> words=sentences[i]->GetGrammard();
		for (unsigned int j=0;j<words.size();++j)
		{
			if(words[j]->Type()==Punctuation)
			{
				continue;
			}

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
	LOG("GenerateByConceptChainAnalysis: Begin");

	vector<shared_ptr<DataCollection::Sentence>> res;

	ChainGenerator chainGenerator;
	chainGenerator.Generate(_interactTable);
	vector<Mind::ConceptChainProperty> reactChains=chainGenerator.GetReactChains();
	LOG("ChainGenerator");

#ifdef _COUT_DEBUG_INFO
	DisplayReactChains(reactChains);
#endif // _DEBUG

	ChainAnalyzer chainAnalyzer;
	chainAnalyzer.Analyze(reactChains);
	vector<shared_ptr<Mind::iConceptChain>> hyperChains=chainAnalyzer.GetHyperChains();
	LOG("ChainAnalyzer");

#ifdef _COUT_DEBUG_INFO
	DisplayHyperChains(hyperChains);
#endif // _DEBUG

	SentenceGenerator sentenceGenerator;
	sentenceGenerator.Generate(hyperChains);
	res.push_back(sentenceGenerator.GetSentence());
	LOG("SentenceGenerator");

	return res;
}

vector<shared_ptr<DataCollection::Sentence>> ReactionParser::GenerateByLogicAnalysis(const shared_ptr<DataCollection::Sentence> input) const
{
	LOG("GenerateByLogicAnalysis: Begin");

	vector<shared_ptr<DataCollection::Sentence>> res;

	LogicReactor logicReactor;
	shared_ptr<Sentence> outSentence = logicReactor.Analyze(input);
	if(outSentence==NULL)
	{
		return res;
	}
	else
	{
		res.push_back(outSentence);
		return res;
	}
}

