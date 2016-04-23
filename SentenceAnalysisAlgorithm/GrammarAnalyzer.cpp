#include "StdAfx.h"
#include "GrammarAnalyzer.h"

#include "../CommonTools/CommonTranslateFunction.h"
#include "../CommonTools/CommonDeleteFunction.h"

#include "../DataCollection/Word.h"
#include "../DataCollection/Sentence.h"
#include "../DataCollection/GrammaPattern.h"
#include "../DataCollection/DataBaseProcessorTool.h"

#include "../Mind/Cerebrum.h"
#include "../Mind/CommonFunction.h"

#include <functional>

using namespace std;
using namespace DataCollection;
using namespace CommonTool;



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

WordRep GetWordRep(shared_ptr<Word> word)
{
	Mind::Cerebrum *brain=Mind::Cerebrum::Instance();
	WordRep wordrep;
	vector<shared_ptr<Word>> rep=brain->GetAllKindsofWord(word);
	if(rep.size()==0)
	{
		wordrep.Add(word);
		return wordrep;
	}


	for(unsigned int i=0;i<rep.size();++i)
	{
		wordrep.Add(rep[i]);
	}

	return wordrep;
}

int CheckUnknownWords(const vector<shared_ptr<Word>>& words)
{
	Mind::Cerebrum *brain=Mind::Cerebrum::Instance();

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


int CheckAmbiguousWords(const vector<WordRep>& words)
{
	int count(0);
	for (unsigned int i=0;i<words.size();++i)
	{
		if(words[i].Size()!=1) continue;//Contain only one ambiguous word.

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

void GetAllPossibleCombine(const int index, const vector<WordRep>& wordRepSet, vector<vector<shared_ptr<Word>>>& out)
{
	if(index<0) return;

	vector<shared_ptr<Word>> rep=wordRepSet[index].GetAllRep();
	vector<vector<shared_ptr<Word>>> newout;
	for (unsigned int i=0;i<rep.size();++i)
	{
		if(index!=wordRepSet.size()-1)//把rep[i]弹入<out>里每一句的结尾
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


void GetAllUnknownAmbiguousCombine(const vector<shared_ptr<Word>> words, const int index, vector<vector<shared_ptr<Word>>>& out)
{
	if(index<0) return;

	PartOfSpeech pos=words[index]->Type();
	if(pos==Unknown || pos==Ambiguous)
	{
		vector<vector<shared_ptr<Word>>> newout;
		for (unsigned int i=0;i<DataCollection::NUM_PARTOFSPEECH;++i)
		{
			shared_ptr<Word> newword=DataBaseProcessorTool::GetParticularWord(words[index]->GetString(),PartOfSpeech(i));
			if(index!=words.size()-1)
			{
				vector<vector<shared_ptr<Word>>> tmpout(out.size());
				transform(out.begin(),out.end(),tmpout.begin(),pushfrontval(newword));
				newout.insert(newout.end(),tmpout.begin(),tmpout.end());
			}
			else
			{
				vector<shared_ptr<Word>> oneword;
				oneword.push_back(newword);
				newout.push_back(oneword);
			}
		}
		out=newout;
	}
	else
	{
		if(!out.empty())
		{
			vector<vector<shared_ptr<Word>>> newout(out.size());
			transform(out.begin(),out.end(),newout.begin(),pushfrontval(words[index]));
			out=newout;
		}
		else
		{
			vector<shared_ptr<Word>> oneword;
			oneword.push_back(words[index]);
			out.push_back(oneword);
		}
	}

	GetAllUnknownAmbiguousCombine(words,index-1,out);
	
}

vector<vector<shared_ptr<Word>>> SpanUnknownAndAmbiguousToEveryPOS(const vector<shared_ptr<Word>> words)
{
	vector<int> unknown_ambiguous_vec;
	for (unsigned int i=0;i<words.size();++i)
	{
		if(words[i]->Type()==Unknown ||words[i]->Type()==Ambiguous )
		{
			unknown_ambiguous_vec.push_back(i);
		}
	}

	vector<vector<shared_ptr<Word>>> res;
	if(unknown_ambiguous_vec.empty()) 
	{
		res.push_back(words);
		return res;
	}

	GetAllUnknownAmbiguousCombine(words,words.size()-1,res);
	return res;
}


void SelectOptimalGrammarPattern(const vector<vector<shared_ptr<Word>>>& combination, vector<shared_ptr<Word>>& optimal)
{
	Mind::Cerebrum *brain=Mind::Cerebrum::Instance();

	//目标值，等于GrammarPattern的总频率乘以其局域的概率值.
	double maxValueFun(-1);
	for (unsigned int i=0;i<combination.size();++i)
	{
		GrammarPattern pattern=DataBaseProcessorTool::ConvertToPattern(combination[i]);
		vector<GrammarPattern> matchedPattern=brain->ContainSubsequence(pattern);
		if(matchedPattern.empty()) continue;;

		int freq_sum(0);
		for (unsigned int j=0;j<matchedPattern.size();++j)
		{
			freq_sum+=brain->GetFreqencyofPattern(matchedPattern[j]);
		}

		double value=freq_sum*Mind::CommonFunction::ComputeP_GrammarLocalAnalysis(pattern);

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
	int unknown_ambiguous_Limit=2;
	bool containUnknownWord(false);
	bool containAmbiguousWord(false);

	vector<vector<shared_ptr<Word>>> candidates;//存入所有的可能性，再选择最优的。

	for (unsigned int i=0;i<_segments.size();++i)
	{
		vector<shared_ptr<Word>> segmented=_segments[i]->Get();
		pair<vector<shared_ptr<Word>>,vector<shared_ptr<Word>>> sen_punc =DataBaseProcessorTool::TrimEndPunctures(segmented);
		vector<shared_ptr<Word>> segmented_withNoPunc=sen_punc.first;
		vector<shared_ptr<Word>> punc=sen_punc.second;

		//Get all kinds of part of speech of each word
		vector<WordRep> segmente_allRep(segmented_withNoPunc.size());
		for (unsigned int j=0;j<segmented_withNoPunc.size();++j)
		{
			segmente_allRep[j]=GetWordRep(segmented_withNoPunc[j]);
		}

		int count_unknown=CheckUnknownWords(segmented_withNoPunc);
		if(count_unknown>0)
		{
			containUnknownWord=true;
		}
		if(count_unknown>unknown_ambiguous_Limit)
		{
			return;
		}

		int count_ambiguous=CheckAmbiguousWords(segmente_allRep);
		if(count_ambiguous>0)
		{
			containAmbiguousWord=true;
		}
		if(count_ambiguous+count_unknown>unknown_ambiguous_Limit)
		{
			return;
		}

		//Get all combinations according to  POS of each word.
		vector<vector<shared_ptr<Word>>> possi_Combine;
		GetAllPossibleCombine(segmente_allRep.size()-1,segmente_allRep,possi_Combine);


		//Compute the count of pattern match of each combination.
		vector<shared_ptr<Word>> optimal;
		if(containUnknownWord || containAmbiguousWord)
		{
			for (unsigned int j=0;j<possi_Combine.size();++j)
			{
				vector<vector<shared_ptr<Word>>> spannedCombination=SpanUnknownAndAmbiguousToEveryPOS(possi_Combine[j]);//Let the unknown word span over every POS.
				SelectOptimalGrammarPattern(spannedCombination,optimal);
			}
		}
		else
		{
			SelectOptimalGrammarPattern(possi_Combine,optimal);
		}

		optimal.insert(optimal.end(),punc.begin(),punc.end());
		candidates.push_back(optimal);
		//_raw_sen->AddGrammard(optimal);
	}
	

	vector<shared_ptr<Word>> mostOptimal;
	SelectOptimalGrammarPattern(candidates,mostOptimal);
	//当前只处理只有一个间断标点的短句子.
	_raw_sen->SetGrammard(mostOptimal);
}



void GrammarAnalyzer::BuildGrammarAssociationOfWords()
{
	Mind::Cerebrum *brain=Mind::Cerebrum::Instance();

	vector<shared_ptr<Word>> grammard=_raw_sen->GetGrammard();
	if(grammard.empty())
	{
		return;
	}

	GrammarPattern pattern=DataBaseProcessorTool::ConvertToPattern(grammard);
	vector<GrammarPattern> matchedPattern=brain->ContainSubsequence(pattern);
	_raw_sen->BuildGrammarAssociation(matchedPattern);
}

