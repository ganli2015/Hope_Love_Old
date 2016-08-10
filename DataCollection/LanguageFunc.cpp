#include "StdAfx.h"
#include "LanguageFunc.h"
#include "Character.h"
#include "Word.h"
#include "GrammaPattern.h"
#include "Punctuations.h"

#include "../CommonTools/GeneralFunctor.h"
#include "../CommonTools/assertions.h"

using namespace std;

namespace DataCollection
{
	shared_ptr<Punctuations> LanguageFunc::_punctures(new Punctuations());

	DataCollection::LanguageFunc::LanguageFunc(void)
	{
	}


	DataCollection::LanguageFunc::~LanguageFunc(void)
	{
	}

	bool DataCollection::LanguageFunc::IsPuncEndofSentence( shared_ptr<Character> val )
	{
		return _punctures->IsPuncEndofSentence(val);
	}

	bool DataCollection::LanguageFunc::IsPuncRightside( shared_ptr<Character> val )
	{
		return _punctures->IsPuncRightside(val);
	}

	std::vector<shared_ptr<Character>> DataCollection::LanguageFunc::ConvertStringToCharacter( std::string str)
	{
		//Assume the input <str> are all Chinese characters.
		//Then convert two by two.
		//assert(str.size()%2==0);
		Check(str.size() % 2 == 0);

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

	pair<vector<shared_ptr<Character>>,vector<shared_ptr<Character>>> LanguageFunc::TrimEndPunctures( const vector<shared_ptr<Character>>& raw )
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

	pair<vector<Character>,vector<Character>> LanguageFunc::TrimEndPunctures( const vector<Character>& raw )
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


	vector<shared_ptr<Word>> LanguageFunc::ConvertPuncturesToWords( const vector<Character>& puncs )
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

	pair<vector<shared_ptr<Word>>,vector<shared_ptr<Word>>> LanguageFunc::TrimEndPunctures( const vector<shared_ptr<Word>>& raw )
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

	pair<vector<Word>,vector<Word>> LanguageFunc::TrimEndPunctures( const vector<Word>& raw )
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

	std::string LanguageFunc::ConvertCharacterToString( std::vector<shared_ptr<Character>> charas )
	{
		string res="";
		for (unsigned int i=0;i<charas.size();++i)
		{
			res+=charas[i]->GetString();
		}

		return res;
	}

	DataCollection::GrammarPattern LanguageFunc::ConvertToPattern( const vector<shared_ptr<DataCollection::Word>> words )
	{
		vector<PartOfSpeech> ps(words.size());
		for (unsigned int i=0;i<words.size();++i)
		{
			ps[i]=words[i]->Type();
		}

		return GrammarPattern(ps);
	}

	DataCollection::GrammarPattern LanguageFunc::ConvertToPattern(const vector<int> posInt)
	{
		CREATE_FUNCTOR_R(ToPOS, int, PartOfSpeech,
			return (PartOfSpeech)input;
		);

		vector<PartOfSpeech> pos(posInt.size());
		transform(posInt.begin(), posInt.end(), pos.begin(), ToPOS());

		return GrammarPattern(pos);
	}

	shared_ptr<DataCollection::Word> LanguageFunc::GetParticularWord(const std::string str, const DataCollection::PartOfSpeech partofspeech)
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
		case Punctuation:
			return shared_ptr<Word>(new puncture(str));
		case Unknown:
			return NULL;
		default:
			break;
		}

		return NULL;
	}

	int LanguageFunc::IndexOf( const vector<shared_ptr<Word>>& words,const shared_ptr<Word> word )
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


	vector<shared_ptr<Word>> LanguageFunc::RemovePuncs( const vector<shared_ptr<Word>>& words )
	{
		vector<shared_ptr<Word>> res;
		remove_copy_if(words.begin(),words.end(),back_inserter(res),LanguageFunc::IsPuncture);
		return res;
	}

	bool LanguageFunc::IsPuncture( const shared_ptr<Word> word )
	{
		if(word->Type()==Punctuation)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool LanguageFunc::SameGrammarPattern( const GrammarPattern& left,const GrammarPattern& right )
	{
		return left.IsSameWith(right);
	}

	std::string LanguageFunc::ConvertWordsToString( const vector<shared_ptr<Word>> words )
	{
		string res="";
		for (unsigned int i=0;i<words.size();++i)
		{
			res+=words[i]->GetString();
		}

		return res;
	}

}

