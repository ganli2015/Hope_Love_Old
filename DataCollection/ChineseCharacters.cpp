#include "StdAfx.h"
#include "Character.h"
#include "ChineseCharacters.h"
#include <fstream>
#include <assert.h>
#include <iterator>

using namespace std;

namespace DataCollection
{
	class input_chinesecharacters;
	class input_chinesecharacters
	{
		std::map<int,Character> _ccs;
	public:
		input_chinesecharacters():_ccs(){}
		~input_chinesecharacters(){}
		void operator()(string val)
		{
			if(val.empty()) return;
			if(val[0]>0) return;
			Character word(val);
			int index=word.ToInt();
			if(_ccs.find(index)==_ccs.end())
				_ccs[index]=word;
		}

		const std::map<int,Character>& GetResult(){return _ccs;}
	};
	ChineseCharacters::ChineseCharacters(void)
	{
		Initialize();
	}


	ChineseCharacters::~ChineseCharacters(void)
	{
	}

	void DataCollection::ChineseCharacters::Initialize()
	{
// 		ifstream filename("..\\..\\..\\DataCollection\\DataBase\\Chinese Characters.txt");
// 		istream_iterator<string> file_it(filename);
// 		input_chinesecharacters input=for_each(file_it,istream_iterator<string>(),input_chinesecharacters());
// 		_chinesecharacters=input.GetResult();
// 		filename.close();

	}

	Character DataCollection::ChineseCharacters::GetChara( int index )
	{
		if(_chinesecharacters.count(index)!=0)
			return _chinesecharacters[index];
		else
		{
			Character nullChara;
			return nullChara;
		}
	}

	
}

