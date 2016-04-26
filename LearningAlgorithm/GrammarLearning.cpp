#include "StdAfx.h"
#include "GrammarLearning.h"

#include "../DataCollection/Word.h"
#include "../DataCollection/Sentence.h"
#include "../DataCollection/GrammaPattern.h"
#include "../DataCollection/DataBaseProcessorTool.h"

#include "../MindInterface/iCerebrum.h"

using namespace DataCollection;

GrammarLearning::GrammarLearning(void)
{
}


GrammarLearning::~GrammarLearning(void)
{
}

void GrammarLearning::AdjustGrammarPatternFrequency( const shared_ptr<DataCollection::Sentence> sentence )
{
	Mind::iCerebrum* brain=Mind::iCerebrum::Instance();

	vector<shared_ptr<Word>> words=DataBaseProcessorTool::RemovePuncs(sentence->GetGrammard());
	vector<GrammarPattern> matchedPatterns=brain->ContainSubsequence(DataBaseProcessorTool::ConvertToPattern(words));

	class IncreaseFrequency
	{
		Mind::iCerebrum* _brain;
	public:
		IncreaseFrequency()
		{
			_brain=Mind::iCerebrum::Instance();
		}
		~IncreaseFrequency(){}

		void operator()(const GrammarPattern& pattern)
		{
			_brain->IncreasePatternFreqency(pattern);
		}
	};

	for_each(matchedPatterns.begin(),matchedPatterns.end(),IncreaseFrequency());
}
