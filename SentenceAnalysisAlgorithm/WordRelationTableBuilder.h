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

	//An interact table that contain interactions between prototype concepts.
	shared_ptr<Mind::iConceptInteractTable> _protoTable;
	//An interact table that contain interactions between base concepts of prototype concepts.
	shared_ptr<Mind::iConceptInteractTable> _baseTable;
public:
	WordRelationTableBuilder( shared_ptr<DataCollection::Sentence> sen);
	~WordRelationTableBuilder(void);

	///Build a table containing interactions between concepts of the input sentence.
	bool Build();
	///Return the interact table that contain interactions between base concepts of prototype concepts.
	const shared_ptr<Mind::iConceptInteractTable> GetBaseInteractTable() const {return _baseTable;}
	///Return the interact table that contain interactions between prototype concepts.
	const shared_ptr<Mind::iConceptInteractTable> GetProtoInteractTable() const {return _protoTable;}

private:
	void BuildConceptInteractTable( const shared_ptr<DataCollection::Word> from,const shared_ptr<DataCollection::Word> to);
};

