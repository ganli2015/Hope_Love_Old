#include "StdAfx.h"
#include "Sentence.h"
#include "Character.h"

#include "DataBaseProcessorTool.h"
#include "Word.h"

using namespace CommonTool;
using namespace std;
namespace DataCollection
{
	Sentence::Sentence(void)
	{
	}


	Sentence::~Sentence(void)
	{
// 		DeleteVectorPtr(_rawSentence);
// 		for (unsigned int i=0;i<_segmented.size();++i)
// 		{
// 			DeleteVectorPtr(_segmented[i]);
// 		}
		
	}

	Sentence::Sentence(std::vector<shared_ptr<Character>> val):_rawSentence(val)
	{

	}

	Sentence::Sentence(std::string str):_rawSentence(str)
	{
		
	}

	std::vector<shared_ptr<Character>> Sentence::GetRawSentence() const
	{
		return _rawSentence.GetRawSentence();
	}

	void Sentence::AddSegmented( const std::vector<shared_ptr<DataCollection::Word>> vec )
	{
		_segmented.push_back(SegmentedSentence(vec));
	}

	void Sentence::AddGrammard( const std::vector<shared_ptr<DataCollection::Word>> vec )
	{
		_grammard.push_back(GrammardSentence(vec));
		_structured.push_back(StructuredSentence(vec));
	}

	vector<shared_ptr<Word>> Sentence::GetSegmented( const unsigned int i ) const
	{
		if(i>_segmented.size())
		{
			throw out_of_range("");
		}
		return _segmented[i].Get();
	}

	std::vector<shared_ptr<Word>> Sentence::GetGrammard( const unsigned int i ) const
	{
		if(_grammard.empty())
		{
			throw runtime_error("No Grammared!!");
		}

		if(i>_grammard.size())
		{
			throw out_of_range("");
		}
		return _grammard[i].Get();
	}

	void Sentence::BuildGrammarAssociation(const int i, const vector<GrammarPattern>& patterns )
	{
		_grammard[i].BuildGrammarAssociation(patterns);
	}

	void Sentence::GetAssociationInfo( const int i_thGra,const int i_thWord,vector<vector<int>>& associatedIndexes,vector<GrammarPattern>& associatedPatterns )
	{
		_grammard[i_thGra].GetAssociationInfo(i_thWord,associatedIndexes,associatedPatterns);
	}

	unsigned int Sentence::GrammarWordCount( const unsigned int i )
	{
		if(i>=_grammard.size())
		{
			throw out_of_range("i is out of the range!!");
		}
		return _grammard[i].WordCount();
	}

	void Sentence::SetWordIntensity( const unsigned int i,const unsigned int i_word,const unsigned int j_word,double intensity )
	{
		if(i>=_structured.size())
		{
			throw out_of_range("i is out of the range!!");
		}

		_structured[i].SetIntensity(i_word,j_word,intensity);
	}

	double Sentence::GetWordIntensity( const unsigned int i,const unsigned int i_word,const unsigned int j_word )
	{
		if(i>=_structured.size())
		{
			throw out_of_range("i is out of the range!!");
		}

		return _structured[i].GetIntensity(i_word,j_word);
	}

	std::string Sentence::GetString() const
	{
		return _rawSentence.GetString();
	}


	RawSentence::RawSentence()
	{

	}

	RawSentence::~RawSentence()
	{

	}

	RawSentence::RawSentence(std::vector<shared_ptr<Character>> vec)
	{
		_raw=vec;
	}

	RawSentence::RawSentence(std::string str)
	{
		std::vector<shared_ptr<Character>> val=DataBaseProcessorTool::ConvertStringToCharacter(str);
		_raw=val;
	}

	std::vector<shared_ptr<Character>> RawSentence::GetRawSentence() const
	{
		return _raw;
	}

	std::string RawSentence::GetString() const
	{
		return DataBaseProcessorTool::ConvertCharacterToString(_raw);
	}




	SegmentedSentence::SegmentedSentence()
	{

	}

	SegmentedSentence::~SegmentedSentence()
	{

	}

	SegmentedSentence::SegmentedSentence(const std::vector<shared_ptr<DataCollection::Word>> vec)
	{
		_seg=vec;
	}

	std::vector<shared_ptr<Word>> SegmentedSentence::Get() const
	{
		return _seg;
	}


	

}


