#pragma once
#include "InOut.h"

#include <iostream>

namespace DataCollection
{
	class Word;
}

namespace Mind
{
#define _CheckInitialConceptData

	class ConceptSet;
	struct Identity;
	struct Connection_Info;

	class ConceptSetInitializer
	{
		struct Word_ID
		{
			shared_ptr<DataCollection::Word> word;
			//����ͬһ�����ʵĲ�ͬ����.Ŀǰͬһ�����ʵ�ͬһ������ֻ��Ӧ��һ��id��
			//Ҳ����˵���id��ʱ�𲻵����ã�
			int id;
		};

	public:
		ConceptSetInitializer(void);
		~ConceptSetInitializer(void);

		static void InitializeNonBaseConcept(ConceptSet* conceptSet,const string filename_concept);

		static void InitializeBaseConcept(ConceptSet* conceptSet,const string filename);		

		static void InitializeConceptConnection(ConceptSet* conceptSet,string filename);

		static void CheckInitialConceptData();

	private:
		//��ʼ��ConceptSetʱʹ��
		static vector<Word_ID> InputWordFromFile( string filename );

		static void CheckConceptString(const vector<Word_ID>& wholeConcepts,ofstream& out);
		static void CheckConceptConnection(const vector<Connection_Info>& connectionInfos, const vector<Word_ID>& wholeConcepts, ofstream& out);
		static void CheckBaseConcept(const vector<Word_ID>& base,const vector<Word_ID>& wholeConcepts,ofstream& out);

		static bool ExistDuplicatedIDAndPOS(const Word_ID word_id,const int index,const vector<Word_ID>& list,Word_ID& duplicated);
		static void OutputWordID(const Word_ID w_i,std::ofstream& out);
		static void OutputIdentity( const Identity identity,std::ofstream& out );
		static bool IdentityExist(const Identity identity,const vector<Word_ID>& list);
		static bool WordIDExist(const Word_ID word_id,const vector<Word_ID>& list);

	};
}
