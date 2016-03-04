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
	vector<shared_ptr<DataCollection::Sentence>> _analyzedSentences;
	
	vector<shared_ptr<DataCollection::Word>> _unknownWords;
public:
	SentenceAnalyzer(void);
	~SentenceAnalyzer(void);
	SentenceAnalyzer(std::string sen);

	void Analyze();

	vector<shared_ptr<DataCollection::Word>> GetUnknownWords() const {return _unknownWords;};
	vector<shared_ptr<DataCollection::Sentence>> GetAnalyzedSentences() const {return _analyzedSentences;}
private:
	void Cout_GrammardSentence(const shared_ptr<DataCollection::Sentence> grammard);
	void Cout_WordConnectionIntensity(const shared_ptr<DataCollection::Sentence> sentence);
	void Cout_WordRelations();
};

