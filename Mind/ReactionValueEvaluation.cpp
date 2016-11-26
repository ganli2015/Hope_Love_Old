#include "stdafx.h"
#include "ReactionValueEvaluation.h"
#include "FilePath.h"
#include <functional>

#include "../CommonTools/ConfigureInfoManager.h"
#include "../CommonTools/GeneralFunctor.h"

#include "../DataCollection/Sentence.h"
#include "../DataCollection/Word.h"

#include "../SentenceAnalysisAlgorithm/Punctuator.h"

namespace Mind
{
	ReactionValueEvaluation::ReactionValueEvaluation():_commonWordsFilepath ( GetHopeLoveMindPath() + "现代汉语常用词汇表.txt"),
		_commonCharaFilepath(GetHopeLoveMindPath() + "常用汉字表.txt"),
		_conversationFilepath(GetHopeLoveMindPath() + "Conversation Sample.txt"),
		_commonWordDistriFilepath(GetHopeLoveMindPath() + "Distribution of Common Words.txt"),
		_commonWordIDFFilepath(GetHopeLoveMindPath()+"IDF of Common Words.txt"),
		_conversationPairsFilepath(GetHopeLoveMindPath() + "Conversation Pairs Sample.txt")
	{
		CFG_SECTION(GENERATE_IDF_OF_COMMON_WORDS)
		{
			GenerateIDFOfCommonWords();
		}

		//Read IDF from txt file.
		ReadIDFOfCommonWords();

		ReadConversationPairs();
		RemoveInvalidConversationPairs(_conversationPairs);
	}


	ReactionValueEvaluation::~ReactionValueEvaluation()
	{
	}

	void ReactionValueEvaluation::GenerateIDFOfCommonWords()
	{
		ReadConversation();

		//Generate distribution of common words from conversation samples.
		CFG_SECTION(GENERATE_DISTRIBUTION_COMMON_WORDS)
		{
			ReadCommonWords();
			OutputSmoothedDistributionOfCommonWords();
		};

		//Read distribution of common words from txt.
		_commonWords = ReadCommonWordInfo();
		ComputeIDF(_commonWords);
		OutputIDFOfCommonWords(_commonWords);
	}

	void ReactionValueEvaluation::ReadIDFOfCommonWords()
	{
		_commonWords.clear();

		ifstream in(_commonWordIDFFilepath);
		while (!in.eof())
		{
			string word;
			double IDF;
			int count;

			in >> word;
			in >> IDF;
			in >> count;

			CommonWordInfo wordInfo;
			wordInfo.word = word;
			wordInfo.IDF = IDF;
			wordInfo.count = count;
			_commonWords.push_back(wordInfo);
		}
		in.close();
	}

	void ReactionValueEvaluation::ReadCommonWords()
	{
		_commonWords.clear();

		//Read words.
		ifstream in(_commonWordsFilepath);
		while (!in.eof())
		{
			string word;
			in >> word;

			CommonWordInfo wordInfo;
			wordInfo.word = word;
			_commonWords.push_back(wordInfo);
		}
		in.close();

		//Read characters.
		in.open(_commonCharaFilepath);
		while (!in.eof())
		{
			string chara;
			in >> chara;

			CommonWordInfo wordInfo;
			wordInfo.word = chara;
			_commonWords.push_back(wordInfo);
		}
		in.close();
	}

	void ReactionValueEvaluation::ReadConversation()
	{
		_conversation.clear();

		ifstream in(_conversationFilepath);
		string line = "";
		while (getline(in, line))
		{		
			//Drop sentences that has Odd size as Chinese characters and punctuations are of Even size.
			//Odd-size sentences will cause difficulty in following operations.
			//Besides, drop sentences that contain positive chars as Chinese characters are of negtive chars.
			if (IsValidSentence(line))
			{
				_conversation.push_back(line);
			}

		}
		in.close();
	}

	void ReactionValueEvaluation::ReadConversationPairs()
	{
		_conversationPairs.clear();

		ifstream in(_conversationPairsFilepath);
		
		string first, second;
		while (getline(in, first) && getline(in, second))
		{
			ConversationPair pair;
			pair.first = first;
			pair.second = second;

			_conversationPairs.push_back(pair);
		}

		in.close();
	}

	void ReactionValueEvaluation::RemoveInvalidConversationPairs(vector<ConversationPair>& conversationPairs) const
	{
		for (vector<ConversationPair>::iterator it=conversationPairs.begin();it!=conversationPairs.end();)
		{
			if((!IsValidSentence(it->first)) || (!IsValidSentence(it->second)))
			{
				it = conversationPairs.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	void ReactionValueEvaluation::OutputSmoothedDistributionOfCommonWords() const
	{
		ofstream out(_commonWordDistriFilepath);

		for (unsigned int i=0;i<_commonWords.size();++i)
		{
			int count = CountInConversation(_commonWords[i].word);

			//Smoothing process.
			count += 1;

			out << _commonWords[i].word << " " << count << endl;
		}
	}

	int ReactionValueEvaluation::CountInConversation(const string word) const
	{
		class WordExist
		{
			string _word;
			int _freq;
		public:
			WordExist(const string word) :_word(word), _freq(0) {};
			~WordExist() {};

			void operator()(const string& senStr)
			{
				//Find index of <_word>.
				//The index must be an Even number as Chinese characters are of Even size,
				//so start of Chinese characters are Even index.
				size_t findIndex = senStr.find(_word);

				while (findIndex!= string::npos && findIndex%2!=0)
				{
					string remainStr(senStr.begin() + findIndex + 1, senStr.end());
					size_t remainFindIndex = remainStr.find(_word);
					if (remainFindIndex == string::npos)
					{
						findIndex= string::npos;
					}
					else
						findIndex = remainFindIndex + findIndex + 1;
				}

				if (findIndex != string::npos)
				{
					++_freq;
				}
			}
			int GetFrequency() const { return _freq; }
		};

		WordExist wordExist(word);
		wordExist = for_each(_conversation.begin(), _conversation.end(), wordExist);

		return wordExist.GetFrequency();
	}

	std::vector<Mind::ReactionValueEvaluation::CommonWordInfo> ReactionValueEvaluation::ReadCommonWordInfo() const
	{
		vector<CommonWordInfo> res;
		ifstream in(_commonWordDistriFilepath);
		while (!in.eof())
		{
			string word;
			int count;
			in >> word;
			in >> count;

			if (res.size() == _commonWords.size()-2)
			{
				assert("");
			}


			CommonWordInfo info;
			info.word = word;
			info.count = count;
			res.push_back(info);
		}

		in.close();

		return res;
	}


	void ReactionValueEvaluation::ComputeIDF(vector<CommonWordInfo>& wordsInfo) const
	{
		//Functor to compute IDF.
		CREATE_FUNCTOR_I(IDF, int, CommonWordInfo,
			input.IDF=log((double)_init / input.count) / log(2.);
		);

		int conversationLineCount = _conversation.size();
		for_each(wordsInfo.begin(), wordsInfo.end(), IDF(conversationLineCount));
	}

	void ReactionValueEvaluation::OutputIDFOfCommonWords(const vector<CommonWordInfo>& commonWords) const
	{
		ofstream out(_commonWordIDFFilepath);
		out.precision(10);

		for (unsigned int i=0;i<commonWords.size();++i)
		{
			out << commonWords[i].word << " " << commonWords[i].IDF<<" "<<commonWords[i].count;

			if(i!=commonWords.size()-1)
			{
				out << endl;
			}
		}

		out.close();
	}

	bool ReactionValueEvaluation::IsValidSentence(const string line) const
	{
		return line.size() % 2 == 0 && all_of(line.begin(), line.end(), bind2nd(less<int>(), 0));
	}

}

