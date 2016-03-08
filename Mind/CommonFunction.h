#pragma once
#include "InOut.h"

namespace DataCollection
{
	class Word;
}

namespace NeuralNetwork
{
	class iDataArray;
}

namespace Mind
{
	struct Identity
	{
		string str;
		//表示同一个string所对应的不同的concept。引导词的id等于-1！
		//目前同一个单词的同一个词性只对应于一个id！
		//也就是说这个id暂时起不到作用！
		int id;
	};

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


	class Concept;
	class ConceptInteractTable;
	class ConceptChain;
	class ConceptSet;

	namespace CommonFunction
	{
		//初始化ConceptSet时使用
		vector<Connection_Info> InputConnectionFromFile(string filename);

		Identity TransformToIdentity(const string idStr,const string wordStr);

		bool IsSameConcept(const shared_ptr<Concept> left,const shared_ptr<Concept> right);

		//如果没有找到，则返回-1.
		int _MINDINOUT IndexOf(const vector<shared_ptr<Concept>>& concepts,const shared_ptr<Concept> concept);
		
		//把<from>和<to>的所有相互作用都添加到table
		void AppendToInteractTable(const vector<shared_ptr<Concept>>& from,const vector<shared_ptr<Concept>>& to,shared_ptr<ConceptInteractTable> table);
	
		void _MINDINOUT WriteConcepts(const vector<shared_ptr<Concept>>& vec,ofstream& out);

		shared_ptr<NeuralNetwork::iDataArray> ToDataArray(const shared_ptr<ConceptChain> chain, const ConceptSet* conceptSet);

	}
}


