#include "StdAfx.h"
#include "WordRelationTableBuilder.h"

#include "../DataCollection/Sentence.h"
#include "../DataCollection/WordRelationTable.h"
#include "../DataCollection/Word.h"

#include "../Mind/Cerebrum.h"
#include "../Mind/Concept.h"

using namespace DataCollection;
using namespace Mind;

WordRelationTableBuilder::WordRelationTableBuilder( shared_ptr<DataCollection::Sentence> sen):_raw_sen(sen)
{
}


WordRelationTableBuilder::~WordRelationTableBuilder(void)
{
}

bool WordRelationTableBuilder::Build()
{
	Mind::Cerebrum* brain=Mind::Cerebrum::Instance();

	double intensity_lowerlimit=1./10;

	int grammarIndex=0;
	for (unsigned int i=0;i<_raw_sen->GrammarWordCount(grammarIndex);++i)//暂时只考虑第一个语法句子
	{
		for (unsigned int j=i+1;j<_raw_sen->GrammarWordCount(grammarIndex);++j)
		{
			double intensity=_raw_sen->GetWordIntensity(grammarIndex,i,j);
			if(intensity>intensity_lowerlimit)
			{
				vector<shared_ptr<Word>> words=_raw_sen->GetGrammard(grammarIndex);
				BuildConceptInteractTable(words[i],words[j]);
			}
		}
	}

	return true;
}

void WordRelationTableBuilder::BuildConceptInteractTable( const shared_ptr<DataCollection::Word> from,const shared_ptr<DataCollection::Word> to)
{
	Mind::Cerebrum* brain=Mind::Cerebrum::Instance();

	shared_ptr<Concept> fromConcept=brain->GetConcept(from);
	shared_ptr<Concept> toConcept=brain->GetConcept(to);
	
	brain->BuildConceptInteractTable(fromConcept,toConcept);
}