#include "StdAfx.h"
#include "SentenceParser.h"
#include "SentenceAnalyzer.h"
#include "WordRelationTableBuilder.h"

#include "../DataCollection/Word.h"

#include "../MindElement/Concept.h"
#include "../MindInterface/iConceptInteractTable.h"
#include "../MindInterface/iCerebrum.h"
#include "../MindInterface/iMindElementCreator.h"
#include "../MindElement/ConceptInteractTable.h"

#include "../CommonTools/LogWriter.h"

using namespace std;
using namespace DataCollection;
using namespace Mind;
SentenceParser::SentenceParser(void)
{
}

SentenceParser::SentenceParser(const std::string sen):_sentence(sen),_conceptTable(shared_ptr<iConceptInteractTable>(iMindElementCreator::CreateConceptInteractTable()))
{

}

SentenceParser::~SentenceParser(void)
{
}

void SentenceParser::Execute()
{
	LOG("SentenceParser: Begin");

	Mind::iCerebrum* brain=Mind::iCerebrum::Instance();
//	brain->ClearConceptInteractTable();

	shared_ptr<SentenceAnalyzer> sentenceAnalyzer(new SentenceAnalyzer(_sentence));
	sentenceAnalyzer->Analyze();
	//vector<shared_ptr<Word>> unknownWords=sentenceAnalyzer->GetUnknownWords();

	_parsedSentence=sentenceAnalyzer->GetAnalyzedSentences();

	WordRelationTableBuilder wordRelationTableBuilder(_parsedSentence);
	wordRelationTableBuilder.Build();
	shared_ptr<iConceptInteractTable> baseConceptTable=wordRelationTableBuilder.GetBaseInteractTable();
	shared_ptr<iConceptInteractTable> protoConceptTable=wordRelationTableBuilder.GetProtoInteractTable();
	_conceptTable->Absorb(baseConceptTable);
	LOG("WordRelationTableBuilder");

#ifdef _COUT_DEBUG_INFO //≤‚ ‘WordRelationTableBuilder
	Cout_WordRelations();
#endif
}

void SentenceParser::Cout_WordRelations()
{
	Mind::iCerebrum* brain=Mind::iCerebrum::Instance();
	vector<pair<shared_ptr<Mind::iConcept>,shared_ptr<Mind::iConcept>>> relations=_conceptTable->GetAllRelations();

	cout<<"Test Word Relations"<<endl;

	CommonFunction::OutputConceptPairs(relations,cout);

	cout<<endl;
	
}