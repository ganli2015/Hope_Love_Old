#include "StdAfx.h"
#include "PrepositionCollection.h"
#include <fstream>
using namespace std;
namespace DataCollection
{
	PrepositionCollection::PrepositionCollection(void)
	{
		Initialize();
	}


	PrepositionCollection::~PrepositionCollection(void)
	{
	}

	void PrepositionCollection::Initialize()
	{
// 		ifstream filename;
// 		filename.open("E:\\Artificial Intelligence\\Project\\Hope_Love\\DataCollection\\DataBase\\Preposition.txt");
// 		if (filename)
// 		{
// 
// 			while(!filename.eof())
// 			{
// 				string aword;
// 				filename>>aword;
// 				Word word(aword);
// 				long long index=word.ToInt();
// 				_prepositions.insert(make_pair(index,word));
// 			}
// 		}
// 		else assert(false&&"Preposition file is absent");
// 
// 		filename.close();
	}
}

