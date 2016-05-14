#include "StdAfx.h"
#include "DataBaseProcessorTool.h"
#include "Character.h"
#include "Word.h"
#include "GrammaPattern.h"
#include "Punctures.h"

using namespace std;

namespace DataCollection
{
	shared_ptr<Punctures> DataBaseProcessorTool::_punctures(new Punctures());

	DataCollection::DataBaseProcessorTool::DataBaseProcessorTool(void)
	{
	}


	DataCollection::DataBaseProcessorTool::~DataBaseProcessorTool(void)
	{
	}

	bool DataCollection::DataBaseProcessorTool::IsPuncEndofSentence( shared_ptr<Character> val )
	{
		return _punctures->IsPuncEndofSentence(val);
	}

	bool DataCollection::DataBaseProcessorTool::IsPuncRightside( shared_ptr<Character> val )
	{
		return _punctures->IsPuncRightside(val);
	}

	std::vector<shared_ptr<Character>> DataCollection::DataBaseProcessorTool::ConvertStringToCharacter( std::string str)
	{
		assert(str.size()%2==0);
		vector<shared_ptr<Character>> charas;
		for (string::iterator it=str.begin();it!=str.end();it+=2)
		{
			string temp;
			temp.push_back(*it);
			temp.push_back(*(it+1));
			charas.push_back(shared_ptr<Character>(new Character(temp)));
		}
		return charas;
	}

	pair<vector<shared_ptr<Character>>,vector<shared_ptr<Character>>> DataBaseProcessorTool::TrimEndPunctures( const vector<shared_ptr<Character>>& raw )
	{
		vector<shared_ptr<Character>>::const_iterator chara_it=find_if(raw.begin(),raw.end(),IsPuncEndofSentence);
		int index=distance(raw.begin(),chara_it);
		vector<shared_ptr<Character>> sentenceWithNoPunctures;
		for (unsigned int i=0;i<(size_t)index;++i)
		{
			sentenceWithNoPunctures.push_back(raw[i]);
		}
		vector<shared_ptr<Character>> endPunctures;
		for (unsigned int i=index;i<raw.size();++i)
		{
			endPunctures.push_back(raw[i]);
		}

		return make_pair(sentenceWithNoPunctures,endPunctures);
	}

	pair<vector<Character>,vector<Character>> DataBaseProcessorTool::TrimEndPunctures( const vector<Character>& raw )
	{
		vector<shared_ptr<Character>> sptr_raw;
		for (unsigned int i=0;i<raw.size();++i)
		{
			sptr_raw.push_back(shared_ptr<Character>(new Character(raw[i])));
		}
		pair<vector<shared_ptr<Character>>,vector<shared_ptr<Character>>> pair= TrimEndPunctures(sptr_raw);
		vector<Character> sen;
		for (unsigned int i=0;i<pair.first.size();++i)
		{
			sen.push_back(*pair.first[i]);
		}
		vector<Character> punc;
		for (unsigned int i=0;i<pair.second.size();++i)
		{
			punc.push_back(*pair.second[i]);
		}

		return make_pair(sen,punc);
	}


	vector<shared_ptr<Word>> DataBaseProcessorTool::ConvertPuncturesToWords( const vector<Character>& puncs )
	{
		vector<shared_ptr<Word>> res;
		res.reserve(puncs.size());
		for (unsigned int i=0;i<puncs.size();++i)
		{
			string puncStr=puncs[i].GetString();
			shared_ptr<Character> chara(new Character(puncStr));
			assert(IsPuncEndofSentence(chara) || IsPuncRightside(chara));
			res.push_back(shared_ptr<puncture>(new puncture(puncs[i].GetString())));
		}

		return res;
	}

	pair<vector<shared_ptr<Word>>,vector<shared_ptr<Word>>> DataBaseProcessorTool::TrimEndPunctures( const vector<shared_ptr<Word>>& raw )
	{
		unsigned int index=raw.size();
		for (unsigned int i=0;i<raw.size();++i)
		{
			shared_ptr<Character> chara(new Character(raw[i]->GetString()));
			if(IsPuncEndofSentence(chara))
			{
				index=i;
				break;
			}
		}

		vector<shared_ptr<Word>> sentenceWithNoPunctures;
		for (unsigned int i=0;i<index;++i)
		{
			sentenceWithNoPunctures.push_back(raw[i]);
		}
		vector<shared_ptr<Word>> endPunctures;
		for (unsigned int i=index;i<raw.size();++i)
		{
			endPunctures.push_back(raw[i]);
		}

		return make_pair(sentenceWithNoPunctures,endPunctures);
	}

	pair<vector<Word>,vector<Word>> DataBaseProcessorTool::TrimEndPunctures( const vector<Word>& raw )
	{
		vector<shared_ptr<Word>> sptr_raw;
		for (unsigned int i=0;i<raw.size();++i)
		{
			sptr_raw.push_back(shared_ptr<Word>(new Word(raw[i])));
		}
		pair<vector<shared_ptr<Word>>,vector<shared_ptr<Word>>> pair= TrimEndPunctures(sptr_raw);
		vector<Word> sen;
		for (unsigned int i=0;i<pair.first.size();++i)
		{
			sen.push_back(*pair.first[i]);
		}
		vector<Word> punc;
		for (unsigned int i=0;i<pair.second.size();++i)
		{
			punc.push_back(*pair.second[i]);
		}

		return make_pair(sen,punc);
	}

	std::string DataBaseProcessorTool::ConvertCharacterToString( std::vector<shared_ptr<Character>> charas )
	{
		string res="";
		for (unsigned int i=0;i<charas.size();++i)
		{
			res+=charas[i]->GetString();
		}

		return res;
	}

	DataCollection::GrammarPattern DataBaseProcessorTool::ConvertToPattern( const vector<shared_ptr<DataCollection::Word>> words )
	{
		vector<PartOfSpeech> ps(words.size());
		for (unsigned int i=0;i<words.size();++i)
		{
			ps[i]=words[i]->Type();
		}

		return GrammarPattern(ps);
	}

	shared_ptr<DataCollection::Word> DataBaseProcessorTool::GetParticularWord( const std::string str, const DataCollection::PartOfSpeech partofspeech )
	{
		switch(partofspeech)
		{
		case Noun:
			return shared_ptr<Word>(new noun(str)) ;
		case Verb:
			return shared_ptr<Word>(new verb(str));
		case Adjective:
			return shared_ptr<Word>(new adjective(str));
		case Numeral:
			return shared_ptr<Word>(new numeral(str));
		case Quantifier:
			return shared_ptr<Word>(new quantifier(str));
		case Pronoun:
			return shared_ptr<Word>(new pronoun(str));
		case Adverb:
			return shared_ptr<Word>(new adverb(str));
		case Preposition:
			return shared_ptr<Word>(new preposition(str));
		case Conjunction:
			return shared_ptr<Word>(new conjunction(str));
		case Auxiliary:
			return shared_ptr<Word>(new auxiliary(str));
		case Onomatopoeia:
			return shared_ptr<Word>(new onomatopoeia(str));
		case Interjection:
			return shared_ptr<Word>(new interjection(str));
		case Puncture:
			return shared_ptr<Word>(new puncture(str));
		case Unknown:
			return NULL;
		default:
			break;
		}

		return NULL;
	}

	int DataBaseProcessorTool::IndexOf( const vector<shared_ptr<Word>>& words,const shared_ptr<Word> word )
	{
		class IsSameWith
		{
			shared_ptr<Word> _val;
		public:
			IsSameWith(const shared_ptr<Word> val):_val(val){};
			~IsSameWith(){}

			bool operator()(const shared_ptr<Word> val)
			{
				if(_val->IsSame(val))
				{
					return true;
				}
				else
					return false;
			}
		};

		vector<shared_ptr<Word>>::const_iterator iter=find_if(words.begin(),words.end(),IsSameWith(word));
		if(iter==words.end())
		{
			return -1;
		}
		else
		{
			return distance(words.begin(),iter);
		}
	}


	vector<shared_ptr<Word>> DataBaseProcessorTool::RemovePuncs( const vector<shared_ptr<Word>>& words )
	{
		vector<shared_ptr<Word>> res;
		remove_copy_if(words.begin(),words.end(),back_inserter(res),DataBaseProcessorTool::IsPuncture);
		return res;
	}

	bool DataBaseProcessorTool::IsPuncture( const shared_ptr<Word> word )
	{
		if(word->Type()==Puncture)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool DataBaseProcessorTool::SameGrammarPattern( const GrammarPattern& left,const GrammarPattern& right )
	{
		return left.IsSameWith(right);
	}

	std::string DataBaseProcessorTool::ConvertWordsToString( const vector<shared_ptr<Word>> words )
	{
		string res="";
		for (unsigned int i=0;i<words.size();++i)
		{
			res+=words[i]->GetString();
		}

		return res;
	}

}

