#include "StdAfx.h"
#include "GrammarLocal.h"

#include "../DataCollection/GrammaPattern.h"
#include "../DataCollection/Word.h"

using namespace DataCollection;
using namespace Math;

namespace Mind
{


	GrammarLocal::GrammarLocal()
	{

	}

	GrammarLocal::GrammarLocal( const PartOfSpeech myPos ) :_pos(myPos)
	{
		for (int i=0;i<DataCollection::NUM_PARTOFSPEECH;++i)
		{
			_forward[PartOfSpeech(i)]=MyInt();
			_backward[PartOfSpeech(i)]=MyInt();
		}
	}

	GrammarLocal::~GrammarLocal()
	{

	}

	void GrammarLocal::AddForward( const PartOfSpeech& pos )
	{
		++_forward[pos];
	}

	void GrammarLocal::AddBackward( const PartOfSpeech& pos )
	{
		++_backward[pos];
	}

	double GrammarLocal::GetRatio_Forward( const DataCollection::PartOfSpeech& pos ) const
	{
		return _forward.at(pos)/TotalCount(_forward);
	}

	Math::MyInt GrammarLocal::TotalCount( const map<DataCollection::PartOfSpeech,Math::MyInt>& myMap ) const
	{
		MyInt res;
		for (map<PartOfSpeech,MyInt>::const_iterator it=myMap.begin();it!=myMap.end();++it)
		{
			res+=it->second;
		}

		return res;
	}

	double GrammarLocal::GetRatio_Backward( const DataCollection::PartOfSpeech& pos ) const
	{
		return _backward.at(pos)/TotalCount(_backward);
	}

}
