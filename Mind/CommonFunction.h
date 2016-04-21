#pragma once
#include "InOut.h"

#include "../MindElement/CommonFunction.h"

namespace DataCollection
{
	class Word;
	class GrammarPattern;
	enum PartOfSpeech;
}

namespace NeuralNetwork
{
	class iDataArray;
}

namespace Mind
{
	struct Edge_Info//��ʾ���ļ���ȡ��ConceptEdge����Ϣ
	{
		Identity to;
		vector<Identity> modifications;
	};
	struct Connection_Info
	{
		Identity me;
		vector<Edge_Info> edge_infos;
	};


	
	class ConceptSet;

	namespace CommonFunction
	{
		//��ʼ��ConceptSetʱʹ��
		vector<Connection_Info> InputConnectionFromFile(string filename);

		Identity TransformToIdentity(const string idStr,const string wordStr);

		shared_ptr<NeuralNetwork::iDataArray> ToDataArray(const shared_ptr<ConceptChain> chain, const ConceptSet* conceptSet);

		double _MINDINOUT ComputeP_GrammarLocalAnalysis(const DataCollection::GrammarPattern& pattern);

		//����<curPos>�����Ŷȣ���������������������<forwardPos>��<backwardPos>.
		double _MINDINOUT ComputeP_GrammarLocal(const DataCollection::PartOfSpeech& curPos,const DataCollection::PartOfSpeech& forwardPos,const DataCollection::PartOfSpeech& backwardPos);

		
	}
}


