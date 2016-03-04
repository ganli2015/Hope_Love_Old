#include "StdAfx.h"
#include "TestGramma.h"
#include "../CommonTools/IOFunction.h"
#include "../Mathmatic/Vector.h"
#include "MathTool.h"
#include "CompetitiveNetwork.h"
#include "Neuron_compet.h"
#include "FindSequence.h"
#include "GrammardSentence.h"
#include "Word.h"
#include "GrammaPattern.h"
#include "DataBaseProcessorTool.h"

using namespace std;
using namespace Math;
using namespace CommonTool;
using namespace NeuralNetwork;
using namespace DataCollection;
int num_speech(12);
struct sen_gra
{
	string str;
	vector<int> gra;
	Vector graVec;
	shared_ptr<Vector> patternVec;
	sen_gra():graVec(num_speech)
	{

	}
};

// vector<vector<int>> InputGraSamples(string file)
// {
// 	vector<vector<int>> res;
// 
// 	ifstream in(file);
// 	istream_iterator<int> file_it(in);
// 	
// 	while(file_it!=istream_iterator<int>())
// 	{
// 		int count=*file_it;
// 		file_it++;
// 		vector<int> array;
// 		for (int i=1;i<=count;++i)
// 		{
// 			array.push_back(*file_it++);
// 
// 		}
// 		res.push_back(array);
// 	}
// 
// 
// 	return res;
// }

vector<sen_gra> InputGraSamples(string file)
{
	vector<sen_gra> samples;

	ifstream in(file);

	while(!in.eof())
	{
		sen_gra sample;

		//read string
		string str;
		in>>str;
		sample.str=str;

		int count;
		in>>count;
		Vector array(num_speech);
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
		sample.graVec=array;
		samples.push_back(sample);
	}

	return samples;
}

Test_Gramma::Test_Gramma(void)
{
}


Test_Gramma::~Test_Gramma(void)
{
}

bool gra_sort(const sen_gra& left,const sen_gra& right)
{
	shared_ptr<Vector> vec1=left.patternVec;
	shared_ptr<Vector> vec2=right.patternVec;
	int row1,row2;

	for (unsigned int i=0;i<vec1->Dimension();++i)
	{
		if(DoubleCompare(vec1->Get_ithVal(i),1)==0)
		{
			row1=i;
			break;
		}
	}

	for (unsigned int i=0;i<vec2->Dimension();++i)
	{
		if(DoubleCompare(vec2->Get_ithVal(i),1)==0)
		{
			row2=i;
			break;
		}
	}

	if(row1<row2)
		return true;
	else return false;
}

int NonzeroRow(Vector vec)
{
	for (unsigned int i=0;i<vec.Dimension();++i)
	{
		if(DoubleCompare(vec.Get_ithVal(i),0)!=0)
		{
			return i;
		}
	}
	return -1;
}

void Test_Gramma::RunTest()
{
	//Test_Network();
	//Test_Subsequence();
	Test_GetIndexOfMatchedPattern();
	Test_BuildGrammarAssociation();
}

void Test_Gramma::Test_Network()
{
	vector<sen_gra> samples=InputGraSamples("str_sample.txt");

	//using competitive network
	int gra_degree(50);
	NeuralNetwork::CompetitiveNetwork comp_net(num_speech,gra_degree);
	for (unsigned int i=0;i<samples.size();++i)
	{
		shared_ptr<iDataArray> p(new DataArray(samples[i].graVec));
		comp_net.SetMyData(p);
	}

	Matrix mat(CreateRandomMatrix(num_speech,gra_degree));
	shared_ptr<iNeuron> neu(new Neuron_compet(mat));
	comp_net.SetMyNeuron(neu);

	comp_net.SetLearningRate(0.2);
	comp_net.SetMaxIterationCount(500);
	comp_net.Training();

	for (unsigned int i=0;i<samples.size();++i)
	{
		shared_ptr<iDataArray> p(new DataArray(samples[i].graVec));
		Vector r=comp_net.GetResult(p)->GetArray();
		r.Normalize();
		samples[i].patternVec=shared_ptr<Vector>(new Vector(r));
	}

	stable_sort(samples.begin(),samples.end(),gra_sort);

	ofstream out("catagory5.txt");

	for (unsigned int i=0;i<samples.size();++i)
	{
		out<<samples[i].str<<"  ";
		Vector vec=*samples[i].patternVec;
		out<<NonzeroRow(vec);
		out<<endl;
	}

	// 	ofstream out("catagory6.txt");
	// 
	// 	for (unsigned int i=0;i<samples.size();++i)
	// 	{
	// 		out<<samples[i].str<<"  ";
	// 		Vector vec=*samples[i].patternVec;
	// 		//vec=vec.Normalized();
	// 		double maxval(-1);
	// 		for (int i=0;i<vec.Dimension();++i)
	// 		{
	// 			out<<vec[i]<<" ";
	// 			if(vec[i]>maxval)
	// 				maxval=vec[i];
	// 		}
	// 		out<<"        "<<maxval;
	// 		out<<endl;
	// 	}
}

// bool comp_sequence(const vector<int>& left,const vector<int>& right)
// {
// 	if(left.size()!=right.size())
// 		return false;
// 
// 	for (unsigned int i=0;i<left.size();++i)
// 	{
// 		if(left[i]!=right[i])
// 			return false;
// 	}
// 	return true;
// }

class comp_sequence
{
	vector<int> _vec;
public:
	comp_sequence(const vector<int>& left):_vec(left){}
	~comp_sequence(){}

	bool operator() (const vector<int>& vec)
	{
		if(_vec.size()!=vec.size())
			return false;

		for (unsigned int i=0;i<_vec.size();++i)
		{
			if(_vec[i]!=vec[i])
				return false;
		}
		return true;
	}
};

void Test_Gramma::Test_Subsequence()
{
	vector<sen_gra> samples=InputGraSamples("str_sample.txt");
	
	std::vector<std::vector<int>> allcommon_seqs;
	for (unsigned int i=0;i<samples.size();++i)
	{
		vector<int> gra1=samples[i].gra;
		for (unsigned int j=i+1;j<samples.size();++j)
		{
			vector<int> gra2=samples[j].gra;
			std::vector<std::vector<int>> common_seqs;
			FindAllCommonSubsequence(gra1,gra2,common_seqs);
			allcommon_seqs.insert(allcommon_seqs.end(),common_seqs.begin(),common_seqs.end());
		}
	}

	//test distribution of grammar pattern
	struct pattern_distribution
	{
		vector<int> pattern;
		int count;
	};
	vector<pattern_distribution> p_d;
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
			pattern_distribution pd;
			pd.pattern=pattern;
			pd.count=1;
			p_d.push_back(pd);
		}
	}
	vector<int> counts;
	for (unsigned int i=0;i<p_d.size();++i)
	{
		counts.push_back(p_d[i].count);
	}


	vector<vector<int>> common_seq_unique;
	for (unsigned int i=0;i<allcommon_seqs.size();++i)
	{
		if(find_if(common_seq_unique.begin(),common_seq_unique.end(),comp_sequence(allcommon_seqs[i]))==common_seq_unique.end())
			common_seq_unique.push_back(allcommon_seqs[i]);
	}

	assert(common_seq_unique.size()==counts.size());
	ofstream out("..\\..\\Mind\\HopeLove\\GrammaPatterns.txt");
	out.clear();
	for (unsigned int i=0;i<common_seq_unique.size();++i)
	{
		vector<int> seq=common_seq_unique[i];
		out<<seq.size()<<" ";
		for (unsigned int j=0;j<seq.size();++j)
		{
			out<<seq[j]<<" ";
		}
		out<<counts[i]<<" ";
		out<<endl;
	}

}

void Test_Gramma::Test_GetIndexOfMatchedPattern()
{
// 	{
// 		GrammardSentence gs;
// 		vector<PartOfSpeech> pos;
// 		pos.push_back(PartOfSpeech(1));
// 		pos.push_back(PartOfSpeech(2));
// 		pos.push_back(PartOfSpeech(3));
// 		pos.push_back(PartOfSpeech(4));
// 		pos.push_back(PartOfSpeech(5));
// 		pos.push_back(PartOfSpeech(6));
// 		GrammarPattern raw(pos);
// 
// 		vector<PartOfSpeech> pos2;
// 		pos2.push_back(PartOfSpeech(2));
// 		pos2.push_back(PartOfSpeech(4));
// 		GrammarPattern pattern(pos2);
// 
// 		vector<vector<int>> indexes;
// 		gs.GetIndexOfMatchedPattern(raw,pattern,indexes);
// 	}
// 
// 	{
// 		GrammardSentence gs;
// 		vector<PartOfSpeech> pos;
// 		pos.push_back(PartOfSpeech(1));
// 		pos.push_back(PartOfSpeech(2));
// 		pos.push_back(PartOfSpeech(3));
// 		pos.push_back(PartOfSpeech(4));
// 		pos.push_back(PartOfSpeech(2));
// 		pos.push_back(PartOfSpeech(4));
// 		GrammarPattern raw(pos);
// 
// 		vector<PartOfSpeech> pos2;
// 		pos2.push_back(PartOfSpeech(2));
// 		pos2.push_back(PartOfSpeech(4));
// 		GrammarPattern pattern(pos2);
// 
// 		vector<vector<int>> indexes;
// 		gs.GetIndexOfMatchedPattern(raw,pattern,indexes);
// 	}
// 
// 	{
// 		GrammardSentence gs;
// 		vector<PartOfSpeech> pos;
// 		pos.push_back(PartOfSpeech(1));
// 		pos.push_back(PartOfSpeech(2));
// 		pos.push_back(PartOfSpeech(2));
// 		pos.push_back(PartOfSpeech(4));
// 		pos.push_back(PartOfSpeech(6));
// 		pos.push_back(PartOfSpeech(4));
// 		GrammarPattern raw(pos);
// 
// 		vector<PartOfSpeech> pos2;
// 		pos2.push_back(PartOfSpeech(2));
// 		pos2.push_back(PartOfSpeech(4));
// 		GrammarPattern pattern(pos2);
// 
// 		vector<vector<int>> indexes;
// 		gs.GetIndexOfMatchedPattern(raw,pattern,indexes);
// 	}
// 
// 	{
// 		GrammardSentence gs;
// 		vector<PartOfSpeech> pos;
// 		pos.push_back(PartOfSpeech(1));
// 		pos.push_back(PartOfSpeech(2));
// 		pos.push_back(PartOfSpeech(2));
// 		pos.push_back(PartOfSpeech(4));
// 		pos.push_back(PartOfSpeech(2));
// 		pos.push_back(PartOfSpeech(8));
// 		GrammarPattern raw(pos);
// 
// 		vector<PartOfSpeech> pos2;
// 		pos2.push_back(PartOfSpeech(2));
// 		pos2.push_back(PartOfSpeech(4));
// 		GrammarPattern pattern(pos2);
// 
// 		vector<vector<int>> indexes;
// 		gs.GetIndexOfMatchedPattern(raw,pattern,indexes);
// 	}
// 
// 	{
// 		GrammardSentence gs;
// 		vector<PartOfSpeech> pos;
// 		pos.push_back(PartOfSpeech(1));
// 		pos.push_back(PartOfSpeech(2));
// 		pos.push_back(PartOfSpeech(2));
// 		pos.push_back(PartOfSpeech(4));
// 		pos.push_back(PartOfSpeech(2));
// 		pos.push_back(PartOfSpeech(3));
// 		pos.push_back(PartOfSpeech(5));
// 		pos.push_back(PartOfSpeech(2));
// 		pos.push_back(PartOfSpeech(4));
// 		pos.push_back(PartOfSpeech(5));
// 		pos.push_back(PartOfSpeech(7));
// 		pos.push_back(PartOfSpeech(9));
// 		pos.push_back(PartOfSpeech(5));
// 		pos.push_back(PartOfSpeech(1));
// 		pos.push_back(PartOfSpeech(3));
// 		pos.push_back(PartOfSpeech(2));
// 		pos.push_back(PartOfSpeech(5));
// 		pos.push_back(PartOfSpeech(7));
// 		pos.push_back(PartOfSpeech(8));
// 		GrammarPattern raw(pos);
// 
// 		vector<PartOfSpeech> pos2;
// 		pos2.push_back(PartOfSpeech(2));
// 		pos2.push_back(PartOfSpeech(4));
// 		pos2.push_back(PartOfSpeech(5));
// 		GrammarPattern pattern(pos2);
// 
// 		vector<vector<int>> indexes;
// 		gs.GetIndexOfMatchedPattern(raw,pattern,indexes);
// 	}
}

void Test_Gramma::Test_BuildGrammarAssociation()
{
	vector<PartOfSpeech> pos;
	pos.push_back(PartOfSpeech(1));
	pos.push_back(PartOfSpeech(2));
	pos.push_back(PartOfSpeech(2));
	pos.push_back(PartOfSpeech(4));
	pos.push_back(PartOfSpeech(2));
	pos.push_back(PartOfSpeech(3));
	pos.push_back(PartOfSpeech(5));
	pos.push_back(PartOfSpeech(2));
	pos.push_back(PartOfSpeech(4));
	pos.push_back(PartOfSpeech(5));
	vector<shared_ptr<Word>> words;
	for (unsigned int i=0;i<pos.size();++i)
	{
		words.push_back(DataBaseProcessorTool::GetParticularWord("ÎÒ",pos[i]));
	}

	vector<PartOfSpeech> pos1;
	pos1.push_back(PartOfSpeech(2));
	pos1.push_back(PartOfSpeech(4));
	vector<PartOfSpeech> pos2;
	pos2.push_back(PartOfSpeech(1));
	pos2.push_back(PartOfSpeech(2));
	pos2.push_back(PartOfSpeech(3));
	vector<PartOfSpeech> pos3;
	pos3.push_back(PartOfSpeech(3));
	pos3.push_back(PartOfSpeech(4));
	vector<PartOfSpeech> pos4;
	pos4.push_back(PartOfSpeech(4));
	pos4.push_back(PartOfSpeech(5));
	GrammarPattern pattern1(pos1);
	pattern1.SetID(0);
	GrammarPattern pattern2(pos2);
	pattern2.SetID(1);
	GrammarPattern pattern3(pos3);
	pattern3.SetID(2);
	GrammarPattern pattern4(pos4);
	pattern4.SetID(3);

	vector<GrammarPattern> patterns;
	patterns.push_back(pattern1);
	patterns.push_back(pattern2);
	patterns.push_back(pattern3);
	patterns.push_back(pattern4);

	GrammardSentence gs(words);
	gs.BuildGrammarAssociation(patterns);
	


}
