#pragma once
#include "InOut.h"
#include "Reaction.h"

namespace DataCollection
{
	class Sentence;
}

namespace Mind
{
	class iConceptInteractTable;
}

class _REACTIONLISTINOUT SpeakReaction:public Reaction
{
	vector<shared_ptr<DataCollection::Sentence>> _sentence_input;
	shared_ptr<Mind::iConceptInteractTable> _interactTable;

	vector<shared_ptr<DataCollection::Sentence>> _sentence_output;

public:
	SpeakReaction(void);
	~SpeakReaction(void);

	SpeakReaction(const vector<shared_ptr<DataCollection::Sentence>> sentence,const shared_ptr<Mind::iConceptInteractTable> interactTable);

	virtual void React();

	shared_ptr<DataCollection::Sentence> GetReactSentence() const;
};

