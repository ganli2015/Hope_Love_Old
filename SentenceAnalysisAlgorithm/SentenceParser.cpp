#include "StdAfx.h"
#include "SentenceParser.h"
#include "SentenceAnalyzer.h"
#include "WordRelationTableBuilder.h"

#include "../DataCollection/Word.h"

#include "../MindElement/Concept.h"
#include "../MindElement/ConceptInteractTable.h"
#include "../Mind/Cerebrum.h"

using namespace std;
using namespace DataCollection;
using namespace Mind;
SentenceParser::SentenceParser(void)
{
}

SentenceParser::SentenceParser(const std::string sen):_sentence(sen),_conceptTable(shared_ptr<ConceptInteractTable>(new ConceptInteractTable()))
{

}

SentenceParser::~SentenceParser(void)
{
}

void SentenceParser::Execute()
{
	Mind::Cerebrum* brain=Mind::Cerebrum::Instance();
//	brain->ClearConceptInteractTable();

	shared_ptr<SentenceAnalyzer> sentenceAnalyzer(new SentenceAnalyzer(_sentence));
	sentenceAnalyzer->Analyze();
	//vector<shared_ptr<Word>> unknownWords=sentenceAnalyzer->GetUnknownWords();

	_parsedSentence=sentenceAnalyzer->GetAnalyzedSentences();

	WordRelationTableBuilder wordRelationTableBuilder(_parsedSentence);
	wordRelationTableBuilder.Build();
	_conceptTable->Absorb(wordRelationTableBuilder.GetInteractTable());

#ifdef _DEBUG //≤‚ ‘WordRelationTableBuilder
	Cout_WordRelations();
#endif
}

void SentenceParser::Cout_WordRelations()
{
	Mind::Cerebrum* brain=Mind::Cerebrum::Instance();
	vector<pair<shared_ptr<Mind::Concept>,shared_ptr<Mind::Concept>>> relations=_conceptTable->GetAllRelations();

	cout<<"Test Word Relations"<<endl;

	for (unsigned int i=0;i<relations.size();++i)
	{
		cout<<relations[i].first->GetString();
		cout<<" ";
		cout<<relations[i].second->GetString();
		cout<<endl;
	}

	cout<<endl;
}