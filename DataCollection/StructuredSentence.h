#pragma once
#include "InOut.h"

namespace DataCollection
{
	class Word;

	class _DATACOLLECTIONINOUT StructuredSentence
	{
		std::vector<shared_ptr<DataCollection::Word>> _sen;
		vector<vector<double>> _intensityMatrix; //��¼����word����ǿ�ȵľ��󣬶ԳƵġ�
		bool _analyzed;

	public:
		StructuredSentence(void);
		~StructuredSentence(void);
		StructuredSentence(const std::vector<shared_ptr<DataCollection::Word>>& vec);

		//�趨��i��word�͵�j��word��intensity��
		void SetIntensity(const unsigned int i,const unsigned int j,double intensity);
		double GetIntensity(const unsigned int i,const unsigned int j);

		bool Analyzed() const {return _analyzed;}
	private: 
		void InitializeMatrix();
	};
}


