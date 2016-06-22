#pragma once
#include "InOut.h"
//#include "../DataCollection/Character.h"

namespace DataCollection
{
	class Sentence;
	class Word;
}
class Punctuator;

class _SENTENCEANALYSISALGORITHMINOUT SentenceAnalyzer
{
	std::string _rawSentenceString;
	shared_ptr<DataCollection::Sentence> _analyzedSentences;
	
	vector<shared_ptr<DataCollection::Word>> _unknownWords;
public:
	SentenceAnalyzer(void);
	~SentenceAnalyzer(void);
	SentenceAnalyzer(const std::string sen);

	///Analyze the input sentence and generate the internal relation between words in the sentence.
	void Analyze();

	///Return the unknown words in the input sentence.
	vector<shared_ptr<DataCollection::Word>> GetUnknownWords() const {return _unknownWords;};
	shared_ptr<DataCollection::Sentence> GetAnalyzedSentences() const {return _analyzedSentences;}
private:
	void Cout_GrammardSentence(const shared_ptr<DataCollection::Sentence> grammard);
	void Cout_WordConnectionIntensity(const shared_ptr<DataCollection::Sentence> sentence);

	vector<shared_ptr<DataCollection::Word>> CountUnknownWords(const shared_ptr<DataCollection::Sentence>& sentences) const;
};

