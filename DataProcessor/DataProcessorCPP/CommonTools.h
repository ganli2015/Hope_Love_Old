#pragma once
#include <vector>
#include <string>

using namespace std;

class CommonTools
{
public:
	CommonTools();
	~CommonTools();

	static vector<string> SplitString(const string& str, const char splitTag);

	static string Getline_UnicodeFile(ifstream& fin, size_t& index);
};


static string rawdir = "../Corpus/Raw/";
static string newdir = "../Corpus/New/";

static string outdir = "../OutData/";

