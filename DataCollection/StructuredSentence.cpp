#include "StdAfx.h"
#include "StructuredSentence.h"
#include "Word.h"
#include "DataBaseProcessorTool.h"

namespace DataCollection
{
	StructuredSentence::StructuredSentence(void)
	{
	}


	StructuredSentence::~StructuredSentence(void)
	{
	}

	StructuredSentence::StructuredSentence( const std::vector<shared_ptr<DataCollection::Word>>& vec):_sen(vec)
	{
		InitializeMatrix();
	}

	void StructuredSentence::InitializeMatrix()
	{
		_intensityMatrix.clear();
		unsigned int size=_sen.size();
		for (unsigned int i=0;i<size;++i)
		{
			vector<double> tmpVec(size,0);
			_intensityMatrix.push_back(tmpVec);
		}
	}

	void StructuredSentence::SetIntensity( const unsigned int i,const unsigned int j,double intensity )
	{
		if(i>=_intensityMatrix.size() || j>=_intensityMatrix.size())
		{
			throw out_of_range("i or j is out of the range!!");
		}
		_intensityMatrix[i][j]=intensity;
		_intensityMatrix[j][i]=intensity;
	}

	double StructuredSentence::GetIntensity( const unsigned int i,const unsigned int j )
	{
		if(i>=_intensityMatrix.size() || j>=_intensityMatrix.size())
		{
			throw out_of_range("i or j is out of the range!!");
		}

		return _intensityMatrix[i][j];
	}

}

