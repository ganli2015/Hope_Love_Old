#include "StdAfx.h"
#include "GrammaPattern.h"

#include "../Mathmatic/FindSequence.h"

using namespace std;
namespace DataCollection
{
	GrammarPattern::GrammarPattern(void):_id(-1)
	{
	}


	GrammarPattern::~GrammarPattern(void)
	{
	}

	GrammarPattern::GrammarPattern(const std::vector<int>& val):_pattern(val),_id(-1)
	{

	}

	GrammarPattern::GrammarPattern(const std::vector<PartOfSpeech>& val):_id(-1)
	{
		_pattern.clear();
		for (unsigned int i=0;i<val.size();++i)
		{
			_pattern.push_back((int)val[i]);
		}
	}

	pair<GrammarPattern,GrammarPattern> GrammarPattern::Divide( const int index )  const
	{
		assert(index>=-1 && index<=(int)(_pattern.size()-1));

		//Get the former reversed pattern.
		vector<int> former;
		for (int i=0;i<=index;++i)
		{
			former.push_back(_pattern[i]);
		}
		reverse(former.begin(),former.end());
		//Get the latter pattern.
		vector<int> latter;
		for (unsigned int i=index+1;i<_pattern.size();++i)
		{
			latter.push_back(_pattern[i]);
		}

		GrammarPattern formerPattern(former);
		GrammarPattern latterPattern(latter);
		//Set the same ID with <me> for convenience search of the divided patterns.
		formerPattern.SetID(_id);
		latterPattern.SetID(_id);
		return make_pair(formerPattern,latterPattern);
	}

	std::vector<PartOfSpeech> GrammarPattern::GetPattern() const
	{
		vector<PartOfSpeech> res;
		res.reserve(_pattern.size());
		for (unsigned int i=0;i<_pattern.size();++i)
		{
			res.push_back((PartOfSpeech)_pattern[i]);
		}
		return res;
	}

	bool GrammarPattern::IsSubsequenceOf( const GrammarPattern& pattern ) const
	{
		return Math::IsSubsequence<PartOfSpeech>(GetPattern(),pattern.GetPattern());
	}

	bool GrammarPattern::ContainSubsequence( const GrammarPattern& sub ) const
	{
		return Math::IsSubsequence<PartOfSpeech>(sub.GetPattern(),GetPattern());
	}

	bool GrammarPattern::IsSameWith( const GrammarPattern& pattern ) const
	{
		if(_pattern.size()!=pattern._pattern.size())
		{
			return false;
		}

		for (unsigned int i=0;i<_pattern.size();++i)
		{
			if(_pattern[i]!=pattern._pattern[i])
			{
				return false;
			}
		}

		return true;
	}

	bool operator==( const GrammarPattern& left,const GrammarPattern& right )
	{
		return left.IsSameWith(right);
	}

}

