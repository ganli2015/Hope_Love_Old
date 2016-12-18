#include "StdAfx.h"
#include "GrammarAnalyzer.h"

#include "../CommonTools/CommonTranslateFunction.h"
#include "../CommonTools/CommonDeleteFunction.h"

#include "../DataCollection/Word.h"
#include "../DataCollection/Sentence.h"
#include "../DataCollection/GrammaPattern.h"
#include "../DataCollection/LanguageFunc.h"

#include "../Mind/CommonFunction.h"

#include "../MindInterface/iCerebrum.h"

#include <functional>

using namespace std;
using namespace DataCollection;
using namespace CommonTool;


///Contain several possible POS of a word.
class WordRep
{
	std::vector<shared_ptr<DataCollection::Word>> _rep;
public:
	WordRep(void){};
	~WordRep(){};

	void Add(shared_ptr<DataCollection::Word> word)
	{
		_rep.push_back(word);
	};
	int Size() const {return _rep.size();}
	vector<shared_ptr<Word>> GetAllRep() const 
	{
		return _rep;
	}
};


GrammarAnalyzer::GrammarAnalyzer(void)
{
}


GrammarAnalyzer::~GrammarAnalyzer(void)
{
}

GrammarAnalyzer::GrammarAnalyzer( shared_ptr<DataCollection::Sentence> sen)
{
	_raw_sen=sen;
}

WordRep GrammarAnalyzer::GetWordRep(shared_ptr<Word> word)
{
	Mind::iCerebrum *brain=Mind::iCerebrum::Instance();
	WordRep wordrep;
	vector<shared_ptr<Word>> rep=brain->GetAllKindsofWord(word);
	if(rep.size()==0)
	{
		//If the word is unknows, I still append it to the result for following convenience.
		wordrep.Add(word);
		return wordrep;
	}


	for(unsigned int i=0;i<rep.size();++i)
	{
		wordrep.Add(rep[i]);
	}

	return wordrep;
}

int GrammarAnalyzer::CheckUnknownWords(const vector<shared_ptr<Word>>& words)
{
	Mind::iCerebrum *brain=Mind::iCerebrum::Instance();

	int count(0);
	for (unsigned int i=0;i<words.size();++i)
	{
		if(!brain->IsInMind(words[i]))
		{
			count++;
		}
	}
	return count;
}


int GrammarAnalyzer::CheckAmbiguousWords(const vector<WordRep>& words)
{
	int count(0);
	for (unsigned int i=0;i<words.size();++i)
	{
		///If it is an ambiguous word , its WordRep must contain only one element.
		if(words[i].Size()!=1) continue;

		if(words[i].GetAllRep().at(0)->Type()==Ambiguous)
		{
			count++;
		}
	}
	return count;
}

class pushfrontval
{
	shared_ptr<Word> _val;

public:
	pushfrontval(shared_ptr<Word> val) {_val=val;}
	~pushfrontval(){}

	vector<shared_ptr<Word>> operator()(vector<shared_ptr<Word>> vec)
	{
		vector<shared_ptr<Word>> newvec;
		newvec.push_back(_val);
		newvec.insert(newvec.end(),vec.begin(),vec.end());
		return newvec;
	}
};

void GrammarAnalyzer::GetAllPossibleCombine(const int index, const vector<WordRep>& wordRepSet, vector<vector<shared_ptr<Word>>>& out)
{
	if(index<0) return;

	vector<shared_ptr<Word>> rep=wordRepSet[index].GetAllRep();
	vector<vector<shared_ptr<Word>>> newout;
	//Go through each POS of the current word.
	//For each POS, connect the word with the old combination.
	for (unsigned int i=0;i<rep.size();++i)
	{
		if(index!=wordRepSet.size()-1)
		{
			vector<vector<shared_ptr<Word>>> tmpCombine(out.size());
			transform(out.begin(),out.end(),tmpCombine.begin(),pushfrontval(rep[i]));
			newout.insert(newout.end(),tmpCombine.begin(),tmpCombine.end());
		}
		else//if the size of out equals to zero, push every element of <rep> to out.
		{
			vector<shared_ptr<Word>> oneword;
			oneword.push_back(rep[i]);
			newout.push_back(oneword);
		}
		
	}
	out=newout;
	GetAllPossibleCombine(index-1,wordRepSet,out);
}

vector<vector<shared_ptr<Word>>> GrammarAnalyzer::SpanUandAWords(const vector<shared_ptr<Word>>& words, const int index,
	const vector<vector<shared_ptr<Word>>>& latterCombinations)
{
	vector<vector<shared_ptr<Word>>> newout;
	for (unsigned int i = 0; i < DataCollection::NUM_PARTOFSPEECH; ++i)
	{
		shared_ptr<Word> newword = LanguageFunc::GetParticularWord(words[index]->GetString(), PartOfSpeech(i));
		if (index != words.size() - 1)
		{
			vector<vector<shared_ptr<Word>>> tmpout(latterCombinations.size());
			transform(latterCombinations.begin(), latterCombinations.end(), tmpout.begin(), pushfrontval(newword));
			newout.insert(newout.end(), tmpout.begin(), tmpout.end());
		}
		else
		{
			//As usual ,the last word does not connect to the latter combinations 
			//as it is the start of iterations.
			vector<shared_ptr<Word>> oneword;
			oneword.push_back(newword);
			newout.push_back(oneword);
		}
	}

	return newout;
}

void GrammarAnalyzer::SpanNonUandAWords(const vector<shared_ptr<Word>> words, const int index,vector<vector<shared_ptr<Word>>>& out)
{
	if (!out.empty())
	{
		vector<vector<shared_ptr<Word>>> newout(out.size());
		transform(out.begin(), out.end(), newout.begin(), pushfrontval(words[index]));
		out = newout;
	}
	else
	{
		vector<shared_ptr<Word>> oneword;
		oneword.push_back(words[index]);
		out.push_back(oneword);
	}
}

void GrammarAnalyzer::GetAllUnknownAmbiguousCombine(const vector<shared_ptr<Word>> words, const int index, vector<vector<shared_ptr<Word>>>& out)
{
	if(index<0) return;

	PartOfSpeech pos=words[index]->Type();
	if(pos==Unknown || pos==Ambiguous)
	{
		//For U_A word, span the word from Noun to Interjection and generate all combinations with other words.
		vector<vector<shared_ptr<Word>>> newout = SpanUandAWords(words, index, out);
		out=newout;
	}
	else
	{
		//For non U_A word, simply connect it to combinations.
		SpanNonUandAWords(words, index, out);
	}

	GetAllUnknownAmbiguousCombine(words,index-1,out);
	
}

vector<vector<shared_ptr<Word>>> GrammarAnalyzer::SpanUnknownAndAmbiguousToEveryPOS(const vector<shared_ptr<Word>> words)
{
	vector<int> unknown_ambiguous_vec;
	for (unsigned int i=0;i<words.size();++i)
	{
		if(words[i]->Type()==Unknown ||words[i]->Type()==Ambiguous )
		{
			unknown_ambiguous_vec.push_back(i);
		}
	}

	//If there is no U_A word, I do not need to span.
	vector<vector<shared_ptr<Word>>> res;
	if(unknown_ambiguous_vec.empty()) 
	{
		res.push_back(words);
		return res;
	}

	//The action of span starts from the end of the sentence.
	//The U_A word will span to every POS and other words simply connect.
	GetAllUnknownAmbiguousCombine(words,words.size()-1,res);
	return res;
}


void GrammarAnalyzer::SelectOptimalGrammarPattern(const vector<vector<shared_ptr<Word>>>& combination, vector<shared_ptr<Word>>& optimal)
{
	Mind::iCerebrum *brain=Mind::iCerebrum::Instance();

	//The object value to select the most optimal combination.
	//The value equals to sum of frequencies of incorporated grammar patterns as well as local grammar confidence.
	//It means that the optimal combinatin must satisfy grammar statistic information.
	double maxValueFun(-1);
	for (unsigned int i=0;i<combination.size();++i)
	{
		GrammarPattern pattern=LanguageFunc::ConvertToPattern(combination[i]);

		double value = brain->ComputePossibility(pattern);

		if(value>maxValueFun)
		{
			maxValueFun=value;
			optimal=combination[i];
		}
	}
}


bool GrammarAnalyzer::Analyze()
{
	OptimizePOSofWords();
	BuildGrammarAssociationOfWords();

	return true;
}

void GrammarAnalyzer::OptimizePOSofWords()
{
	vector<vector<shared_ptr<Word>>> candidates;

	//Go through all segmented sentences and find the most optimal.
	//There will be only one sentence survive!
	for (unsigned int i=0;i<_segments.size();++i)
	{
		vector<shared_ptr<Word>> segmented = _segments[i]->Get();
		vector<shared_ptr<Word>> optimal;
		AnalyzeResult result = AnalyzeEachSegmented(segmented, optimal);

		candidates.push_back(optimal);
		//_raw_sen->AddGrammard(optimal);
	}
	
	//After go through segmented sentences, there are several candidates for final sentence.
	//And now I continue to select one of them for convenience of following computation.
	vector<shared_ptr<Word>> mostOptimal;
	SelectOptimalGrammarPattern(candidates,mostOptimal);
	_raw_sen->SetGrammard(mostOptimal);
}

vector<WordRep> GrammarAnalyzer::SearchAllWordRep(const vector<shared_ptr<Word>>& segmented_withNoPunc)
{
	//Search all words in Cerebrum and
	//find all known POS of each word for every possible combination.
	vector<WordRep> segmente_allRep(segmented_withNoPunc.size());
	for (unsigned int j = 0; j < segmented_withNoPunc.size(); ++j)
	{
		segmente_allRep[j] = GetWordRep(segmented_withNoPunc[j]);
	}

	return segmente_allRep;
}

GrammarAnalyzer::AnalyzeResult GrammarAnalyzer::AnalyzeEachSegmented(const vector<shared_ptr<Word>>& segmented, vector<shared_ptr<Word>> &optimal)
{
	int unknown_ambiguous_Limit = 2;
	bool containUnknownWord(false);
	bool containAmbiguousWord(false);

	//Separate words with punctures as punctures will interfere grammar analysis.
// 	pair<vector<shared_ptr<Word>>, vector<shared_ptr<Word>>> sen_punc = LanguageFunc::TrimEndPunctures(segmented);
// 	vector<shared_ptr<Word>> segmented_withNoPunc = sen_punc.first;
// 	vector<shared_ptr<Word>> punc = sen_punc.second;

	vector<WordRep> segmente_allRep = SearchAllWordRep(segmented);

	//If the number of unknown and ambiguous words exceed the limit, then it is hard and inaccurate to analyze.
	int count_unknown = CheckUnknownWords(segmented);
	if (count_unknown > 0)
	{
		containUnknownWord = true;
	}
	if (count_unknown > unknown_ambiguous_Limit)
	{
		return TooManyUknownWords;
	}
	int count_ambiguous = CheckAmbiguousWords(segmente_allRep);
	if (count_ambiguous > 0)
	{
		containAmbiguousWord = true;
	}
	if (count_ambiguous + count_unknown > unknown_ambiguous_Limit)
	{
		return TooManyAmbiguousWords;
	}

	//Get all combinations according to  POS of each word.
	//Each word has several POS and collection all combinations.
	vector<vector<shared_ptr<Word>>> possi_Combine;
	GetAllPossibleCombine(segmente_allRep.size() - 1, segmente_allRep, possi_Combine);

	//Compute the count of pattern match of each combination.
	if (containUnknownWord || containAmbiguousWord)
	{
		vector<vector<shared_ptr<Word>>> allCombinations;

		//For each U_A word, I consider its POS arbitrary and go through every POS.
		for (unsigned int j = 0; j < possi_Combine.size(); ++j)
		{
			vector<vector<shared_ptr<Word>>> spannedCombination = SpanUnknownAndAmbiguousToEveryPOS(possi_Combine[j]);//Let the unknown word span over every POS.
			allCombinations.insert(allCombinations.end(), spannedCombination.begin(), spannedCombination.end());
		}

		SelectOptimalGrammarPattern(allCombinations, optimal);
	}
	else
	{
		SelectOptimalGrammarPattern(possi_Combine, optimal);
	}

	//Convert punctuations from Type word to Type punctuation.
// 	for (unsigned int i=0;i<punc.size();++i)
// 	{
// 		punc[i] = shared_ptr<puncture>(new puncture(punc[i]->GetString()));
// 	}
// 	optimal.insert(optimal.end(), punc.begin(), punc.end());

	return Fine;
}

void GrammarAnalyzer::BuildGrammarAssociationOfWords()
{
	Mind::iCerebrum *brain=Mind::iCerebrum::Instance();

	vector<shared_ptr<Word>> grammard=_raw_sen->GetGrammard();
	if(grammard.empty())
	{
		return;
	}

	//Build grammar association according to grammar patterns the sentence contains.
	//Grammar patterns reflect the internal structure of the sentence and
	//They provide informatin about which words are related.
	GrammarPattern pattern=LanguageFunc::ConvertToPattern(grammard);
	vector<GrammarPattern> matchedPattern=brain->ContainSubsequence(pattern);
	_raw_sen->BuildGrammarAssociation(matchedPattern);
}

