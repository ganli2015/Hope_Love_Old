#pragma once
#include "InOut.h"

namespace DataCollection
{
	class Sentence;
	class Word;
}

namespace Mind
{
	class iConceptChain;
	class iConceptInteractTable;
	struct ConceptChainProperty;
}


class _REACTIONANALYSISALGORITHMINOUT ReactionParser
{
	vector<shared_ptr<DataCollection::Sentence>> _sentence_input;
	shared_ptr<Mind::iConceptInteractTable> _interactTable;

	vector<shared_ptr<DataCollection::Sentence>> _sentence_output;

	

public:
	ReactionParser(void);
	~ReactionParser(void);
	ReactionParser(const vector<shared_ptr<DataCollection::Sentence>> sentence,const shared_ptr<Mind::iConceptInteractTable> interactTable);

	void Execute();
	shared_ptr<DataCollection::Sentence> GetReactSentence() const;
private:
	vector<shared_ptr<DataCollection::Sentence>> GenerateByConceptChainAnalysis() const;
	vector<shared_ptr<DataCollection::Sentence>> GenerateByLogicAnalysis() const;

	vector<shared_ptr<DataCollection::Word>> CountUnknownWords(const vector<shared_ptr<DataCollection::Sentence>>& sentences) const;

	void DisplayChain( const shared_ptr<Mind::iConceptChain>& chain ) const;
	void DisplayReactChains( const vector<Mind::ConceptChainProperty>& chains ) const;
	void DisplayHyperChains( const vector<shared_ptr<Mind::iConceptChain>>& chains ) const;
};

