#pragma once
#include "InOut.h"

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
	struct Identity
	{
		string str;
		//��ʾͬһ��string����Ӧ�Ĳ�ͬ��concept�������ʵ�id����-1��
		//Ŀǰͬһ�����ʵ�ͬһ������ֻ��Ӧ��һ��id��
		//Ҳ����˵���id��ʱ�𲻵����ã�
		int id;
	};

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


	class Concept;
	class ConceptInteractTable;
	class ConceptChain;
	class ConceptSet;

	namespace CommonFunction
	{
		//��ʼ��ConceptSetʱʹ��
		vector<Connection_Info> InputConnectionFromFile(string filename);

		Identity TransformToIdentity(const string idStr,const string wordStr);

		bool IsSameConcept(const shared_ptr<Concept> left,const shared_ptr<Concept> right);

		//���û���ҵ����򷵻�-1.
		int _MINDINOUT IndexOf(const vector<shared_ptr<Concept>>& concepts,const shared_ptr<Concept> concept);
		
		//��<from>��<to>�������໥���ö���ӵ�table
		void AppendToInteractTable(const vector<shared_ptr<Concept>>& from,const vector<shared_ptr<Concept>>& to,shared_ptr<ConceptInteractTable> table);
	
		void _MINDINOUT WriteConcepts(const vector<shared_ptr<Concept>>& vec,ofstream& out);

		shared_ptr<NeuralNetwork::iDataArray> ToDataArray(const shared_ptr<ConceptChain> chain, const ConceptSet* conceptSet);

		double _MINDINOUT ComputeP_GrammarLocalAnalysis(const DataCollection::GrammarPattern& pattern);

		//����<curPos>�����Ŷȣ���������������������<forwardPos>��<backwardPos>.
		double _MINDINOUT ComputeP_GrammarLocal(const DataCollection::PartOfSpeech& curPos,const DataCollection::PartOfSpeech& forwardPos,const DataCollection::PartOfSpeech& backwardPos);

		class _MINDINOUT SameConcept
		{
			shared_ptr<Concept> _me;
		public:
			SameConcept(const shared_ptr<Concept> val):_me(val){}
			~SameConcept(){}

			bool operator()(const shared_ptr<Concept> val);
		};
	}
}


