#include "stdafx.h"
#include "TestPOSTagging.h"
#include "CommonTools.h"

#include <iostream>

TestPOSTagging::TestPOSTagging()
{
}


TestPOSTagging::~TestPOSTagging()
{
}

void TestPOSTagging::Run(const string corpusFilename)
{
	//Running too slow
	try
	{
		HopeLove::InitializeBrain("..\\Data\\");

	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}

	ofstream out("Incorrect posTagging.txt");

	auto samples = ReadSentences(corpusFilename);
	int correctNum = 0;
	int totalNum = 0;

	for (unsigned int i = 0; i < samples.size(); ++i)
	{
		try
		{
			auto result = HopeLove::POSTagging(samples[i].raw);
			if (IsCorrect(samples[i].POSTag, result))
			{
				correctNum++;
			}
			else
			{
				OutputResult(samples[i].POSUnsplit, result, out);
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

vector<TestPOSTagging::POSSample> TestPOSTagging::ReadSentences(const string filename)
{
	ifstream in(filename, ios::binary);
	if (!in)
	{
		throw runtime_error("File not found!");
	}

	vector<POSSample> res;

	int sampleNum = 10000;
	int maxLength = 180;
	size_t index = 2;
	while (!in.eof())
	{
		POSSample aSample;
		aSample.raw = CommonTools::Getline_UnicodeFile(in, index);
		string POSUnsplit = CommonTools::Getline_UnicodeFile(in, index);

		//Too long or contains strange character.
		if (aSample.raw.size() > maxLength)
		{
			continue;
		}

		aSample.POSUnsplit = POSUnsplit;
		aSample.POSTag = ParsePOSTagging(POSUnsplit);
		res.push_back(aSample);

		if (res.size() >= sampleNum)
		{
			break;
		}
	}

	return res;
}

vector<pair<string, HopeLove::PartOfSpeech>> TestPOSTagging::ParsePOSTagging(const string line)
{
	auto split = CommonTools::SplitString(line, ' ');

	vector<pair<string, HopeLove::PartOfSpeech>> res;

	for (unsigned int i=0;i<split.size();++i)
	{
		auto word_POS = CommonTools::SplitString(split[i], '/');
		if (word_POS.size() != 2)
		{
			throw runtime_error("Error in ParsePOSTagging");
		}

		res.push_back(make_pair(word_POS[0], (HopeLove::PartOfSpeech)atoi(word_POS[1].c_str())));
	}

	return res;
}

bool TestPOSTagging::IsCorrect(const vector<pair<string, HopeLove::PartOfSpeech>>& expect, const vector<pair<string, HopeLove::PartOfSpeech>>& result)
{
	if (expect.size() != result.size()) return false;

	for (unsigned int i = 0; i < expect.size(); ++i)
	{
		if (expect[i].first != result[i].first || expect[i].second != result[i].second)
		{
			return false;
		}
	}

	return true;
}

void TestPOSTagging::OutputResult(const string POSUnsplit, const vector<pair<string, HopeLove::PartOfSpeech>>& results, ofstream& out)
{
	out << "Expect: " + POSUnsplit << " Result: ";
	for (unsigned int i = 0; i < results.size(); ++i)
	{
		out << results[i].first << "/" << (int)results[i].second << " ";
	}
	out << endl;
}
