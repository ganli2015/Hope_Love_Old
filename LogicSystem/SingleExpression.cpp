#include "StdAfx.h"
#include "SingleExpression.h"

#include "../SentenceAnalysisAlgorithm/SentenceAnalyzer.h"
#include "../SentenceAnalysisAlgorithm/WordRelationTableBuilder.h"

#include "../DataCollection/Sentence.h"

#include "../MindInterface/iConceptInteractTable.h"
#include "../MindInterface/iCerebrum.h"
#include "../MindInterface/iConcept.h"

using namespace DataCollection;
using namespace Mind;

namespace LogicSystem
{
	SingleExpression::SingleExpression(void)
	{
	}


	SingleExpression::SingleExpression( const string val )
	{
		SentenceAnalyzer sentenceAnalyzer(val);
		sentenceAnalyzer.Analyze();
		_sen=sentenceAnalyzer.GetAnalyzedSentences();
	}

	SingleExpression::SingleExpression(const shared_ptr<DataCollection::Sentence> val)
	{
		if(!val->StructureAnalyzed())
		{
			SentenceAnalyzer sentenceAnalyzer(val->GetString());
			sentenceAnalyzer.Analyze();
			_sen=sentenceAnalyzer.GetAnalyzedSentences();
		}
		else
		{
			_sen=val;
		}
	}

	SingleExpression::~SingleExpression(void)
	{
	}

	shared_ptr<Mind::iConceptInteractTable> SingleExpression::GetBaseInteractTable() const
	{
		if(_sen==NULL) return NULL;
		if(!_sen->StructureAnalyzed()) return NULL;

		WordRelationTableBuilder builder(_sen);
		builder.Build();
		return builder.GetBaseInteractTable();
	}

	shared_ptr<Mind::iConceptInteractTable> SingleExpression::GetProtoInteractTable() const
	{
		if(_sen==NULL) return NULL;
		if(!_sen->StructureAnalyzed()) return NULL;

		WordRelationTableBuilder builder(_sen);
		builder.Build();
		return builder.GetProtoInteractTable();
	}

	shared_ptr<Mind::iConcept> SingleExpression::GetProtoConcept() const
	{
		unsigned int wordCount=_sen->GrammarWordCount();
		if(wordCount!=1)
		{
			return NULL;
		}

		shared_ptr<Word> word=_sen->GetGrammardWord(0);
		if(iCerebrum::Empty())
		{
			return NULL;
		}
		
		return iCerebrum::Instance()->GetConcept(word);
	}

}

