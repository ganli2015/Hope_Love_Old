#pragma once
#include "InOut.h" 

namespace DataCollection
{
	class Sentence;
	class Word;
}

namespace Mind
{
	class ConceptInteractTable;
}

class WordRelationTableBuilder
{
	shared_ptr<DataCollection::Sentence> _raw_sen;//unanalyzed

	shared_ptr<Mind::ConceptInteractTable> _table;
public:
	WordRelationTableBuilder( shared_ptr<DataCollection::Sentence> sen);
	~WordRelationTableBuilder(void);

	bool Build();

	shared_ptr<Mind::ConceptInteractTable> GetInteractTable() const {return _table;}

private:
	shared_ptr<Mind::ConceptInteractTable> BuildConceptInteractTable( const shared_ptr<DataCollection::Word> from,const shared_ptr<DataCollection::Word> to);
};

