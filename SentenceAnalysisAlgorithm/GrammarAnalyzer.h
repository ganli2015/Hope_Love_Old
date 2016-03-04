#pragma once
#include "InOut.h"
#include <map>

namespace DataCollection
{
	class Sentence;
	class Word;
	class GrammarPattern;
}

class  GrammarAnalyzer
{
	shared_ptr<DataCollection::Sentence> _raw_sen;//unanalyzed
public:
	GrammarAnalyzer(void);
	~GrammarAnalyzer(void);
	GrammarAnalyzer( shared_ptr<DataCollection::Sentence> sen);

	bool Analyze();
	shared_ptr<DataCollection::Sentence> GetResult() const {return _raw_sen;}

private:
	void OptimizePOSofWords();
	void BuildGrammarAssociationOfWords();
};

class WordRep;

WordRep GetWordRep(shared_ptr<DataCollection::Word> word);
int CheckUnknownWords(const vector<shared_ptr<DataCollection::Word>>& words);
int CheckAmbiguousWords(const vector<WordRep>& words);
void GetAllPossibleCombine(const int index, const vector<WordRep>& wordRepSet, vector<vector<shared_ptr<DataCollection::Word>>>& out);
void GetAllUnknownAmbiguousCombine(const vector<shared_ptr<DataCollection::Word>> words, const int index, vector<vector<shared_ptr<DataCollection::Word>>>& out);
vector<vector<shared_ptr<DataCollection::Word>>> SpanUnknownAndAmbiguousToEveryPOS(const vector<shared_ptr<DataCollection::Word>> words);
void SelectOptimalGrammarPattern(const vector<vector<shared_ptr<DataCollection::Word>>>& combination, vector<shared_ptr<DataCollection::Word>>& optimal);
void AddGrammarPatternsToMind(const vector<DataCollection::GrammarPattern>& patterns);