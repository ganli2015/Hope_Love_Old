#pragma once
#include "InOut.h"

namespace DataCollection
{
	class Sentence;
}

namespace Mind
{
	class iConceptInteractTable;
}

class _SENTENCEANALYSISALGORITHMINOUT SentenceParser
{
	std::string _sentence;
	shared_ptr<DataCollection::Sentence> _parsedSentence;

	shared_ptr<Mind::iConceptInteractTable> _conceptTable;
public:
	SentenceParser(void);
	~SentenceParser(void);
	SentenceParser(const std::string sen);

	void Execute();
	shared_ptr<DataCollection::Sentence> GetParsedSentence() const {return _parsedSentence;}
	shared_ptr<Mind::iConceptInteractTable> GetInteractTable() const {return _conceptTable;}
private:
	void Cout_WordRelations();
};

