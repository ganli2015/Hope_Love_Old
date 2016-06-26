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
		//Convert grammar information into a new structure:
		//a word and its associated grammar patterns as well as indexes of words each of grammar pattern is related with.
		//In this way, for each word, which words it connects to is easily to be seen.
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

		GrammarPattern raw=LanguageFunc::ConvertToPattern(_gra);
		for (unsigned int i=0;i<grammarPatterns.size();++i)
		{
			if(grammarPatterns[i].GetID()<0)
			{
				throw runtime_error("Error in BuildGrammarAssociation:The ID of Pattern is incorrect!");
			}

			//For each grammar pattern , compute indexes of words that matching the grammar pattern.
			vector<vector<int>> indexes;
			GetIndexOfMatchedPattern(raw,grammarPatterns[i],indexes);
			if(indexes.empty())
			{
				throw runtime_error("Error in BuildGrammarAssociation:Cannot find pattern!");
			}

			//Classify grammar information into a new structure
			//in which one word corresponding to its grammar information.
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

		//Use recursion to solve the problem as it is a problem of divide-and-conquer.
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

		//Search from <rawStartIndex> to end in <patternRaw>, 
		//find sequences matching with sequences from <matchStartIndex> to end in <patternMatch>.
		//It is a problem of divide-and-conquer.Once <patternRaw> and <patternMatch> are matched, their some sub sequences are also matched.
		//And for each <patternMatch>, there are several matched indexes.
		int patternSize=patternMatch.Size();
		PartOfSpeech matchPOS=patternMatch.Get_ithElem(matchStartIndex);
		for (unsigned int i=rawStartIndex;i<patternRaw.Size();++i)
		{
			PartOfSpeech rawPOS=patternRaw.Get_ithElem(i);
			//Find the next matched POS in <patternRaw>.
			//For current <matchPOS>, there are several satisfied <rawPOS>.
			if(rawPOS!=matchPOS)
			{
				continue;
			}

			//If reach the end of <patternMatch>, simply append the last index satisfied to the result.
			if(matchStartIndex==patternMatch.Size()-1)
			{
				vector<int> oneIndex;
				oneIndex.push_back(i);
				indexes.push_back(oneIndex);
				continue;
			}

			//Go on to search the substructure of the problem.
			vector<vector<int>> tmpIndexes;
			GetIndexOfMatchedPattern(patternRaw,patternMatch,i+1,matchStartIndex+1,tmpIndexes);
			if(tmpIndexes.empty())
			{
				continue;
			}
			
			//Connect results in substructure with current results.
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