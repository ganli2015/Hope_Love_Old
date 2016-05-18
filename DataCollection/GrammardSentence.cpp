#include "StdAfx.h"
#include "GrammardSentence.h"
#include "GrammaPattern.h"
#include "Word.h"
#include "LanguageFunc.h"


namespace DataCollection
{
	GrammardSentence::GrammardSentence()
	{

	}

	GrammardSentence::~GrammardSentence()
	{

	}

	GrammardSentence::GrammardSentence(const std::vector<shared_ptr<DataCollection::Word>> vec)
	{
		_gra=vec;
	}

	std::vector<shared_ptr<Word>> GrammardSentence::Get() const
	{
		return _gra;
	}

	void GrammardSentence::ClassifyGrammarInfoSet(multimap<int,GraAssoInfo>& graInfoSet,const vector<vector<int>>& indexes,const GrammarPattern& pattern)
	{
		for (unsigned int i=0;i<indexes.size();++i)
		{
			vector<int> indexSeq=indexes[i];
			for (unsigned int j=0;j<indexSeq.size();++j)
			{
				GraAssoInfo info;
				info.indexes=indexSeq;
				info.pattern=pattern;
				graInfoSet.insert(make_pair(indexSeq[j],info));
			}
		}
	}

	bool GrammardSentence::BuildGrammarAssociation( const vector<GrammarPattern>& grammarPatterns )
	{
		if(_gra.empty()) return false;

		//整句话的GrammarPattern
		GrammarPattern raw=LanguageFunc::ConvertToPattern(_gra);
		for (unsigned int i=0;i<grammarPatterns.size();++i)
		{
			if(grammarPatterns[i].GetID()<0)
			{
				throw runtime_error("Error in BuildGrammarAssociation:The ID of Pattern is incorrect!");
			}

			vector<vector<int>> indexes;
			GetIndexOfMatchedPattern(raw,grammarPatterns[i],indexes);
			if(indexes.empty())
			{
				throw runtime_error("Error in BuildGrammarAssociation:Cannot find pattern!");
			}

			ClassifyGrammarInfoSet(_graInfoSet,indexes,grammarPatterns[i]);
		}

		return true;
	}

	bool GrammardSentence::GetIndexOfMatchedPattern(const GrammarPattern& patternRaw,
		const GrammarPattern& patternMatch, 
		vector<vector<int>>& indexes)
	{
		if(patternRaw.Size()==0)
		{
			return false;
		}
		if(patternMatch.Size()==0)
		{
			return false;
		}

		indexes.clear();

		GetIndexOfMatchedPattern(patternRaw,patternMatch,0,0,indexes);
		return true;
	}

	void GrammardSentence::GetIndexOfMatchedPattern( 
		const GrammarPattern& patternRaw,
		const GrammarPattern& patternMatch,
		const unsigned int rawStartIndex,
		const unsigned int matchStartIndex,
		vector<vector<int>>& indexes )
	{
		if(rawStartIndex>patternRaw.Size()-1)
		{
			return;
		}
		if(matchStartIndex>patternMatch.Size()-1)
		{
			return;
		}

		//从patternRaw的第rawStartIndex个元素到最后中，寻找与patternMatch的第matchStartIndex到最后的部分相匹配元素的序号。
		int patternSize=patternMatch.Size();
		PartOfSpeech matchPOE=patternMatch.Get_ithElem(matchStartIndex);
		for (unsigned int i=rawStartIndex;i<patternRaw.Size();++i)
		{
			PartOfSpeech rawPOE=patternRaw.Get_ithElem(i);
			if(rawPOE!=matchPOE)//如果当前元素不匹配，就继续。
			{
				continue;
			}

			if(matchStartIndex==patternMatch.Size()-1)//不进入递归
			{
				vector<int> oneIndex;
				oneIndex.push_back(i);
				indexes.push_back(oneIndex);
				continue;
			}

			vector<vector<int>> tmpIndexes;
			GetIndexOfMatchedPattern(patternRaw,patternMatch,i+1,matchStartIndex+1,tmpIndexes);
			if(tmpIndexes.empty())
			{
				continue;
			}
			//把子区域得到的indexes串起来
			for (unsigned int j=0;j<tmpIndexes.size();++j)
			{
				vector<int> newPattern;
				newPattern.push_back(i);
				newPattern.insert(newPattern.end(),tmpIndexes[j].begin(),tmpIndexes[j].end());
				indexes.push_back(newPattern);
			}
		}
	}

	void GrammardSentence::GetAssociationInfo( const unsigned int i,vector<vector<int>>& associatedIndexes,vector<GrammarPattern>& associatedPatterns )
	{
		if(i>=_gra.size())
		{
			throw out_of_range("i is out of the range");
		}

		associatedIndexes.clear();
		associatedPatterns.clear();

		multimap<int,GraAssoInfo>::iterator beg=_graInfoSet.lower_bound(i);
		multimap<int,GraAssoInfo>::iterator end=_graInfoSet.upper_bound(i);
		while(beg!=end)
		{
			associatedIndexes.push_back(beg->second.indexes);
			associatedPatterns.push_back(beg->second.pattern);
			beg++;
		}
	}

}