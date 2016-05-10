#include "StdAfx.h"
#include "StructureAnalyzer.h"

#include "../DataCollection/Word.h"
#include "../DataCollection/Sentence.h"
#include "../DataCollection/GrammaPattern.h"
#include "../DataCollection/DataBaseProcessorTool.h"

#include "../MindInterface/iCerebrum.h"

using namespace DataCollection;

StructureAnalyzer::StructureAnalyzer( shared_ptr<DataCollection::Sentence> sen ):_raw_sen(sen)
{

}


StructureAnalyzer::~StructureAnalyzer(void)
{
}

bool StructureAnalyzer::Analyze()
{
	vector<vector<int>> tri_matrix;//���Ǿ��󣬼�¼����word���﷨ģʽ����Ƶ�ʣ��������������Ƶ�ʣ������Ǹ������Ǿ���
	for (unsigned int j=0;j<_raw_sen->GrammarWordCount();++j)
	{
		vector<vector<int>> associatedIndexes;
		vector<GrammarPattern> associatedPatterns;
		_raw_sen->GetAssociationInfo(j,associatedIndexes,associatedPatterns);
		vector<int> freqRow;
		for (unsigned int k=j+1;k<_raw_sen->GrammarWordCount();++k)
		{
			int totalFreq=TotalPatternFrequency2(j,k,associatedIndexes,associatedPatterns);
			freqRow.push_back(totalFreq);
		}
		tri_matrix.push_back(freqRow);
	}
	vector<vector<double>> normalizedMatrix=NormalizeFreqMatrix(tri_matrix);
	SetEachWordIntenstiy(normalizedMatrix);

	return true;
}

int StructureAnalyzer::TotalPatternFrequency( const int word1_index,const int word2_index,const vector<vector<int>>& word1_assoIndexes,const vector<DataCollection::GrammarPattern>& word1_assoPatterns )
{
	if(word1_assoIndexes.size()!=word1_assoPatterns.size())
	{
		throw logic_error("Error in TotalPatternFrequency");
	}

	Mind::iCerebrum *brain=Mind::iCerebrum::Instance();

	int totalFreq(0);
	for (unsigned int i=0;i<word1_assoIndexes.size();++i)
	{
		vector<int> assoIndexes=word1_assoIndexes[i];
		if(find(assoIndexes.begin(),assoIndexes.end(),word2_index)!=assoIndexes.end()) //���assoIndexes����word2_index����ͳ�����Ӧ���﷨ģʽ��Ƶ��
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

void StructureAnalyzer::SetEachWordIntenstiy( const vector<vector<double>>& triangleMatrix )
{
	for (unsigned int i=0;i<triangleMatrix.size();++i)
	{
		for (unsigned int j=0;j<triangleMatrix[i].size();++j)
		{
			_raw_sen->SetWordIntensity(i,i+j+1,triangleMatrix[i][j]);
		}
	}
}

int StructureAnalyzer::TotalPatternFrequency2( const int word1_index,const int word2_index,const vector<vector<int>>& word1_assoIndexes,const vector<DataCollection::GrammarPattern>& word1_assoPatterns )
{
	if(word1_assoIndexes.size()!=word1_assoPatterns.size())
	{
		throw logic_error("Error in TotalPatternFrequency");
	}

	Mind::iCerebrum *brain=Mind::iCerebrum::Instance();

	int totalFreq(0);
	for (unsigned int i=0;i<word1_assoIndexes.size();++i)
	{
		vector<int> assoIndexes=word1_assoIndexes[i];
		if(IsAdjacentInVec(word1_index,word2_index,assoIndexes))
		{
			int freq=brain->GetFreqencyofPattern(word1_assoPatterns[i]);
			totalFreq+=freq;
		}
	}
	return totalFreq;
}

bool StructureAnalyzer::IsAdjacentInVec( const int word1_index,const int word2_index,const vector<int>& vec )
{
	vector<int>::const_iterator iter1=find(vec.begin(),vec.end(),word1_index);
	vector<int>::const_iterator iter2=find(vec.begin(),vec.end(),word2_index);
	if(iter1==vec.end() || iter2==vec.end())
	{
		return false;
	}
	else if(distance(iter1,iter2)!=1)
	{
		return false;
	}
	else
	{
		return true;
	}
}
