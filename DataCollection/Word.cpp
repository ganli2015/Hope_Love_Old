#include "StdAfx.h"
#include "Character.h"
#include "Word.h"
#include <math.h>
#include <iterator>
#include "../CommonTools/CommonTranslateFunction.h"

using namespace std;
using namespace CommonTool;
namespace DataCollection
{
	Word::Word(void):_known(false)
	{
	}

	Word::Word(std::vector<shared_ptr<Character>> word):_word(word),_known(false)
	{
	}

	Word::Word(const Character chara):_known(false)
	{
		_word.push_back(shared_ptr<Character>(new Character(chara)));
	}

	Word::Word(string word ):_known(false)
	{
		for (unsigned int i=0;i<word.size();i+=2)
		{
			string aword;
			aword.push_back(word[i]);
			aword.push_back(word[i+1]);
			_word.push_back(shared_ptr<Character>(new Character(aword)));
		}
	}


	Word::~Word(void)
	{
	}

	Word::Word(const Word& word)
	{
		_word.clear();
		for (unsigned int i=0;i<word._word.size();++i)
		{
			_word.push_back(word._word[i]);
		}
		_known=word._known;
	}

	long long Word::ToInt()const
	{
		vector<int>  indexset;
		for (vector<shared_ptr<Character>>::const_iterator it=_word.begin();it!=_word.end();++it)
		{
			indexset.push_back((*it)->ToInt());
		}

		long long sumIndex=0;
		for (unsigned int i=0;i<indexset.size();++i)
		{
			sumIndex+=sumIndex*i*10000+indexset[i];
		}

		return sumIndex;
	}

	bool Word::IsSame(const shared_ptr<Word> word ) const
	{
		if(word->NumOfChara()!=NumOfChara())
			return false;

		if(ToInt()==word->ToInt())
			return true;
		else return false;
	}

	std::string Word::GetString() const
	{
		string str("");
		for (unsigned int i=0;i<_word.size();++i)
		{
			str+=_word[i]->GetString();
		}
		return str;
	}

	Word& Word::operator+=(const Character right)
	{
		_word.push_back(shared_ptr<Character>(new Character(right)));
		return *this;
	}

	Word& Word::operator=( const Word right )
	{
		_word=right._word;
		return *this;
	}

	DataCollection::PartOfSpeech Word::Type() const
	{
		if(_known)
			return Ambiguous;
		else return Unknown;
	}

	Word operator+(const Character left,const Character right )
	{
		string str(left.GetString());
		str+=right.GetString();

		return Word(str);
	}

	Word operator+( const Word left,const Character right )
	{
		return Word(left.GetString()+right.GetString());
	}

	Word operator+( const Character left,const Word right )
	{
		return Word(left.GetString()+right.GetString());
	}

	Word operator+( const Word left,const Word right )
	{
		return Word(left.GetString()+right.GetString());
	}

}



