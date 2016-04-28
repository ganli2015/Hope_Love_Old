#pragma once
#include "InOut.h"

#include "../MindInterface/CommonFunction.h"

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
	struct Edge_Info//表示从文件读取的ConceptEdge的信息
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
		//初始化ConceptSet时使用
		vector<Connection_Info> InputConnectionFromFile(string filename);

		Identity TransformToIdentity(const string idStr,const string wordStr);

		shared_ptr<NeuralNetwork::iDataArray> ToDataArray(const shared_ptr<iConceptChain> chain, const ConceptSet* conceptSet);
		
	}
}


