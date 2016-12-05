#include "StdAfx.h"
#include "GrammaSet.h"
#include "FilePath.h"

#include "../CommonTools/LogWriter.h"

#include "../MindElement/GrammarLocal.h"

#include "../DataCollection/LanguageFunc.h"
#include "../DataCollection/Word.h"

#include "../CommonTools/ConfigureInfoManager.h"
#include "../CommonTools/GeneralFunctor.h"
#include "../CommonTools/CommonStringFunction.h"

#include "../Mathmatic/FindSequence.h"

#include <tinyxml.h>

#include <fstream>
#include <functional>
#include <numeric>

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

		//ExtractGrammarLocalDistribution();
		ReadGrammarLocal();

		//Input the grammar patterns from the file.
		vector<GrammarAttribute> patterns=InputGrammaPatterns(GetHopeLoveMindPath()+GrammaPatterns_InitialFilename);

		//Build the grammar trees.
		for (int i=0;i<DataCollection::NUM_PARTOFSPEECH;++i)
		{
			GrammaTree for_tree(i);
			GrammaTree back_tree(i);
			_forwardtree.insert(make_pair(i,for_tree));
			_backwardtree.insert(make_pair(i,back_tree));
		}

		//Add patterns to <me>.
		for (unsigned int i=0;i<patterns.size();++i)
		{
			GrammarPattern pattern=patterns[i].pattern;
			_patterns.push_back(patterns[i]);

			//AddPatternToTree(pattern);
		}

		ReadWeights();

		CFG_SECTION(COMPUTE_GRAMMAR_WEIGHTS)
		{
			InitializeWeights();
		}
	}

	vector<GrammarAttribute> GrammarSet::InputGrammaPatterns( std::string filename )
	{
		vector<GrammarAttribute> patterns;

		ifstream in(filename);
		if (!in) return patterns;

		int id(0);
		string line = "";
		while(getline(in,line))
		{
// 			int count;
// 			in>>count;
// 
// 			vector<int> pattern_int;
// 			pattern_int.reserve(count);
// 			for (int i=1;i<=count;++i)
// 			{
// 				int elem;
// 				in>>elem;
// 				out << elem<<" ";
// 				pattern_int.push_back(elem);
// 			}
// 
// 
// 			vector<PartOfSpeech> pattern_enum;
// 			pattern_enum.reserve(pattern_int.size());
// 			for (unsigned int i=0;i<pattern_int.size();++i)
// 			{
// 				pattern_enum.push_back((PartOfSpeech)pattern_int[i]);
// 			}
// 
// 			GrammarPattern pattern(pattern_enum);
// 			pattern.SetID(id++);
// 			int frequency;
// 			in>>frequency;
// 
// 			out << frequency<<endl;

			vector<string> splits_withBlanks = CommonTool::SplitString(line, ' ');
			//Erase null strings
			vector<string> splits;
			for (unsigned int i=0;i<splits_withBlanks.size();++i)
			{
				if (splits_withBlanks[i] != "")
				{
					splits.push_back(splits_withBlanks[i]);
				}
			}

			vector<PartOfSpeech> pattern_enum;
			for (unsigned int i = 0; i < splits.size() - 1; ++i)
			{
				pattern_enum.push_back((PartOfSpeech)atoi(splits[i].c_str()));
			}
			int frequency = atoi(splits.back().c_str());

			GrammarPattern pattern(pattern_enum);
			pattern.SetID(id++);

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
			FindMaxID():_max(0){}
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

	Math::MyInt GrammarSet::GetTotalFrequency() const
	{
		Math::MyInt res(0);
		for (vector<GrammarAttribute>::const_iterator it=_patterns.begin();it!=_patterns.end();++it)
		{
			res += it->frequency;
		}

		return res;
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
		if (!in) return samples;

		while(!in.eof())
		{
			Sen_Gra sample;

			int count;
			in>>count;
//			Vector array(NUM_PARTOFSPEECH);
			vector<int> gra;
			gra.reserve(count);
			for (int i=1;i<=count;++i)
			{
				int elem;
				in>>elem;
//				++array[elem];
				gra.push_back(elem);
			}

			sample.gra=gra;
//			array.Normalize();
			samples.push_back(sample);
		}

		return samples;
	}

	

	void GrammarSet::ExtractGrammarLocalDistribution()
	{
		vector<Sen_Gra> samples=InputGraSamples(GetHopeLoveMindPath()+StringGrammar_InitialFilename);
		if (samples.empty()) return;

		//Initialize each POS with GrammarLocal.
		map<PartOfSpeech,GrammarLocal> grammarLocalTable;
		for (int i=0;i<NUM_PARTOFSPEECH;++i)
		{
			_grammarLocalTable[PartOfSpeech(i)]=shared_ptr<GrammarLocal>(new GrammarLocal(PartOfSpeech(i)));
		}

		//Statistic the distribution of frequencies of POS from <samples>.
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


	double GrammarSet::ComputePossibility(const DataCollection::GrammarPattern& pattern) const
	{
		//The final possibility takes local grammar and grammar patterns of <pattern> into consideration.
		//And the above two components has weights respectively.
		MyInt totalFreq = GetTotalFrequency();
		double localP = ComputeP_GrammarLocalAnalysis(pattern);
		double patternP = ComputePossibilityGrammarPattern(pattern, totalFreq);
		double res = _wPattern*patternP + _wLocal*localP;
		
		//Adjust the possibility such that it is in the interval of 0 to 1.
		res = min(1., res);
		res = max(0., res);

		return res;
	}

	double GrammarSet::ComputeP_GrammarLocalAnalysis(const DataCollection::GrammarPattern& pattern) const
	{
		vector<PartOfSpeech> poses = pattern.GetPattern();
		//Remove punctuations as they may interfere computation.
		for (vector<PartOfSpeech>::iterator it = poses.begin(); it != poses.end();)
		{
			if (*it == Punctuation)
			{
				it = poses.erase(it);
			}
			else
			{
				++it;
			}
		}

		if (poses.size() <= 1) return 0.;

		double res = 0.;
		for (unsigned int i = 0; i<poses.size(); ++i)
		{
			PartOfSpeech curPos = poses[i];
			if (i == 0)//第一个词性只考虑与第二个词性之间的置信度.
			{
				double p_cur_for = GetP_Forward(curPos, poses[i + 1]);
				double p_for_cur = GetP_Backward(poses[i + 1], curPos);
				res += p_for_cur*p_cur_for;
			}
			else if (i == poses.size() - 1)//最后一个词性只考虑与倒数第二个之间的置信度.
			{
				double p_cur_back = GetP_Backward(curPos, poses[i - 1]);
				double p_back_cur = GetP_Forward(poses[i - 1], curPos);
				res += p_back_cur*p_cur_back;
			}
			else
			{
				res += ComputeP_GrammarLocal(curPos, poses[i + 1], poses[i - 1]);
			}
		}

		return res / poses.size();
	}

	void GrammarSet::InitializeWeights()
	{
		vector<Sen_Gra> samples = InputGraSamples(GetHopeLoveMindPath() + StringGrammar_InitialFilename);

		//Compute possibilities of grammar patterns and local grammar of each pattern.
		MyInt totalFreq = GetTotalFrequency();
		vector<double> localPVec;
		vector<double> patternPVec;
		for (unsigned int i = 0; i < samples.size(); ++i)
		{
			//Compute the possibility of local grammar.
			GrammarPattern pattern=LanguageFunc::ConvertToPattern(samples[i].gra);
			double localP = ComputeP_GrammarLocalAnalysis(pattern);
			localPVec.push_back(localP);

			//Compute the possibility of matched patterns.
			double patternP = ComputePossibilityGrammarPattern(pattern, totalFreq);
			patternPVec.push_back(patternP);
		}

		//Optimize <_wPattern> and <_wLocal> until possibility of each sample is close to 1.
		_wPattern = 0.5, _wLocal = 0.5;
		ComputeWeights(patternPVec, localPVec, _wPattern, _wLocal);

		WriteWeights(_wPattern, _wLocal);
	}

	void GrammarSet::WriteWeights(const double wPattern, const double wLocal)
	{
		string paramFile = GetHopeLoveMindPath() + "MindParam.txt";
		TiXmlDocument *myDocument = new TiXmlDocument(paramFile.c_str());
		myDocument->LoadFile();
		TiXmlNode *root = myDocument->FirstChild("Root");

		TiXmlNode *doubleParamNode = root->FirstChild("DoubleParam");
		TiXmlElement *wPatternNode = doubleParamNode->FirstChildElement("wPattern");
		TiXmlElement *wLocalNode = doubleParamNode->FirstChildElement("wLocal");

		if (wPatternNode == nullptr || wLocalNode == nullptr)
		{
			throw runtime_error("Error in ReadWeights: cannot write weights to file.");
		}

		wPatternNode->SetAttribute("value", to_string(wPattern).c_str() );
		wLocalNode->SetAttribute("value", to_string(wLocal).c_str());

		delete myDocument;
	}

	void GrammarSet::ReadWeights()
	{
		string paramFile = GetHopeLoveMindPath()+"MindParam.txt";
		TiXmlDocument *myDocument = new TiXmlDocument(paramFile.c_str());
		if (!myDocument->LoadFile())
		{
			cout << "Cannot read weights in GrammarSet" << endl;
			return;
		}
		TiXmlNode *root = myDocument->FirstChild("Root");

		TiXmlNode *doubleParamNode=root->FirstChild("DoubleParam");
		TiXmlElement *wPatternNode=doubleParamNode->FirstChildElement("wPattern");
		TiXmlElement *wLocalNode = doubleParamNode->FirstChildElement("wLocal");

		if (wPatternNode == nullptr || wLocalNode == nullptr)
		{
			throw runtime_error("Error in ReadWeights: cannot read weights from file.");
		}

		const char* wpatternStr=wPatternNode->Attribute("value");
		const char* wlocalStr = wLocalNode->Attribute("value");

		_wPattern= strtod(wpatternStr, NULL);
		_wLocal = strtod(wlocalStr, NULL);

		delete myDocument;
	}

	void GrammarSet::ReadGrammarLocal()
	{
		ifstream in(GetHopeLoveMindPath()+GrammarLocal_InitialFilename);
		if (!in)
		{
			LOG("Cannot find file: " + GrammarLocal_InitialFilename);
			return;
		}

		//The total POS for local grammar analysis is 15, including punctuations.
		int NUM_POS_FOR_LOCAL = NUM_PARTOFSPEECH+3;

		//Initialize each POS with GrammarLocal.
		map<PartOfSpeech, GrammarLocal> grammarLocalTable;
		for (int i = 0; i < NUM_POS_FOR_LOCAL; ++i)
		{
			shared_ptr<GrammarLocal> grammarLocal ( new GrammarLocal(PartOfSpeech(i)));
			grammarLocal->Read(in);
			_grammarLocalTable[PartOfSpeech(i)] = grammarLocal;
		}


	}

	void GrammarSet::ComputeWeights(const vector<double>& patternP, const vector<double>& localP,
		double& wPattern, double& wLocal) const
	{
		double gradPattern, gradLocal;
		double deltaStep = 1e-4;
		double divergeTol = 1e-5;
		int iterCount = 0;
		int maxIterCount = 10000;
		do 
		{
			double dev = ComputeDeviation(patternP, localP, wPattern, wLocal);
			//Numerically compute the gradient of each weight.
			double deltaPattern= ComputeDeviation(patternP, localP, wPattern+ deltaStep, wLocal)-dev;
			double deltaLocal = ComputeDeviation(patternP, localP, wPattern , wLocal + deltaStep) - dev;
			gradPattern = deltaPattern / deltaStep;
			gradLocal = deltaLocal / deltaStep;

			//Adjust each weight simply by gradient.
			wPattern -= gradPattern;
			wLocal -= gradLocal;

			if (++iterCount > maxIterCount)
			{
				break;
			};

			//Iterate until both weights are not changed within tolerance.
		} while (Math::DoubleCompare(gradPattern,0,divergeTol)!=0 && Math::DoubleCompare(gradLocal, 0, divergeTol) != 0);

	}

	double GrammarSet::ComputeDeviation(const vector<double>& patternP, const vector<double>& localP,
		const double wPattern, const double wLocal) const
	{
		assert(patternP.size() == localP.size());

		double res = 0;
		for (unsigned int i=0;i<patternP.size();++i)
		{
			//Each element of <patternP> and the element in <localP> of the same index correspond to one grammar pattern.
			//Sum possibilities of each grammar patterns and compute the deviation from one.
			res += pow(patternP[i] * wPattern + localP[i] * wLocal-1,2);
		}

		//Normalize deviation.
		return res/patternP.size();
	}

	double GrammarSet::ComputePossibilityGrammarPattern(const GrammarPattern& pattern, const MyInt totalFreq) const
	{
		//Possibility equals the sum of ratio of each grammar pattern.
		//Therefore, possibility must be in the interval of 0 to 1.

		double sumFreq = 0.;
		vector<GrammarPattern> matchedPattern = ContainSubsequence(pattern);
		for (unsigned int j = 0; j < matchedPattern.size(); ++j)
		{
			MyInt curFreq ( GetFreqencyofPattern(matchedPattern[j]));
			sumFreq += curFreq / totalFreq;
		}

		return sumFreq;
	}

	double GrammarSet::ComputeP_GrammarLocal(const PartOfSpeech& curPos, const PartOfSpeech& forwardPos, const PartOfSpeech& backwardPos) const
	{
		double p_cur_for = GetP_Forward(curPos, forwardPos);
		double p_cur_back = GetP_Backward(curPos, backwardPos);
		double p_for_cur = GetP_Backward(forwardPos, curPos);
		double p_back_cur = GetP_Forward(backwardPos, curPos);


		return (p_cur_for*p_for_cur + p_cur_back*p_back_cur) / 2;
	}

	

}

