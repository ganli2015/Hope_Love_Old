#include "StdAfx.h"
#include "GrammaSet.h"
#include "FilePath.h"

#include "../MindElement/GrammarLocal.h"

#include "../DataCollection/LanguageFunc.h"
#include "../DataCollection/Word.h"

#include "../Mathmatic/FindSequence.h"

#include <fstream>
#include <functional>

using namespace DataCollection;
using namespace std;
using namespace Math;


namespace Mind
{
	GrammarSet::GrammarSet(void)
	{
		Initialize();
	}


	GrammarSet::~GrammarSet(void)
	{
	}

	void GrammarSet::Initialize()
	{
#ifdef _Extract_Initial_Grammar_Pattern
		ExtractGrammarPatternFromInitialFile();
#endif // _Extract_Initial_Grammar_Pattern

		ExtractGrammarLocalDistribution();

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

			//AddPatternToTree(pattern);
		}

	}

	vector<GrammarAttribute> GrammarSet::InputGrammaPatterns( std::string filename )
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
	
	

	std::vector<GrammarPattern> GrammarSet::ContainSubsequence( const GrammarPattern& pattern ) const
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


	std::vector<DataCollection::GrammarPattern> GrammarSet::ContainedSubsequence( const DataCollection::GrammarPattern& pattern ) const
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


	int GrammarSet::CountOfSubsequence( const DataCollection::GrammarPattern& pattern ) const
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

	int GrammarSet::GetFreqencyofPattern( const DataCollection::GrammarPattern& pattern ) const
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

	void GrammarSet::AddGrammarPattern( DataCollection::GrammarPattern& pattern )
	{
		//ID为最大ID+1.
		pattern.SetID(GetMaxID()+1);
		GrammarAttribute g_a;
		g_a.pattern=pattern;
		g_a.frequency=1;

		_patterns.push_back(g_a);
	}

	void GrammarSet::IncreasePatternFreqency( const DataCollection::GrammarPattern& pattern )
	{
		int index=FindPatternIndex(pattern);
		if(index==-1)
		{
			GrammarPattern copy=pattern;
			AddGrammarPattern(copy);
		}
		else
		{
			GrammarAttribute g_a=_patterns[index];
			g_a.frequency++;
			_patterns[index]=g_a;
		}
		
	}

	void GrammarSet::AddPatternToTree( const DataCollection::GrammarPattern& pattern )
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

	int GrammarSet::GetMaxID() const
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

	int GrammarSet::FindPatternIndex( const DataCollection::GrammarPattern& pattern )
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

	vector<GrammarPattern> GrammarSet::GrammarPatternSortByFrequency() const
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

	vector<GrammarSet::Sen_Gra> GrammarSet::InputGraSamples(string file) const
	{
		vector<Sen_Gra> samples;

		ifstream in(file);

		while(!in.eof())
		{
			Sen_Gra sample;

			int count;
			in>>count;
			Vector array(NUM_PARTOFSPEECH);
			vector<int> gra;
			gra.reserve(count);
			for (int i=1;i<=count;++i)
			{
				int elem;
				in>>elem;
				++array[elem];
				gra.push_back(elem);
			}

			sample.gra=gra;
			array.Normalize();
			samples.push_back(sample);
		}

		return samples;
	}

	std::vector<std::vector<int>> GrammarSet::FindAllCommonSequences( const vector<Sen_Gra>& samples) const
	{
		std::vector<std::vector<int>> allcommon_seqs;
		for (unsigned int i=0;i<samples.size();++i)
		{
			vector<int> gra1=samples[i].gra;
			for (unsigned int j=i+1;j<samples.size();++j)
			{
				vector<int> gra2=samples[j].gra;
				std::vector<std::vector<int>> common_seqs;
				Math::FindAllCommonSubsequence(gra1,gra2,common_seqs);
				allcommon_seqs.insert(allcommon_seqs.end(),common_seqs.begin(),common_seqs.end());
			}
		}

		return allcommon_seqs;
	}

	vector<GrammarSet::Pattern_Distribution> GrammarSet::ComputePatternDistribution(const std::vector<std::vector<int>>& allcommon_seqs) const
	{
		vector<Pattern_Distribution> p_d;
		for (unsigned int i=0;i<allcommon_seqs.size();++i)
		{
			vector<int> pattern=allcommon_seqs[i];
			bool existed(false);
			for (unsigned int j=0;j<p_d.size();++j)
			{
				vector<int> pattern2=p_d[j].pattern;
				if(pattern==pattern2)
				{
					p_d[j].count++;
					existed=true;
					break;
				}
			}
			if(existed==false)
			{
				Pattern_Distribution pd;
				pd.pattern=pattern;
				pd.count=1;
				p_d.push_back(pd);
			}
		}

		return p_d;
	}

	void GrammarSet::OutputPatternDistribution(const vector<Pattern_Distribution>& p_d) const
	{
		ofstream out(GetHopeLoveMindPath()+GrammaPatterns_InitialFilename);
		out.clear();
		for (unsigned int i=0;i<p_d.size();++i)
		{
			vector<int> seq=p_d[i].pattern;
			out<<seq.size()<<" ";
			for (unsigned int j=0;j<seq.size();++j)
			{
				out<<seq[j]<<" ";
			}
			out<<p_d[i].count<<" ";
			out<<endl;
		}
	}

	void GrammarSet::ExtractGrammarPatternFromInitialFile() const
	{
		vector<Sen_Gra> samples=InputGraSamples(GetHopeLoveMindPath()+StringGrammar_InitialFilename);

		std::vector<std::vector<int>> allcommon_seqs=FindAllCommonSequences(samples);

		vector<Pattern_Distribution> p_d=ComputePatternDistribution(allcommon_seqs);

		OutputPatternDistribution(p_d);
	}

	void GrammarSet::ExtractGrammarLocalDistribution()
	{
		vector<Sen_Gra> samples=InputGraSamples(GetHopeLoveMindPath()+StringGrammar_InitialFilename);

		map<PartOfSpeech,GrammarLocal> grammarLocalTable;
		for (int i=0;i<NUM_PARTOFSPEECH;++i)
		{
			_grammarLocalTable[PartOfSpeech(i)]=shared_ptr<GrammarLocal>(new GrammarLocal(PartOfSpeech(i)));
		}
		for (unsigned int i=0;i<samples.size();++i)
		{
			vector<int> gra=samples[i].gra;
			for (unsigned int j=0;j<gra.size();++j)
			{
				PartOfSpeech curPos=PartOfSpeech(gra[j]);
				if(j==0)
				{
					_grammarLocalTable[curPos]->AddForward(PartOfSpeech(gra[j+1]));
				}
				else if(j==gra.size()-1)
				{
					_grammarLocalTable[curPos]->AddBackward(PartOfSpeech(gra[j-1]));
				}
				else
				{
					_grammarLocalTable[curPos]->AddForward(PartOfSpeech(gra[j+1]));
					_grammarLocalTable[curPos]->AddBackward(PartOfSpeech(gra[j-1]));
				}
			}
		}
	}

	double GrammarSet::GetP_Forward( const DataCollection::PartOfSpeech& me,const DataCollection::PartOfSpeech& forward ) const
	{
		return _grammarLocalTable.at(me)->GetRatio_Forward(forward);
	}

	double GrammarSet::GetP_Backward( const DataCollection::PartOfSpeech& me,const DataCollection::PartOfSpeech& backward ) const
	{
		return _grammarLocalTable.at(me)->GetRatio_Backward(backward);
	}


	

	

}

