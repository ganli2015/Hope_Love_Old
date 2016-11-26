#include "stdafx.h"
#include "GrammarPatternExtractor.h"

#include <Mathmatic/FindSequence.h>


GrammarPatternExtractor::GrammarPatternExtractor()
{
}


GrammarPatternExtractor::~GrammarPatternExtractor()
{
}


void GrammarPatternExtractor::Run()
{
	ExtractGrammarPatternFromInitialFile();
}

std::vector<std::vector<int>> GrammarPatternExtractor::FindAllCommonSequences(const vector<Sen_Gra>& samples) const
{
	std::vector<std::vector<int>> allcommon_seqs;
	for (unsigned int i = 0; i < samples.size(); ++i)
	{
		vector<int> gra1 = samples[i].gra;
		for (unsigned int j = i + 1; j < samples.size(); ++j)
		{
			try
			{
				vector<int> gra2 = samples[j].gra;
				std::vector<std::vector<int>> common_seqs;
				Math::FindAllCommonSubsequence(gra1, gra2, common_seqs);
				allcommon_seqs.insert(allcommon_seqs.end(), common_seqs.begin(), common_seqs.end());
			}
			catch (const std::exception& e)
			{
				cout << e.what() << endl;
				logfile << "Error in FindAllCommonSubsequence. List index1: " << i << ". List index2: " << j << endl;
			}
			
		}

		cout << i << endl;
	}

	return std::vector<std::vector<int>>();
}

vector<GrammarPatternExtractor::Pattern_Distribution> GrammarPatternExtractor::ComputePatternDistribution(const std::vector<std::vector<int>>& allcommon_seqs) const
{
	vector<Pattern_Distribution> p_d;
	for (unsigned int i = 0; i < allcommon_seqs.size(); ++i)
	{
		vector<int> pattern = allcommon_seqs[i];
		bool existed(false);
		for (unsigned int j = 0; j < p_d.size(); ++j)
		{
			vector<int> pattern2 = p_d[j].pattern;
			if (pattern == pattern2)
			{
				p_d[j].count++;
				existed = true;
				break;
			}
		}
		if (existed == false)
		{
			Pattern_Distribution pd;
			pd.pattern = pattern;
			pd.count = 1;
			p_d.push_back(pd);
		}
	}

	return p_d;
}

void GrammarPatternExtractor::OutputPatternDistribution(const vector<Pattern_Distribution>& p_d) const
{
	ofstream out("GrammaPatterns_Initial2.txt");
	out.clear();
	for (unsigned int i = 0; i < p_d.size(); ++i)
	{
		vector<int> seq = p_d[i].pattern;
		out << seq.size() << " ";
		for (unsigned int j = 0; j < seq.size(); ++j)
		{
			out << seq[j] << " ";
		}
		out << p_d[i].count << " ";
		out << endl;
	}

	out.close();
}

void GrammarPatternExtractor::OutputPatternDistribution(const unordered_map<string, int>& p_d) const
{
	ofstream out("GrammaPatterns_Initial2.txt");
	out.clear();
	for (unordered_map<string,int>::const_iterator it=p_d.begin();it!=p_d.end();++it)
	{
		out << it->first <<it->second<< endl;
	}

	out.close();

}

void GrammarPatternExtractor::ExtractGrammarPatternFromInitialFile() const
{
	vector<Sen_Gra> samples = InputGraSamples("sen_gra2.txt");

// 	std::vector<std::vector<int>> allcommon_seqs = FindAllCommonSequences(samples);
// 
// 	vector<Pattern_Distribution> p_d = ComputePatternDistribution(allcommon_seqs);
// 
// 	OutputPatternDistribution(p_d);

	unordered_map<string, int> allcommon_seqs= FindAllCommonSequencesAndDistribution(samples);

	OutputPatternDistribution(allcommon_seqs);
}

unordered_map<string, int> GrammarPatternExtractor::FindAllCommonSequencesAndDistribution(const vector<Sen_Gra>& samples) const
{
	unordered_map<string, int> res;

	for (unsigned int i = 0; i < samples.size(); ++i)
	{
		vector<int> gra1 = samples[i].gra;
		for (unsigned int j = i + 1; j < samples.size(); ++j)
		{
			try
			{
				vector<int> gra2 = samples[j].gra;
				std::vector<std::vector<int>> common_seqs;
				Math::FindAllCommonSubsequence(gra1, gra2, common_seqs);
				//Convert common sequences to strings, and make them keys in a map.
				vector<string> seqStrings=ConvertToStrings(common_seqs);

				for (unsigned int k=0;k<seqStrings.size();++k)
				{
					if (res.find(seqStrings[k]) == res.end())
					{
						//if not find the common sequence, create one.
						res[seqStrings[k]] = 1;
					}
					else
					{
						res[seqStrings[k]]++;
					}
				}
			}
			catch (const std::exception& e)
			{
				cout << e.what() << endl;
				logfile << "Error in FindAllCommonSubsequence. List index1: " << i << ". List index2: " << j << endl;
			}

		}

		cout << i << endl;
	}

	return res;
}

vector<string> GrammarPatternExtractor::ConvertToStrings(const vector<vector<int>>& commonSeq) const
{
	vector<string> res;
	for (unsigned int i=0;i<commonSeq.size();++i)
	{
		string seqStr = "";
		vector<int> oneSeq = commonSeq[i];
		for (unsigned int j=0;j<oneSeq.size();++j)
		{
			seqStr += to_string(oneSeq[j])+" ";
		}
		res.push_back(seqStr);
	}

	return res;
}

vector<GrammarPatternExtractor::Sen_Gra> GrammarPatternExtractor::InputGraSamples(string file) const
{
	vector<Sen_Gra> samples;

	ifstream in(file);
	if (!in) return samples;

	while (!in.eof())
	{
		Sen_Gra sample;

		int count;
		in >> count;
		vector<int> gra;
		gra.reserve(count);
		for (int i = 1; i <= count; ++i)
		{
			int elem;
			in >> elem;
			gra.push_back(elem);
		}

		sample.gra = gra;
		samples.push_back(sample);
	}

	return samples;
}