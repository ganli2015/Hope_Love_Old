#pragma once
#include "InOut.h"

namespace DataCollection
{
	class Sentence;
	class Word;
}

///Determine the type of sentence, including declarative sentence, Interrogative sentence and so on.
class _REACTIONANALYSISALGORITHMINOUT SentenceTypeDetermination
{
public:
	enum Type
	{
		Declarative,
		Interrogative
	};

private:

	static vector<shared_ptr<DataCollection::Word>> _interrogativePronouns;
	static vector<shared_ptr<DataCollection::Word>> _linkVerb;

	shared_ptr<DataCollection::Sentence> _questionPart;

public:
	SentenceTypeDetermination();
	~SentenceTypeDetermination();

	///Determine the type of the sentence.
	///For interrogative sentence, currently only linkVerb-interrogativePronouns pattern can be catch.
	///For example, "是多少","等于几".After using <Determine>, the question part will be extracted.
	///
	///If <sen> is not a interrogative sentence, it is declarative sentence for default.
	SentenceTypeDetermination::Type Determine(const shared_ptr<DataCollection::Sentence> sen);

	///Get the quetion part of the sentence.
	///Use <Determine> before!
	///It only works when the sentence is an interrogative sentence.
	///It extract the words between the link verb.
	shared_ptr<DataCollection::Sentence> GetQuestionPart() const { return _questionPart; }
private:

	void InitMyWords();

	bool IsInterrogative(const shared_ptr<DataCollection::Sentence> sen);
	shared_ptr<DataCollection::Sentence> ExtractQuetionPart(const shared_ptr<DataCollection::Sentence> sen,const int linkVerbIndex);
};

