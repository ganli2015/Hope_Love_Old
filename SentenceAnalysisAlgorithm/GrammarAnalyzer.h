#pragma once
#include "InOut.h"
#include <map>

namespace DataCollection
{
	class Sentence;
	class SegmentedSentence;
	class Word;
	class GrammarPattern;
}

class WordRep;

class  _SENTENCEANALYSISALGORITHMINOUT GrammarAnalyzer
{
private:

	enum AnalyzeResult
	{
		TooManyUknownWords,
		TooManyAmbiguousWords,
		Fine
	};

	shared_ptr<DataCollection::Sentence> _raw_sen;//unanalyzed
	vector<shared_ptr<DataCollection::SegmentedSentence>> _segments;

public:
	GrammarAnalyzer(void);
	~GrammarAnalyzer(void);
	GrammarAnalyzer( shared_ptr<DataCollection::Sentence> sen);

	///Analyze input segmented sentences and mark each word of sentence with the most optimal POS.
	///And build association among words according to their internal grammar pattern.
	///Currently I can only copy with sentences with only one puntuation of end side.
	bool Analyze();
	///Add segmented manner of the input sentence.
	///Each segmented sentence will contribute to grammar analysis of the input sentence.
	void AddSegment(const shared_ptr<DataCollection::SegmentedSentence> sentence) {_segments.push_back(sentence);}

private:
	///Mark each word of sentence with the most optimal POS.
	void OptimizePOSofWords();
	///Build association among words according to their internal grammar pattern.
	///The association information are recorded in the input sentence.
	void BuildGrammarAssociationOfWords();

	///Get all words of possible POS in Cerebrum.
	///If <word> is not in Cerebrum, returned <WordRep> still contain <word>.
	WordRep GetWordRep(shared_ptr<DataCollection::Word> word);
	///Count the number of unknown words.
	int CheckUnknownWords(const vector<shared_ptr<DataCollection::Word>>& words);
	///Count the number of ambiguous words.
	int CheckAmbiguousWords(const vector<WordRep>& words);
	///Get all possible combination of the sentence.
	///Each word has several POS, and consider all possible combination of them.
	void GetAllPossibleCombine(const int index, const vector<WordRep>& wordRepSet, vector<vector<shared_ptr<DataCollection::Word>>>& out);
	

	void GetAllUnknownAmbiguousCombine(const vector<shared_ptr<DataCollection::Word>> words, const int index, vector<vector<shared_ptr<DataCollection::Word>>>& out);
	///Span the word <words[index]> through all kinds of POS.
	///Then connect them with previous calculated combinations <latterCombinations>.
	vector<vector<shared_ptr<DataCollection::Word>>> SpanUandAWords(const vector<shared_ptr<DataCollection::Word>>& words, const int index, const vector<vector<shared_ptr<DataCollection::Word>>>& latterCombinations);
	void SpanNonUandAWords(const vector<shared_ptr<DataCollection::Word>> words, const int index, vector<vector<shared_ptr<DataCollection::Word>>>& out);
	///If there are U_A words in <words>, I consider each U_A word's POS range from Noun to Interjection.
	///And get all possible combinations according to U_A words.
	vector<vector<shared_ptr<DataCollection::Word>>> SpanUnknownAndAmbiguousToEveryPOS(const vector<shared_ptr<DataCollection::Word>> words);
	///Select the most optimal combination according to grammar patterns.
	void SelectOptimalGrammarPattern(const vector<vector<shared_ptr<DataCollection::Word>>>& combination, vector<shared_ptr<DataCollection::Word>>& optimal);

	GrammarAnalyzer::AnalyzeResult AnalyzeEachSegmented(const vector<shared_ptr<DataCollection::Word>>& segmented, vector<shared_ptr<DataCollection::Word>> &optimal);
	vector<WordRep> SearchAllWordRep(const vector<shared_ptr<DataCollection::Word>>& segmented_withNoPunc);

};

