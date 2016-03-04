#include "StdAfx.h"
#include "StructureAnalyzer.h"

#include "../DataCollection/Word.h"
#include "../DataCollection/Sentence.h"
#include "../DataCollection/GrammaPattern.h"
#include "../DataCollection/DataBaseProcessorTool.h"

#include "../Mind/Cerebrum.h"

using namespace DataCollection;

StructureAnalyzer::StructureAnalyzer( shared_ptr<DataCollection::Sentence> sen ):_raw_sen(sen)
{

}


StructureAnalyzer::~StructureAnalyzer(void)
{
}

bool StructureAnalyzer::Analyze()
{
	for (unsigned int i=0;i<_raw_sen->Count_Grammard();++i)
	{
		vector<vector<int>> tri_matrix;//三角矩阵，记录两两word的语法模式的总频率，不包含与自身的频率，所以是个上三角矩阵。
		for (unsigned int j=0;j<_raw_sen->GrammarWordCount(i);++j)
		{
			vector<vector<int>> associatedIndexes;
			vector<GrammarPattern> associatedPatterns;
			_raw_sen->GetAssociationInfo(i,j,associatedIndexes,associatedPatterns);
			vector<int> freqRow;
			for (unsigned int k=j+1;k<_raw_sen->GrammarWordCount(i);++k)
			{
				int totalFreq=TotalPatternFrequency(j,k,associatedIndexes,associatedPatterns);
				freqRow.push_back(totalFreq);
			}
			tri_matrix.push_back(freqRow);
		}
		vector<vector<double>> normalizedMatrix=NormalizeFreqMatrix(tri_matrix);
		SetEachWordIntenstiy(i,normalizedMatrix);
	}
	return true;
}

int StructureAnalyzer::TotalPatternFrequency( const int word1_index,const int word2_index,const vector<vector<int>>& word1_assoIndexes,const vector<DataCollection::GrammarPattern>& word1_assoPatterns )
{
	if(word1_assoIndexes.size()!=word1_assoPatterns.size())
	{
		throw logic_error("Error in TotalPatternFrequency");
	}

	Mind::Cerebrum *brain=Mind::Cerebrum::Instance();

	int totalFreq(0);
	for (unsigned int i=0;i<word1_assoIndexes.size();++i)
	{
		vector<int> assoIndexes=word1_assoIndexes[i];
		if(find(assoIndexes.begin(),assoIndexes.end(),word2_index)!=assoIndexes.end()) //如果assoIndexes包含word2_index，便统计相对应的语法模式的频率
		{
			int freq=brain->GetFreqencyofPattern(word1_assoPatterns[i]);
			totalFreq+=freq;
		}
	}
	return totalFreq;
}

vector<vector<double>> StructureAnalyzer::NormalizeFreqMatrix( const vector<vector<int>>& freqMatrix )
{
	double sum(0);
	for (unsigned int i=0;i<freqMatrix.size();++i)
	{
		for (unsigned int j=0;j<freqMatrix[i].size();++j)
		{
			sum+=(double)freqMatrix[i][j];
		}
	}

	vector<vector<double>> res;
	for (unsigned int i=0;i<freqMatrix.size();++i)
	{
		vector<double> row;
		for (unsigned int j=0;j<freqMatrix[i].size();++j)
		{
			row.push_back(freqMatrix[i][j]/sum);
		}
		res.push_back(row);
	}

	return res;
}

void StructureAnalyzer::SetEachWordIntenstiy(const int ith_gra, const vector<vector<double>>& triangleMatrix )
{
	for (unsigned int i=0;i<triangleMatrix.size();++i)
	{
		for (unsigned int j=0;j<triangleMatrix[i].size();++j)
		{
			_raw_sen->SetWordIntensity(ith_gra,i,i+j+1,triangleMatrix[i][j]);
		}
	}
}
