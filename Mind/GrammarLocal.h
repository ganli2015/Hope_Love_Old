#pragma once
#include "InOut.h"
#include "../Mathmatic/MyInt.h"

#include "../DataCollection/Word.h"

namespace Mind
{
	//����ĳ�����Եľֲ�����.
	class GrammarLocal
	{
		DataCollection::PartOfSpeech _pos;//me�Ĵ���
		map<DataCollection::PartOfSpeech,Math::MyInt> _forward;//�ô��Ժ���һ������Ĵ��Էֲ�
		map<DataCollection::PartOfSpeech,Math::MyInt> _backward;//�ô���ǰ��һ������Ĵ��Էֲ�

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


