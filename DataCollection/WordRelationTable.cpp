#include "StdAfx.h"
#include "WordRelationTable.h"
#include "DataBaseProcessorTool.h"

namespace DataCollection
{
	WordRelationTable::WordRelationTable( void )
	{

	}

	WordRelationTable::~WordRelationTable( void )
	{

	}

	void WordRelationTable::Add( const shared_ptr<Word> from, const shared_ptr<Word> to )
	{
		int fromIndex=DataBaseProcessorTool::IndexOf(_words,from);
		int toIndex=DataBaseProcessorTool::IndexOf(_words,to);

		if(fromIndex==-1)//���û���ҵ�from������ӽ�������index��Ϊ������ĩβ
		{
			_words.push_back(from);
			fromIndex=_words.size()-1;
		}

		if(toIndex==-1)//ͬ��
		{
			_words.push_back(to);
			toIndex=_words.size()-1;
		}

		_relationIndex.insert(make_pair(fromIndex,toIndex));
	}

}
