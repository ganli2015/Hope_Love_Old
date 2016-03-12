#pragma once
#include "InOut.h"
#include "../Mathmatic/MyInt.h"

#include "../DataCollection/Word.h"

namespace Mind
{
	//储存某个词性的局部特征.
	class GrammarLocal
	{
		DataCollection::PartOfSpeech _pos;//me的词性
		map<DataCollection::PartOfSpeech,Math::MyInt> _forward;//该词性后面一个词语的词性分布
		map<DataCollection::PartOfSpeech,Math::MyInt> _backward;//该词性前面一个词语的词性分布

	public:
		GrammarLocal();
		GrammarLocal(const DataCollection::PartOfSpeech myPos);
		~GrammarLocal();

		void AddForward(const DataCollection::PartOfSpeech& pos);
		void AddBackward(const DataCollection::PartOfSpeech& pos);

		double GetRatio_Forward(const DataCollection::PartOfSpeech& pos) const;
		double GetRatio_Backward(const DataCollection::PartOfSpeech& pos) const;

	private:
		Math::MyInt TotalCount(const map<DataCollection::PartOfSpeech,Math::MyInt>& myMap) const;
	};
}


