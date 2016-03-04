#include "StdAfx.h"
#include "GrammaSet.h"
#include "FilePath.h"

#include "../DataCollection/DataBaseProcessorTool.h"

#include <fstream>
#include <functional>

using namespace DataCollection;
using namespace std;
namespace Mind
{
	GrammaSet::GrammaSet(void)
	{
		Initialize();
	}


	GrammaSet::~GrammaSet(void)
	{
	}

	void GrammaSet::Initialize()
	{
		vector<GrammarAttribute> patterns=InputGrammaPatterns(GetHopeLoveMindPath()+GrammaPatterns_InitialFilename);

		for (int i=0;i<DataCollection::NUM_PARTOFSPEECH;++i)
		{
			GrammaTree for_tree(i);
			GrammaTree back_tree(i);
			_forwardtree.insert(make_pair(i,for_tree));
			_backwardtree.insert(make_pair(i,back_tree));
		}

		for (unsigned int i=0;i<patterns.size();++i)
		{
			GrammarPattern pattern=patterns[i].pattern;
			_patterns.push_back(patterns[i]);

			AddPatternToTree(pattern);
		}

	}

	vector<GrammarAttribute> GrammaSet::InputGrammaPatterns( std::string filename )
	{
		vector<GrammarAttribute> patterns;

		ifstream in(filename);

		int id(0);
		while(!in.eof())
		{
			int count;
			in>>count;

			vector<int> pattern_int;
			pattern_int.reserve(count);
			for (int i=1;i<=count;++i)
			{
				int elem;
				in>>elem;
				pattern_int.push_back(elem);
			}

			vector<PartOfSpeech> pattern_enum;
			pattern_enum.reserve(pattern_int.size());
			for (unsigned int i=0;i<pattern_int.size();++i)
			{
				pattern_enum.push_back((PartOfSpeech)pattern_int[i]);
			}

			GrammarPattern pattern(pattern_enum);
			pattern.SetID(id++);
			int frequency;
			in>>frequency;

			GrammarAttribute ga;
			ga.pattern=pattern;
			ga.frequency=frequency;
			patterns.push_back(ga);
		}

		return patterns;
	}
	
	

	std::vector<GrammarPattern> GrammaSet::ContainSubsequence( const GrammarPattern& pattern ) const
	{
		class ExtractSubsequences
		{
			vector<GrammarPattern> _sub;
			GrammarPattern _input;
		public:
			ExtractSubsequences(const GrammarPattern& pattern):_input(pattern){}
			~ExtractSubsequences(){}

			vector<GrammarPattern> GetResult()const {return _sub;}
			void operator()(const GrammarAttribute& pattern)
			{
				if(_input.ContainSubsequence(pattern.pattern))
				{
					_sub.push_back(pattern.pattern);
				}
			}
		};

		ExtractSubsequences extractsub(pattern);
		extractsub=for_each(_patterns.begin(),_patterns.end(),extractsub);
		return extractsub.GetResult();
	}


	std::vector<DataCollection::GrammarPattern> GrammaSet::ContainedSubsequence( const DataCollection::GrammarPattern& pattern ) const
	{
		class ExtractParentsequences
		{
			vector<GrammarPattern> _parent;
			GrammarPattern _input;
		public:
			ExtractParentsequences(const GrammarPattern& pattern):_input(pattern){}
			~ExtractParentsequences(){}

			vector<GrammarPattern> GetResult()const {return _parent;}
			void operator()(const GrammarAttribute& pattern)
			{
				if(_input.IsSubsequenceOf(pattern.pattern))
				{
					_parent.push_back(pattern.pattern);
				}
			}
		};

		ExtractParentsequences extractParent(pattern);
		extractParent=for_each(_patterns.begin(),_patterns.end(),extractParent);
		return extractParent.GetResult();
	}


	int GrammaSet::CountOfSubsequence( const DataCollection::GrammarPattern& pattern ) const
	{
		class countSubsequences
		{
			GrammarPattern _input;
			int _count;
		public:
			countSubsequences(const GrammarPattern& pattern):_input(pattern),_count(0){}
			~countSubsequences(){}

			int GetResult()const {return _count;}
			void operator()(const GrammarAttribute& pattern)
			{
				if(_input.ContainSubsequence(pattern.pattern))
				{
					++_count;
				}
			}
		};

		countSubsequences countsub(pattern);
		countsub=for_each(_patterns.begin(),_patterns.end(),countsub);
		return countsub.GetResult();
	}

	int GrammaSet::GetFreqencyofPattern( const DataCollection::GrammarPattern& pattern ) const
	{
		if(pattern.Size()==0) return -1;
		if(pattern.GetID()<0) return -1;

		int id=pattern.GetID();
		if(id<0)
		{
			throw runtime_error("Error in GetFreqencyofPattern");
		}

		return _patterns[id].frequency;
	}

	void GrammaSet::AddGrammarPattern( DataCollection::GrammarPattern& pattern )
	{
		//ID为最大ID+1.
		pattern.SetID(GetMaxID()+1);
		GrammarAttribute g_a;
		g_a.pattern=pattern;
		g_a.frequency=1;

		_patterns.push_back(g_a);
	}

	void GrammaSet::IncreasePatternFreqency( const DataCollection::GrammarPattern& pattern )
	{
		int index=FindPatternIndex(pattern);
		if(index==-1)
		{
			throw runtime_error("Error in IncreasePatternFreqency");
			return;
		}

		GrammarAttribute g_a=_patterns[index];
		g_a.frequency++;
		_patterns[index]=g_a;
	}

	void GrammaSet::AddPatternToTree( const DataCollection::GrammarPattern& pattern )
	{
		for (unsigned int j=-1;j<pattern.Size();++j)
		{
			pair<GrammarPattern,GrammarPattern> pattern_pair=pattern.Divide(j);
			GrammarPattern former=pattern_pair.first;
			if(former.Size())//former one is backward!!
			{
				_backwardtree[former.Get_ithElem(0)].AppendGramma(former);
			}
			GrammarPattern latter=pattern_pair.second;
			if(latter.Size())//latter one is forward!!
			{
				_forwardtree[latter.Get_ithElem(0)].AppendGramma(latter);
			}
		}
	}

	int GrammaSet::GetMaxID() const
	{
		class FindMaxID
		{
			int _max;
		public:
			FindMaxID(){}
			~FindMaxID(){}

			void operator()(const GrammarAttribute& g_a)
			{
				if(g_a.pattern.GetID()>_max)
				{
					_max=g_a.pattern.GetID();
				}
			}

			int GetResult(){return _max;}
		};

		FindMaxID findMaxID;
		findMaxID=for_each(_patterns.begin(),_patterns.end(),findMaxID);

		return findMaxID.GetResult();
	}

	int GrammaSet::FindPatternIndex( const DataCollection::GrammarPattern& pattern )
	{
		class SamePattern
		{
			GrammarPattern _pattern;

		public:
			SamePattern(const GrammarPattern& val):_pattern(val){}
			~SamePattern(){}

			bool operator()(const GrammarAttribute& g_a)
			{
				if(g_a.pattern.IsSameWith(_pattern))
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		};
		vector<GrammarAttribute>::iterator find_iter=find_if(_patterns.begin(),_patterns.end(),SamePattern(pattern));
		if(find_iter==_patterns.end())
		{
			return -1;
		}
		else
		{
			return distance(_patterns.begin(),find_iter);
		}
	}

	vector<GrammarPattern> GrammaSet::GrammarPatternSortByFrequency() const
	{
		class SortAttribute
		{
		public:
			SortAttribute(){}
			~SortAttribute(){}

			bool operator()(const GrammarAttribute& left,const GrammarAttribute& right)
			{
				if(left.frequency>right.frequency)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		};

		//对频率从大到小排序
		vector<GrammarAttribute> grammarAttributes=_patterns;
		sort(grammarAttributes.begin(),grammarAttributes.end(),SortAttribute());

		class ExtracePattern
		{
		public:
			ExtracePattern(){}
			~ExtracePattern(){}

			GrammarPattern operator()(const GrammarAttribute& g_a)
			{
				return g_a.pattern;
			}
		};

		//把GrammarAttribute转换成GrammarPattern
		vector<GrammarPattern> res;
		transform(grammarAttributes.begin(),grammarAttributes.end(),back_inserter(res),ExtracePattern());

		return res;
	}


	

	

}

