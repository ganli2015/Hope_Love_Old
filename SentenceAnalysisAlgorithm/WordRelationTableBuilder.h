#pragma once
#include "InOut.h" 

namespace DataCollection
{
	class Sentence;
	class Word;
}

namespace Mind
{
	class iConceptInteractTable;
}

class _SENTENCEANALYSISALGORITHMINOUT WordRelationTableBuilder
{
	shared_ptr<DataCollection::Sentence> _raw_sen;//unanalyzed

	shared_ptr<Mind::iConceptInteractTable> _table;
public:
	WordRelationTableBuilder( shared_ptr<DataCollection::Sentence> sen);
	~WordRelationTableBuilder(void);

	bool Build();

	shared_ptr<Mind::iConceptInteractTable> GetInteractTable() const {return _table;}

private:
	shared_ptr<Mind::iConceptInteractTable> BuildConceptInteractTable( const shared_ptr<DataCollection::Word> from,const shared_ptr<DataCollection::Word> to);
};

