#include "StdAfx.h"
#include "SingleExpression.h"

#include "../SentenceAnalysisAlgorithm/SentenceAnalyzer.h"

#include "../DataCollection/Sentence.h"

using namespace DataCollection;

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
// 		if(val->Count_Grammard()==0)
// 		{
// 			SentenceAnalyzer sentenceAnalyzer(val->GetString());
// 			sentenceAnalyzer.Analyze();
// 			_sen=sentenceAnalyzer.GetAnalyzedSentences();
// 		}
// 		else
// 		{
// 			_sen.pu
// 		}
	}

	SingleExpression::~SingleExpression(void)
	{
	}
}

