#pragma once
#include "InOut.h" 

namespace DataCollection
{
	class Sentence;
	class Word;
}

class WordRelationTableBuilder
{
	shared_ptr<DataCollection::Sentence> _raw_sen;//unanalyzed

public:
	WordRelationTableBuilder( shared_ptr<DataCollection::Sentence> sen);
	~WordRelationTableBuilder(void);

	bool Build();

private:
	void BuildConceptInteractTable( const shared_ptr<DataCollection::Word> from,const shared_ptr<DataCollection::Word> to);
};

