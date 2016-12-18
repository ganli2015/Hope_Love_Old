#include "stdafx.h"
#include "GrammarSampleGenerator.h"
#include <HopeLoveAPI.h>

#include <fstream>
#include <algorithm>
#include <functional>
#include <iostream>

GrammarSampleGenerator::GrammarSampleGenerator()
{
}


GrammarSampleGenerator::~GrammarSampleGenerator()
{
}

void GrammarSampleGenerator::Run()
{
	vector<std::string> sentences = ReadValidSentence();

	POSTaggingAndOutput(sentences);

// 	std::vector<std::vector<std::string>> segSentences = SegmentSentences(sentences);
// 
// 	OutputGrammarData(segSentences);
}

std::vector<std::string> GrammarSampleGenerator::ReadValidSentence() const
{
	vector<std::string> res;

	string filename = "Conversation Sample.txt";
	ifstream in(filename);
	string line = "";
	while (getline(in,line))
	{
		if (line!="" && IsValid(line))
		{
			res.push_back(line);
		}
	}

	return res;
}

bool GrammarSampleGenerator::IsValid(const string line) const
{
	return line.size() % 2 == 0 && all_of(line.begin(), line.end(), bind2nd(less<int>(), 0));
}


void GrammarSampleGenerator::POSTaggingAndOutput(const vector<string>& sentences) const
{
	try
	{
		HopeLove::InitializeBrain("..\\Data\\");

	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}

	for (unsigned int i = 0; i < sentences.size(); ++i)
	{
		if (sentences[i] == "") continue;
		try
		{
			auto grammard = HopeLove::POSTagging(sentences[i]);
		}
		catch (const std::exception& e)
		{
			logfile << "Error sentence in word segment: " + sentences[i] << " Error is " << e.what() << endl;
		}
	}
}

std::vector<std::vector<std::string>> GrammarSampleGenerator::SegmentSentences(const vector<string>& sentences) const
{
	try
	{
		HopeLove::InitializeBrain("..\\Data\\");

	}
 	catch (const std::exception& e)
 	{
 		cout << e.what() << endl;
 	}


	std::vector<std::vector<std::string>> res;
	for (unsigned int i=0;i<sentences.size();++i)
	{
		if (sentences[i] == "") continue;
		try
		{
			res.push_back(HopeLove::WordSegment(sentences[i].c_str()));
		}
		catch (const std::exception& e)
		{
			logfile << "Error sentence in word segment: " + sentences[i] <<" Error is " <<e.what()<< endl;
		}
	}


	return res;
}

#include <time.h> 
void GrammarSampleGenerator::OutputGrammarData(const std::vector<std::vector<std::string>>& sentences) const
{
	ofstream out("str_sample2.txt");
	srand((unsigned)time(NULL));

	for (size_t i = 0; i < sentences.size(); i++)
	{
		std::vector<std::string> oneSentence = sentences[i];

		vector<HopeLove::PartOfSpeech> poses;

		try
		{

			for (size_t j = 0; j < oneSentence.size(); j++)
			{
				std::vector<HopeLove::PartOfSpeech> posOfWord = HopeLove::GetPartOfSpeech(oneSentence[j]);
				if (posOfWord.empty())
				{
					throw runtime_error("POS of "+oneSentence[j]+" is empty.");
				}
				int randIndex = rand() % (posOfWord.size());
				poses.push_back(posOfWord[randIndex]);
			}

		}
		catch (const std::exception& e)
		{
			logfile << "Error sentence index: " <<i<< " Error is " << e.what() << endl;
			continue;
		}

		out << oneSentence.size();

		for (size_t j = 0; j < poses.size(); j++)
		{
			out << " " << (int)poses[j];
		}

		out << endl;

	}

	HopeLove::DisposeBrain();

	out.close();

}


