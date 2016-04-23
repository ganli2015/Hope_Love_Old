#include "StdAfx.h"
#include "WordSegmentator.h"

#include "../DataCollection/Sentence.h"
#include "../DataCollection/Word.h"
#include "../DataCollection/DataBaseProcessorTool.h"

#include "../Mind/Cerebrum.h"

#include "../Mathmatic/FindSequence.h"

using namespace std;
using namespace DataCollection;



WordSegmentator::WordSegmentator(shared_ptr<DataCollection::Sentence> sentence):_unsegmented(sentence)
{
}


WordSegmentator::~WordSegmentator(void)
{
}

void GetAllPossibleSequentialCombine(const vector<shared_ptr<Word>>& words, vector<vector<shared_ptr<Word>>>& combinations)
{
	combinations.clear();
	if(words.empty()) return;
	if(words.size()==1) 
	{
		combinations.push_back(words);
		return ;
	}

	for (unsigned int i=0;i<words.size();++i)
	{
		Word newword=*words[0];
		for (unsigned int j=1;j<=i;++j)
		{
			newword=newword+*words[j];
		}

		vector<shared_ptr<Word>> restWords;
		restWords.insert(restWords.end(),words.begin()+i+1,words.end());
		vector<vector<shared_ptr<Word>>> tmp_combinations;
		GetAllPossibleSequentialCombine(restWords,tmp_combinations);
		
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

void MergeCombination_UandA(const vector<shared_ptr<Word>>& words, const vector<vector<int>>& seqs_UandA , const int index,vector<vector<shared_ptr<Word>>>& combinations)
{
	if(index==seqs_UandA.size())
	{
		vector<shared_ptr<Word>> lastWords;
		int startIndex=*seqs_UandA[index-1].rbegin()+1;
		
		for (unsigned int i=startIndex;i<words.size();++i)
		{
			lastWords.push_back(words[i]);
		}

		for (unsigned int i=0;i<combinations.size();++i)
		{
			vector<shared_ptr<Word>> newComb=combinations[i];
			newComb.insert(newComb.end(),lastWords.begin(),lastWords.end());
			combinations[i]=newComb;
		}

		return ;
	}

	vector<shared_ptr<Word>> forwardWords;
	int seqStartIndex=seqs_UandA[index][0];
	int index_prev;
	if(index==0)
	{
		index_prev=0;
	}
	else
	{
		index_prev=*seqs_UandA[index-1].rbegin()+1;
	}
	for (int i=index_prev;i<seqStartIndex;++i)
	{
		forwardWords.push_back(words[i]);
	}
	
	vector<shared_ptr<Word>> uandAwords(seqs_UandA[index].size());
	for (unsigned int i=0;i<seqs_UandA[index].size();++i)
	{
		uandAwords[i]=words[seqs_UandA[index][i]];
	}
	vector<vector<shared_ptr<Word>>> combinations_UandA;
	GetAllPossibleSequentialCombine(uandAwords,combinations_UandA);
	vector<vector<shared_ptr<Word>>> newCombinations;
	for (unsigned int i=0;i<combinations_UandA.size();++i)
	{
		if(combinations.empty())
		{
			vector<shared_ptr<Word>> aCombination;
			aCombination.insert(aCombination.end(),forwardWords.begin(),forwardWords.end());
			aCombination.insert(aCombination.end(),combinations_UandA[i].begin(),combinations_UandA[i].end());
			newCombinations.push_back(aCombination);
		}
		else
		{
			for (unsigned int j=0;j<combinations.size();++j)
			{
				vector<shared_ptr<Word>> aCombination;
				aCombination.insert(aCombination.end(),combinations[j].begin(),combinations[j].end());
				aCombination.insert(aCombination.end(),forwardWords.begin(),forwardWords.end());
				aCombination.insert(aCombination.end(),combinations_UandA[i].begin(),combinations_UandA[i].end());
				newCombinations.push_back(aCombination);
			}
		}
		
		
	}
	combinations=newCombinations;
	MergeCombination_UandA(words,seqs_UandA,index+1,combinations);

}

void SegmentMannersAccordingToUandA(const vector<shared_ptr<Word>>& words, vector<vector<shared_ptr<Word>>>& segmented)
{
	Mind::Cerebrum *brain=Mind::Cerebrum::Instance();

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

	if(seqs_UandA.empty())//one way
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
	vector<Character> raw=ConvertStringToCharacter(subsentence);
	pair<vector<Character>,vector<Character>> sen_punc =DataBaseProcessorTool::TrimEndPunctures(raw);
	vector<Character> raw_noPunc=sen_punc.first;
	vector<Character> punc=sen_punc.second;

	vector<CharacterProperty> vec_characterProperty;
	//find the candidate word of each character
	for (unsigned int i=0;i<raw_noPunc.size();++i)
	{
		Character chara=raw_noPunc[i];
		CharacterProperty characterProperty=GenerateCharacterProperty(chara,i,raw_noPunc);

		vec_characterProperty.push_back(characterProperty);
	}

	//pick the longest candidate word of each character to compose the sentence
	unsigned int index(0);
	vector<shared_ptr<Word>> initial_segmented;
	while(index<raw_noPunc.size())
	{
		Word candidate=*(vec_characterProperty[index].candidate.rbegin());
		int step=candidate.NumOfChara();
		initial_segmented.push_back(shared_ptr<Word>(new Word(candidate)));
		index+=step;
	}

	vector<vector<shared_ptr<Word>>> segmented;
	SegmentMannersAccordingToUandA(initial_segmented,segmented);

	vector<shared_ptr<Word>> punc_words=DataBaseProcessorTool::ConvertPuncturesToWords(punc);
	for (unsigned int i=0;i<segmented.size();++i)
	{
		vector<shared_ptr<Word>> seg_withPunc=segmented[i];
		seg_withPunc.insert(seg_withPunc.end(),punc_words.begin(),punc_words.end());
		
		_segmented.insert(make_pair(subsentence,shared_ptr<SegmentedSentence>(new SegmentedSentence(seg_withPunc))));
	}
}

WordSegmentator::CharacterProperty WordSegmentator::GenerateCharacterProperty(const Character& chara,const int myIndex,const vector<Character>& raw_noPunc)
{
	Mind::Cerebrum* brain=Mind::Cerebrum::Instance();

	CharacterProperty characterProperty;
	characterProperty.character=chara;
	characterProperty.index=myIndex;
	Word curWord(chara.GetString());
	if(brain->IsInMind(shared_ptr<Word>(new Word(curWord))))
	{
		curWord.KnowIt();
	}
	characterProperty.candidate.push_back(curWord);//当前的字一定是候选之一，否则如果没有找到新的候选，那么characterProperty.candidate就会是空容器，会引起后面的错误。

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
	vector<shared_ptr<Character>> ptrCharas=DataBaseProcessorTool::ConvertStringToCharacter(str);
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
	//每个元素表示一个子句子对应的所有分词方式.
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

	//每个元素表示完整句子的分词序列.
	vector<vector<shared_ptr<SegmentedSentence>>> segSequence= Math::GetAllCombinations<shared_ptr<SegmentedSentence>>::Get(subSentenSeg);
	//把<segSequence>的每个元素组合成一个完整的句子.
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


