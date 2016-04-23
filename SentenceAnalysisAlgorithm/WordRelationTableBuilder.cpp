#include "StdAfx.h"
#include "WordRelationTableBuilder.h"

#include "../DataCollection/Sentence.h"
#include "../DataCollection/WordRelationTable.h"
#include "../DataCollection/Word.h"

#include "../Mind/Cerebrum.h"
#include "../MindElement/Concept.h"
#include "../MindElement/ConceptInteractTable.h"

using namespace DataCollection;
using namespace Mind;

WordRelationTableBuilder::WordRelationTableBuilder( shared_ptr<DataCollection::Sentence> sen):_raw_sen(sen),_table(shared_ptr<ConceptInteractTable>(new ConceptInteractTable()))
{
}


WordRelationTableBuilder::~WordRelationTableBuilder(void)
{
}

bool WordRelationTableBuilder::Build()
{
	Mind::Cerebrum* brain=Mind::Cerebrum::Instance();

	double intensity_lowerlimit=1./10;

	for (unsigned int i=0;i<_raw_sen->GrammarWordCount();++i)//暂时只考虑第一个语法句子
	{
		for (unsigned int j=i+1;j<_raw_sen->GrammarWordCount();++j)
		{
			double intensity=_raw_sen->GetWordIntensity(i,j);
			if(intensity>intensity_lowerlimit)
			{
				vector<shared_ptr<Word>> words=_raw_sen->GetGrammard();
				shared_ptr<ConceptInteractTable> tmpTable=BuildConceptInteractTable(words[i],words[j]);
				_table->Absorb(tmpTable);
			}
		}
	}

	return true;
}

shared_ptr<ConceptInteractTable> WordRelationTableBuilder::BuildConceptInteractTable( const shared_ptr<DataCollection::Word> from,const shared_ptr<DataCollection::Word> to)
{
	Mind::Cerebrum* brain=Mind::Cerebrum::Instance();

	shared_ptr<Concept> fromConcept=brain->GetConcept(from);
	shared_ptr<Concept> toConcept=brain->GetConcept(to);
	
	return fromConcept->DeepInteractWith(toConcept);
}