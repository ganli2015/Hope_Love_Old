#include "stdafx.h"
#include "TestSegmentation.h"
#include "CommonTools.h"

#include <HopeLoveAPI.h>

#include <iostream>



TestSegmentation::TestSegmentation()
{
}


TestSegmentation::~TestSegmentation()
{
}

void TestSegmentation::Run()
{
	//string filename = "dgk_shooter_z.conv";
	string filename = "corpus_de.txt";

	try
	{
		HopeLove::InitializeBrain("..\\Data\\");

	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}

	ofstream out("Incorrect segmentation.txt");

// 	string raw = "合金材、优质板分别增加２１．７％和２８％特别是市场紧俏的优质镀锌钢丝和镀锌钢丝绳分别比去年同期增长６０．８％和９４．８％，";
// 	vector<vector<string>> result2 = HopeLove::WordSegmentAll(raw.c_str(), HopeLove::ForwardSegment);


	int correctNum = 0;
	int totalNum = 0;
	vector<SentenceSample> samples = ReadSentences(filename);

	for (unsigned int i=0;i<samples.size();++i)
	{
		try
		{
			vector<vector<string>> result = HopeLove::WordSegmentAll(samples[i].raw.c_str(), HopeLove::BackwardSegment);
			if (IsCorrect(samples[i].segmented, result))
			{
				correctNum++;
			}
			else
			{
				OutputResult(samples[i].segmented, result, out);
			}

			++totalNum;
		}
		catch (const std::exception&)
		{
			continue;
		}
		
	}

	cout << "Correct Ratio: " << (double)correctNum / totalNum << endl;
	cout << "Total Number: " << totalNum << endl;
}


vector<TestSegmentation::SentenceSample> TestSegmentation::ReadSentences(const string filename)
{
	ifstream in("../Corpus/New/"+filename,ios::binary);
	if (!in)
	{
		throw runtime_error("File not found!");
	}

	vector<TestSegmentation::SentenceSample> res;

	int sampleNum = 10000;
	int maxLength = 180;
	size_t index = 2;
	while (!in.eof())
	{
		SentenceSample aSample;
		aSample.raw = CommonTools::Getline_UnicodeFile(in,index);
		aSample.segmented = CommonTools::Getline_UnicodeFile(in, index);

		//Too long or contains strange character.
		if (aSample.raw.size() > maxLength)
		{
			continue;
		}

		res.push_back(aSample);

		if (res.size() >= sampleNum)
		{
			break;
		}
	}

	return res;
}




bool TestSegmentation::IsCorrect(const string expect, const vector<string>& result)
{
	vector<string> expectSplit=CommonTools::SplitString(expect, '/');
	vector<string> expect_noBlank;
	for (unsigned int i=0;i<expectSplit.size();++i)
	{
		if (expectSplit[i] != "")
		{
			expect_noBlank.push_back(expectSplit[i]);
		}
	}


	if (expect_noBlank.size() != result.size())
	{
		return false;
	}

	for (unsigned int i=0;i<result.size();++i)
	{
		if (result[i] != expect_noBlank[i])
		{
			return false;
		}
	}

	return true;
}

bool TestSegmentation::IsCorrect(const string expect, const vector<vector<string>>& result)
{
	for (unsigned int i=0;i<result.size();++i)
	{
		if (IsCorrect(expect, result[i]))
		{
			return true;
		}
	}

	return false;
}

void TestSegmentation::OutputResult(const string expect, const vector<vector<string>>& results,ofstream& out)
{
	out << "Expect: " + expect << " Result: ";
	for (unsigned int i = 0; i < results.size(); ++i)
	{
		vector<string> result = results[i];
		for (unsigned int j = 0; j < result.size(); ++j)
		{
			out << result[j] ;
			if (j != result.size() - 1)
			{
				out << "/";
			}
		}
		out << " ";
	}
	out << endl;
}

