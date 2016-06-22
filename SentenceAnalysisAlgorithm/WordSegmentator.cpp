#include "StdAfx.h"
#include "WordSegmentator.h"

#include "../DataCollection/Sentence.h"
#include "../DataCollection/Word.h"
#include "../DataCollection/LanguageFunc.h"

#include "../MindInterface/iCerebrum.h"

#include "../Mathmatic/FindSequence.h"

using namespace std;
using namespace DataCollection;



WordSegmentator::WordSegmentator(shared_ptr<DataCollection::Sentence> sentence):_unsegmented(sentence)
{
}


WordSegmentator::~WordSegmentator(void)
{
}

void WordSegmentator::GetAllPossibleSequentialCombine(const vector<shared_ptr<Word>>& words, vector<vector<shared_ptr<Word>>>& combinations)
{
	//Get all continuous combinations of a word sequence.
	//For example, a b c, the result is a b c, ab c, a bc, and abc.
	combinations.clear();
	if(words.empty()) return;
	if(words.size()==1) 
	{
		combinations.push_back(words);
		return ;
	}

	//Use divide-and-conquer to get all combinations.
	//Each combination can be divide into two parts:
	//first few continuous words and all combinations of remaining words.
	//Then connect them.
	for (unsigned int i=0;i<words.size();++i)
	{
		//Collect first few continuous words.
		Word newword=*words[0];
		for (unsigned int j=1;j<=i;++j)
		{
			newword=newword+*words[j];
		}

		//Get all combinations of remaining words.
		vector<shared_ptr<Word>> restWords;
		restWords.insert(restWords.end(),words.begin()+i+1,words.end());
		vector<vector<shared_ptr<Word>>> tmp_combinations;
		GetAllPossibleSequentialCombine(restWords,tmp_combinations);
		
		//Connect.
		vector<vector<shared_ptr<Word>>> newtmp_combinations;
		if(tmp_combinations.empty())
		{
			vector<shared_ptr<Word>> new_combination;
			new_combination.push_back(shared_ptr<Word>(new Word(newword)));
			newtmp_combinations.push_back(new_combination);
		}
		else
		{
			for (unsigned int j=0;j<tmp_combinations.size();++j)
			{
				vector<shared_ptr<Word>> new_combination;
				new_combination.push_back(shared_ptr<Word>(new Word(newword)));
				new_combination.insert(new_combination.end(),tmp_combinations[j].begin(),tmp_combinations[j].end());
				newtmp_combinations.push_back(new_combination);
			}
		}
		

		combinations.insert(combinations.end(),newtmp_combinations.begin(),newtmp_combinations.end());
	}
}

void WordSegmentator::AppendLastKnownWordsToCombinations(const vector<shared_ptr<Word>>& words, const vector<vector<int>>& seqs_UandA, vector<vector<shared_ptr<Word>>>& combinations)
{
	//Collect the words behind the last U_A word.
	//As it reaches the end of U_A word, remaining words must be known words and 
	//there is only one combination.
	vector<shared_ptr<Word>> lastWords;
	int startIndex = *seqs_UandA.back().rbegin() + 1;
	for (unsigned int i = startIndex; i < words.size(); ++i)
	{
		lastWords.push_back(words[i]);
	}

	//Connect combinations with the last words.
	for (unsigned int i = 0; i < combinations.size(); ++i)
	{
		vector<shared_ptr<Word>> newComb = combinations[i];
		newComb.insert(newComb.end(), lastWords.begin(), lastWords.end());
		combinations[i] = newComb;
	}
}

vector<shared_ptr<Word>> WordSegmentator::CollectKnownWordsBetweenUandAWords(const vector<shared_ptr<Word>>& words, const vector<vector<int>>& seqs_UandA, const int index)
{
	//Collect the words between the end U_A word of last sequence and the start U_A word of current  sequence.
	//If <index> equals to 0, <forwardWords> is empty. 
	vector<shared_ptr<Word>> forwardWords;
	int seqStartIndex = seqs_UandA[index][0];
	int index_prev;
	if (index == 0)
	{
		index_prev = 0;
	}
	else
	{
		index_prev = *seqs_UandA[index - 1].rbegin() + 1;
	}
	for (int i = index_prev; i < seqStartIndex; ++i)
	{
		forwardWords.push_back(words[i]);
	}

	return forwardWords;
}

vector<vector<shared_ptr<Word>>> WordSegmentator::GenerateNewCombinations(const vector<shared_ptr<Word>>& forwardWords,
	const vector<vector<shared_ptr<Word>>>& combinations_UandA, vector<vector<shared_ptr<Word>>>& combinations)
{
	vector<vector<shared_ptr<Word>>> newCombinations;
	for (unsigned int i = 0; i < combinations_UandA.size(); ++i)
	{
		//If <index> is zero, <combinations> is empty.
		//Then connect  <forwardWords> and current U_A words for the first combination.
		//Otherwise, there are several combinations between <forwardWords> and 
		//we should connect <forwardWords> with each of combinations before it as well as current U_A words.
		if (combinations.empty())
		{
			vector<shared_ptr<Word>> aCombination;
			aCombination.insert(aCombination.end(), forwardWords.begin(), forwardWords.end());
			aCombination.insert(aCombination.end(), combinations_UandA[i].begin(), combinations_UandA[i].end());
			newCombinations.push_back(aCombination);
		}
		else
		{
			for (unsigned int j = 0; j < combinations.size(); ++j)
			{
				vector<shared_ptr<Word>> aCombination;
				aCombination.insert(aCombination.end(), combinations[j].begin(), combinations[j].end());
				aCombination.insert(aCombination.end(), forwardWords.begin(), forwardWords.end());
				aCombination.insert(aCombination.end(), combinations_UandA[i].begin(), combinations_UandA[i].end());
				newCombinations.push_back(aCombination);
			}
		}
	}

	return newCombinations;
}

void WordSegmentator::MergeCombination_UandA(const vector<shared_ptr<Word>>& words, const vector<vector<int>>& seqs_UandA , const int index,vector<vector<shared_ptr<Word>>>& combinations)
{
	//After reach the end of <seqs_UandA>, append the words behind the last U_A word to combinations.
	if(index==seqs_UandA.size())
	{
		AppendLastKnownWordsToCombinations(words, seqs_UandA, combinations);
		return ;
	}

	vector<shared_ptr<Word>> forwardWords = CollectKnownWordsBetweenUandAWords(words, seqs_UandA, index);
	
	//Collect all U_A words of current sequence and search all possible combinations.
	vector<shared_ptr<Word>> uandAwords(seqs_UandA[index].size());
	for (unsigned int i=0;i<seqs_UandA[index].size();++i)
	{
		uandAwords[i]=words[seqs_UandA[index][i]];
	}
	vector<vector<shared_ptr<Word>>> combinations_UandA;
	GetAllPossibleSequentialCombine(uandAwords,combinations_UandA);

	//Go through every U_A word combination.
	//And its diverse combination contribute to final diversity of sentence combinations.
	vector<vector<shared_ptr<Word>>> newCombinations=GenerateNewCombinations(forwardWords, combinations_UandA, combinations);

	//Step into the next U_A word sequence and continue to explore combinations.
	combinations=newCombinations;
	MergeCombination_UandA(words,seqs_UandA,index+1,combinations);

}

void WordSegmentator::SegmentMannersAccordingToUandA(const vector<shared_ptr<Word>>& words, vector<vector<shared_ptr<Word>>>& segmented)
{
	Mind::iCerebrum *brain=Mind::iCerebrum::Instance();

	//Collect all continuous U_A words in <words> and each of sequences will append to <seqs_UandA>.
	//There are many combinations in each continuous U_A sequence.
	unsigned int i=0;
	vector<vector<int>> seqs_UandA; 
	while(i<words.size())
	{
		vector<int> seq_UandA;
		while(i<words.size() && brain->GetAllKindsofWord(words[i]).empty())//if the word is unknown or ambiguous
		{
			seq_UandA.push_back(i++);
		}

		if(!seq_UandA.empty())
		{
			seqs_UandA.push_back(seq_UandA);
		}
		++i;
	}

	//If there is no U_A words, then there is only one combination.
	//Otherwise, go through all U_A words and find all combinations.
	if(seqs_UandA.empty())
	{
		segmented.push_back(words);
		return ;
	}
	else
	{
		MergeCombination_UandA(words,seqs_UandA,0,segmented);
	}

}

bool WordSegmentator::Segment(  )
{
	for (unsigned int i=0;i<_unsegmented->Count_SubSentence();++i)
	{
		SegmentSubsentence(_unsegmented->GetSubSentence(i));
	}

 	return true;
}

void WordSegmentator::SegmentSubsentence( const string subsentence )
{
	//Separate words with punctuations as only words need to be segmented.
	vector<Character> raw=ConvertStringToCharacter(subsentence);
	pair<vector<Character>,vector<Character>> sen_punc =LanguageFunc::TrimEndPunctures(raw);
	vector<Character> raw_noPunc=sen_punc.first;
	vector<Character> punc=sen_punc.second;

	vector<CharacterProperty> vec_characterProperty;
	//Find the candidate word of each character.
	//The first character of each word is <chara>.
	for (unsigned int i=0;i<raw_noPunc.size();++i)
	{
		Character chara=raw_noPunc[i];
		CharacterProperty characterProperty=GenerateCharacterProperty(chara,i,raw_noPunc);

		vec_characterProperty.push_back(characterProperty);
	}

	//Pick the longest candidate word of each character to compose the sentence.
	//It is experiential.We assume the sentence made with fewest words as possible.
	unsigned int index(0);
	vector<shared_ptr<Word>> initial_segmented;
	while(index<raw_noPunc.size())
	{
		Word candidate=*(vec_characterProperty[index].candidate.rbegin());
		int step=candidate.NumOfChara();
		initial_segmented.push_back(shared_ptr<Word>(new Word(candidate)));
		index+=step;
	}

	//Collect all combinations according to U_A words.
	//How to determine the desired combination is things behind.
	vector<vector<shared_ptr<Word>>> segmented;
	SegmentMannersAccordingToUandA(initial_segmented,segmented);

	//Recover punctuations.
	vector<shared_ptr<Word>> punc_words=LanguageFunc::ConvertPuncturesToWords(punc);
	for (unsigned int i=0;i<segmented.size();++i)
	{
		vector<shared_ptr<Word>> seg_withPunc=segmented[i];
		seg_withPunc.insert(seg_withPunc.end(),punc_words.begin(),punc_words.end());
		
		_segmented.insert(make_pair(subsentence,shared_ptr<SegmentedSentence>(new SegmentedSentence(seg_withPunc))));
	}
}

WordSegmentator::CharacterProperty WordSegmentator::GenerateCharacterProperty(const Character& chara,const int myIndex,const vector<Character>& raw_noPunc)
{
	Mind::iCerebrum* brain=Mind::iCerebrum::Instance();

	CharacterProperty characterProperty;
	characterProperty.character=chara;
	characterProperty.index=myIndex;
	Word curWord(chara.GetString());
	if(brain->IsInMind(shared_ptr<Word>(new Word(curWord))))
	{
		curWord.KnowIt();
	}
	//The current character must be a candidate whether it is unknown or not.
	//This is for the following computation.
	characterProperty.candidate.push_back(curWord);

	//Determine the longest candidate of <character>.
	//We do not need to search to the end of the sentence, but only to search to the max possible length of candidates.
	unsigned int maxLength_Word=brain->MaxLength_WordWithHead(shared_ptr<Character>(new Character(chara)));//Get the max length of the forward adjacent word, to determine how further we should search in the raw sentence.
	Word possibleWord(chara.GetString());//find the possible word related with the character
	for (unsigned int j=1;j<=maxLength_Word;++j)
	{
		if(myIndex+j>=raw_noPunc.size())//if exceed the raw sentence.
			break;

		possibleWord+=raw_noPunc[myIndex+j];
		if(brain->IsInMind(shared_ptr<Word> (new Word(possibleWord))))
		{
			possibleWord.KnowIt();
			characterProperty.candidate.push_back(possibleWord);
		}
	}

	return characterProperty;
}

std::vector<Character> WordSegmentator::GetRawSentence( shared_ptr<DataCollection::Sentence> sentence ) const
{
	vector<shared_ptr<Character>> raw=sentence->GetRawSentence();
	vector<Character> res;
	for (unsigned int i=0;i<raw.size();++i)
	{
		res.push_back(*raw[i]);
	}

	return res;
}

std::vector<DataCollection::Character> WordSegmentator::ConvertStringToCharacter( const string str ) const
{
	vector<shared_ptr<Character>> ptrCharas=LanguageFunc::ConvertStringToCharacter(str);
	vector<Character> res;
	res.reserve(ptrCharas.size());
	for (unsigned int i=0;i<ptrCharas.size();++i)
	{
		res.push_back(*ptrCharas[i]);
	}

	return res;
}

vector<shared_ptr<DataCollection::SegmentedSentence>> WordSegmentator::GetAllSegementedSentence() const
{
	//Collect all manners of segmentation of all sub sentences.
	//Each element of <subSentenSeg> is all manners of segmentation of one sub sentence.
	vector<vector<shared_ptr<SegmentedSentence>>> subSentenSeg; 
	for (unsigned int i=0;i<_unsegmented->Count_SubSentence();++i)
	{
		string subStr=_unsegmented->GetSubSentence(i);
		multimap<string,shared_ptr<SegmentedSentence>>::const_iterator beg=_segmented.lower_bound(subStr);
		multimap<string,shared_ptr<SegmentedSentence>>::const_iterator end=_segmented.upper_bound(subStr);

		vector<shared_ptr<SegmentedSentence>> allSeg;
		while(beg!=end)
		{
			allSeg.push_back(beg->second);
			beg++;
		}

		subSentenSeg.push_back(allSeg);
	}

	//Go through all combinations of each sub sentence and connect them into all possible sentence.
	vector<vector<shared_ptr<SegmentedSentence>>> segSequence= Math::GetAllCombinations<shared_ptr<SegmentedSentence>>::Get(subSentenSeg);
	
	vector<shared_ptr<SegmentedSentence>> res;
	res.reserve(segSequence.size());
	for (unsigned int i=0;i<segSequence.size();++i)
	{
		vector<shared_ptr<Word>> wholeWords;
		vector<shared_ptr<SegmentedSentence>> oneSequence=segSequence[i];
		for (unsigned int j=0;j<oneSequence.size();++j)
		{
			vector<shared_ptr<Word>> oneSeqWords=oneSequence[j]->Get();
			wholeWords.insert(wholeWords.end(),oneSeqWords.begin(),oneSeqWords.end());
		}

		res.push_back(shared_ptr<SegmentedSentence>(new SegmentedSentence(wholeWords)));
	}

	return res;
}


