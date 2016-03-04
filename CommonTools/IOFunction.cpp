#include "StdAfx.h"
#include "IOFunction.h"
#include <fstream>
#include <iterator>

using namespace std;

namespace CommonTool
{
	std::vector<string> InputStringFromFile( std::string filename )
	{
		ifstream in(filename);
		istream_iterator<string> file_it(in);
		vector<string> out;
		copy(file_it,istream_iterator<string>(),back_inserter(out));
		return out;
	}
}

