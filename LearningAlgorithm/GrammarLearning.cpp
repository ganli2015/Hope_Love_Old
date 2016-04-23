#include "StdAfx.h"
#include "GrammarLearning.h"

#include "../DataCollection/Word.h"
#include "../DataCollection/Sentence.h"
#include "../DataCollection/GrammaPattern.h"
#include "../DataCollection/DataBaseProcessorTool.h"

#include "../Mind/Cerebrum.h"

using namespace DataCollection;

GrammarLearning::GrammarLearning(void)
{
}


GrammarLearning::~GrammarLearning(void)
{
}

void GrammarLearning::AdjustGrammarPatternFrequency( const shared_ptr<DataCollection::Sentence> sentence )
{
	Mind::Cerebrum* brain=Mind::Cerebrum::Instance();

	vector<shared_ptr<Word>> words=DataBaseProcessorTool::RemovePuncs(sentence->GetGrammard());
	vector<GrammarPattern> matchedPatterns=brain->ContainSubsequence(DataBaseProcessorTool::ConvertToPattern(words));

	class IncreaseFrequency
	{
		Mind::Cerebrum* _brain;
	public:
		IncreaseFrequency()
		{
			_brain=Mind::Cerebrum::Instance();
		}
		~IncreaseFrequency(){}

		void operator()(const GrammarPattern& pattern)
		{
			_brain->IncreasePatternFreqency(pattern);
		}
	};

	for_each(matchedPatterns.begin(),matchedPatterns.end(),IncreaseFrequency());
}
