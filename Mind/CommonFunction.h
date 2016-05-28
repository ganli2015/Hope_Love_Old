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
	class ConceptSet;
	class iConceptInteractTable;

	struct Edge_Info//表示从文件读取的ConceptEdge的信息
	{
		Identity to;
		shared_ptr<iConceptInteractTable> modifications;
	};
	struct Connection_Info
	{
		Identity me;
		vector<Edge_Info> edge_infos;
	};


	

	namespace CommonFunction
	{
		Identity TransformToIdentity(const string idStr,const string wordStr);

		shared_ptr<NeuralNetwork::iDataArray> ToDataArray(const shared_ptr<iConceptChain> chain, const ConceptSet* conceptSet);
		
	}
}


