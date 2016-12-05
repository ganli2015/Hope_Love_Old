#pragma once
#include <string>
#include <vector>
#include <map>
#include <memory>

#include <HopeLoveAPI.h>

using namespace std;

const int NUM_PARTOFSPEECH=15;

class GrammarLocal
{

	//////////////////////////////////////////////////////////////////////////
	///POS of <me>
	//////////////////////////////////////////////////////////////////////////
	HopeLove::PartOfSpeech _pos;
	//////////////////////////////////////////////////////////////////////////
	///The distribution of frequencies of POS behind <me>.
	//////////////////////////////////////////////////////////////////////////
	map<HopeLove::PartOfSpeech, long> _forward;
	//////////////////////////////////////////////////////////////////////////
	///The distribution of frequencies of POS in front of <me>.
	//////////////////////////////////////////////////////////////////////////
	map<HopeLove::PartOfSpeech, long> _backward;

public:
	GrammarLocal() {};
	GrammarLocal(const HopeLove::PartOfSpeech myPos) :_pos(myPos)
	{
		for (int i = 0; i < NUM_PARTOFSPEECH; ++i)
		{
			_forward[HopeLove::PartOfSpeech(i)] = 0;
			_backward[HopeLove::PartOfSpeech(i)] = 0;
		}
	};
	~GrammarLocal() {};

	//////////////////////////////////////////////////////////////////////////
	///Add the frequency of POS in front of <me> by one.
	//////////////////////////////////////////////////////////////////////////
	void AddForward(const HopeLove::PartOfSpeech& pos) { ++_forward[pos]; };
	//////////////////////////////////////////////////////////////////////////
	///Add the frequency of POS behind <me> by one.
	//////////////////////////////////////////////////////////////////////////
	void AddBackward(const HopeLove::PartOfSpeech& pos) { ++_backward[pos]; };

	void Output(ofstream& out) const;

};

class GrammarLocalDistributionExtractor
{
	map<HopeLove::PartOfSpeech, shared_ptr<GrammarLocal>> _grammarLocalTable;

public:
	GrammarLocalDistributionExtractor();
	~GrammarLocalDistributionExtractor();

	void Run();

private:

	void BuildLocalTable();

	void OutputLocalTable() const;
};

