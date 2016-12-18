#include "stdafx.h"
#include "GrammarLocalDistributionExtractor.h"
#include "GrammarPatternExtractor.h"

GrammarLocalDistributionExtractor::GrammarLocalDistributionExtractor()
{
}


GrammarLocalDistributionExtractor::~GrammarLocalDistributionExtractor()
{
}

void GrammarLocalDistributionExtractor::Run(const string filename)
{
	BuildLocalTable(filename);

	OutputLocalTable();
}

void GrammarLocalDistributionExtractor::BuildLocalTable(const string filename)
{
	vector<GrammarPatternExtractor::Sen_Gra> samples = GrammarPatternExtractor::InputGraSamples(filename);
	if (samples.empty()) return;

	//Initialize each POS with GrammarLocal.
	map<HopeLove::PartOfSpeech, GrammarLocal> grammarLocalTable;
	for (int i = 0; i < NUM_PARTOFSPEECH; ++i)
	{
		_grammarLocalTable[HopeLove::PartOfSpeech(i)] = shared_ptr<GrammarLocal>(new GrammarLocal(HopeLove::PartOfSpeech(i)));
	}

	//Statistic the distribution of frequencies of POS from <samples>.
	for (unsigned int i = 0; i < samples.size(); ++i)
	{
		vector<int> gra = samples[i].gra;
		for (unsigned int j = 0; j < gra.size(); ++j)
		{
			if(gra.size()==1) continue;

			HopeLove::PartOfSpeech curPos = HopeLove::PartOfSpeech(gra[j]);
			if (j == 0)
			{
				_grammarLocalTable[curPos]->AddForward(HopeLove::PartOfSpeech(gra[j + 1]));
			}
			else if (j == gra.size() - 1)
			{
				_grammarLocalTable[curPos]->AddBackward(HopeLove::PartOfSpeech(gra[j - 1]));
			}
			else
			{
				_grammarLocalTable[curPos]->AddForward(HopeLove::PartOfSpeech(gra[j + 1]));
				_grammarLocalTable[curPos]->AddBackward(HopeLove::PartOfSpeech(gra[j - 1]));
			}
		}
	}
}

void GrammarLocalDistributionExtractor::OutputLocalTable() const
{
	string filename = "GrammarLocal_Initial2.txt";
	ofstream out(filename);

	for (map<HopeLove::PartOfSpeech, shared_ptr<GrammarLocal>>::const_iterator it = _grammarLocalTable.begin(); it != _grammarLocalTable.end(); ++it)
	{
		it->second->Output(out);
	}

	out.close();
}

void GrammarLocal::Output(ofstream& out) const
{
	out << (int)_pos;
	for (map<HopeLove::PartOfSpeech, long>::const_iterator it=_forward.begin();it!=_forward.end();++it)
	{
		out << " " << (int)it->second;
	}

	for (map<HopeLove::PartOfSpeech, long>::const_iterator it = _backward.begin(); it != _backward.end(); ++it)
	{
		out << " " << (int)it->second;
	}

	out << endl;
}
