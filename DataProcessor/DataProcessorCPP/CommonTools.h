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
};

