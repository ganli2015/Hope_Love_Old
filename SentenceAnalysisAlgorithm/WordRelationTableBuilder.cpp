#include "StdAfx.h"
#include "WordRelationTableBuilder.h"

#include "../DataCollection/Sentence.h"
#include "../DataCollection/WordRelationTable.h"
#include "../DataCollection/Word.h"

#include "../MindInterface/iCerebrum.h"
#include "../MindInterface/iConceptInteractTable.h"
#include "../MindInterface/iConcept.h"
#include "../MindInterface/iMindElementCreator.h"

#include "../MindElement/ConceptInteractTable.h"

using namespace DataCollection;
using namespace Mind;

WordRelationTableBuilder::WordRelationTableBuilder( shared_ptr<DataCollection::Sentence> sen):_raw_sen(sen)
{
	_protoTable=iMindElementCreator::CreateConceptInteractTable();
	_baseTable=iMindElementCreator::CreateConceptInteractTable();
}


WordRelationTableBuilder::~WordRelationTableBuilder(void)
{
}

bool WordRelationTableBuilder::Build()
{
	Mind::iCerebrum* brain=Mind::iCerebrum::Instance();

	//The lower limit of the intensity.
	//Only if the intensity of two concepts is above the limit,then the pair will contribute to the result.
	double intensity_lowerlimit=1./10;

	for (unsigned int i=0;i<_raw_sen->GrammarWordCount();++i)
	{
		for (unsigned int j=i+1;j<_raw_sen->GrammarWordCount();++j)
		{
			double intensity=_raw_sen->GetWordIntensity(i,j);
			if(intensity>intensity_lowerlimit)
			{
				vector<shared_ptr<Word>> words=_raw_sen->GetGrammard();
				BuildConceptInteractTable(words[i],words[j]);			
			}
		}
	}

	return true;
}

void WordRelationTableBuilder::BuildConceptInteractTable( const shared_ptr<DataCollection::Word> from,const shared_ptr<DataCollection::Word> to)
{
	Mind::iCerebrum* brain=Mind::iCerebrum::Instance();

	shared_ptr<iConcept> fromConcept=brain->GetConcept(from);
	shared_ptr<iConcept> toConcept=brain->GetConcept(to);

	//If either of from or to concept is null, we cannot get the interaction concept pairs of their base concepts,
	//as AI has no knowledge of the null concept.
	if(fromConcept!=NULL && toConcept!=NULL)
	{
		shared_ptr<iConceptInteractTable> baseTable = fromConcept->DeepInteractWith(toConcept);
		_baseTable->Absorb(baseTable);
		_protoTable->Add(fromConcept, toConcept);
	}
	

}