#pragma once
#include "InOut.h"

namespace DataCollection
{
	class Word;

	class _DATACOLLECTIONINOUT StructuredSentence
	{
		std::vector<shared_ptr<DataCollection::Word>> _sen;
		vector<vector<double>> _intensityMatrix; //记录两两word连接强度的矩阵，对称的。
		bool _analyzed;

	public:
		StructuredSentence(void);
		~StructuredSentence(void);
		StructuredSentence(const std::vector<shared_ptr<DataCollection::Word>>& vec);

		//设定第i个word和第j个word的intensity。
		void SetIntensity(const unsigned int i,const unsigned int j,double intensity);
		double GetIntensity(const unsigned int i,const unsigned int j);

		bool Analyzed() const {return _analyzed;}
	private: 
		void InitializeMatrix();
	};
}


