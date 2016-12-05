#pragma once
#include "InOut.h"
#include "../DataCollection/Character.h"
#include "map"

namespace DataCollection
{
	class Word;
	class Sentence;
	class SegmentedSentence;
}

class _SENTENCEANALYSISALGORITHMINOUT WordSegmentator
{
public:
	enum SegmentMethod
	{
		Forward,
		Backward
	};


private:

    shared_ptr<DataCollection::Sentence> _unsegmented;

	///Sentences after segmented.Key is strings of sentences and value is sentences.
	multimap<string,shared_ptr<DataCollection::SegmentedSentence>> _segmented;

	SegmentMethod _segMethod;


public:
	///<sentence> must be punctuated before.
	WordSegmentator(shared_ptr<DataCollection::Sentence> sentence);
	~WordSegmentator(void);

	///Segment the input sentence into individual words.
	///Those words have no definite POS.Their POS have not been deduced.
	bool Segment();

	vector<shared_ptr<DataCollection::SegmentedSentence>> GetAllSegementedSentence() const;

	void SetSegmentMethod(const SegmentMethod method) { _segMethod = method; }

private:
	
	struct CharacterProperty
	{
		DataCollection::Character character;
		///The candidates of words related with <character>.
		vector<DataCollection::Word> candidate;
		///the index of <character> in a sentence.
		int index;
	};

	///Segment each subsentence.
	void SegmentSubsentence(const string subsentence);

	vector<shared_ptr<DataCollection::Word>> ForwardSegment(const vector<DataCollection::Character>& raw_noPunc) const;
	vector<shared_ptr<DataCollection::Word>> BackwardSegment(const vector<DataCollection::Character>& raw_noPunc) const;

	std::vector<DataCollection::Character> GetRawSentence(shared_ptr<DataCollection::Sentence> sentence) const;
	std::vector<DataCollection::Character> ConvertStringToCharacter(const string str) const ;
	WordSegmentator::CharacterProperty GenerateCharacterProperty(const DataCollection::Character& chara,const int myIndex,const vector<DataCollection::Character>& raw_noPunc) const;

	///Get all combinations considering the different combination of U_A words.
	void SegmentMannersAccordingToUandA(const vector<shared_ptr<DataCollection::Word>>& words, vector<vector<shared_ptr<DataCollection::Word>>>& segmented);
	vector<vector<int>> ComputeUandAIndexes(const vector<shared_ptr<DataCollection::Word>>& words);
	void GetAllPossibleSequentialCombine(const vector<shared_ptr<DataCollection::Word>>& words, vector<vector<shared_ptr<DataCollection::Word>>>& combinations);

	///Connect the <newword> with all <sub_combinations>
	///and return new connected sentences.
	vector<vector<shared_ptr<DataCollection::Word>>> ConnectCurrentWordWithSubCombinations(const DataCollection::Word& newword, const vector<vector<shared_ptr<DataCollection::Word>>>& sub_combinations);
	///Search all possible combinations of unknown and ambiguous words in <words> and output them <combinations>.
	///<seqs_UandA> are indexes of unknown and ambiguous words in words.
	///When U_A words in <words> are continuous , there will be several combinations of them.
	///Then one element of <seqs_UandA> is one continuous U_A word sequence in <words>.
	void MergeCombination_UandA(const vector<shared_ptr<DataCollection::Word>>& words, const vector<vector<int>>& seqs_UandA, const int index, vector<vector<shared_ptr<DataCollection::Word>>>& combinations);
	///Append the words behind the last U_A word to combinations.
	void AppendLastKnownWordsToCombinations(const vector<shared_ptr<DataCollection::Word>>& words, const vector<vector<int>>& seqs_UandA, vector<vector<shared_ptr<DataCollection::Word>>>& combinations);
	///Collect the words between the end word of seqs_UandA[index-1] and the start word of seqs_UandA[index] .
	///They are all known words.
	vector<shared_ptr<DataCollection::Word>> CollectKnownWordsBetweenUandAWords(const vector<shared_ptr<DataCollection::Word>>& words, const vector<vector<int>>& seqs_UandA, const int index);
	vector<vector<shared_ptr<DataCollection::Word>>> GenerateNewCombinations(const vector<shared_ptr<DataCollection::Word>>& forwardWords, const vector<vector<shared_ptr<DataCollection::Word>>>& combinations_UandA, vector<vector<shared_ptr<DataCollection::Word>>>& combinations);
};
