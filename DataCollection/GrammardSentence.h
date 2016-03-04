#pragma once
#include "InOut.h"
#include "GrammaPattern.h"
#include <map>


namespace DataCollection
{
	class Word;

	class _DATACOLLECTIONINOUT GrammardSentence
	{
	public:
		struct GraAssoInfo
		{
			vector<int> indexes;//��ʾ��GrammarPattern����Ӧ�Ŀ��ܵ����У���ÿ��word���������ʾ
			GrammarPattern pattern;
		};

	private:
		std::vector<shared_ptr<DataCollection::Word>> _gra;
		multimap<int,GraAssoInfo> _graInfoSet; //int��ʾword��_gra�����ţ�GraAssoInfo�����˰�����word��GrammarPattern���Լ���GrammarPattern����Ӧ�Ŀ������С�
	public:
		GrammardSentence();
		~GrammardSentence();
		GrammardSentence(const std::vector<shared_ptr<DataCollection::Word>> vec);

		std::vector<shared_ptr<Word>> Get() const ; 
		int WordCount() const {return _gra.size();}

		bool BuildGrammarAssociation(const vector<GrammarPattern>& grammarPatterns);

		//������i��word���﷨ƥ����Ϣ��associatedIndexes���﷨ģʽƥ�����ż��ϣ�associatedPatterns����Ӧ��ģʽ������vectorһһ��Ӧ��
		void GetAssociationInfo(const unsigned int i,vector<vector<int>>& associatedIndexes,vector<GrammarPattern>& associatedPatterns);
	private:
		bool GetIndexOfMatchedPattern(const GrammarPattern& patternRaw,const GrammarPattern& patternMatch,vector<vector<int>>& indexes);
		void GetIndexOfMatchedPattern(const GrammarPattern& patternRaw,const GrammarPattern& patternMatch,const unsigned int rawStartIndex,const unsigned int matchStartIndex,vector<vector<int>>& indexes);
		void ClassifyGrammarInfoSet(multimap<int,GraAssoInfo>& graInfoSet,const vector<vector<int>>& indexes,const GrammarPattern& pattern);
	};
}

