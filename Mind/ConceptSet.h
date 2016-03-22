#pragma once
#include "InOut.h"
#include "Concept.h"
#include "CommonFunction.h"

namespace DataCollection
{
	class Character;
	class Word;
	enum PartOfSpeech;
}

namespace Mind
{
	class ConceptInteractTable;

	class _MINDINOUT ConceptSet
	{
		typedef std::multimap<std::string,shared_ptr<Concept>> ConceptMap;
		typedef std::multimap<std::string,shared_ptr<BaseConcept>> BaseConceptMap;
		ConceptMap _conceptset;
		BaseConceptMap _baseConceptset;

		typedef ConceptMap::iterator conceptIter;
		typedef ConceptMap::const_iterator const_conceptIter;
		typedef BaseConceptMap::iterator baseConceptIter;
		typedef BaseConceptMap::const_iterator const_baseConceptIter;
	public:
		ConceptSet(void);
		~ConceptSet(void);

	    bool IsConceptExist(const std::string str) const;
		//����word���һ��Concept��
		//�����������ַ����ĵ��ʣ��ж��Ƿ��Ѿ�������word������ͬ��Concept��
		//����ǣ����׳��쳣�����������������ʵ�Concept����idΪ��ǰ�����id+1.
		void AddConcept(const shared_ptr<DataCollection::Word> word);
		//����word���һ��Concept��
		//�����������ַ����ĵ��ʣ��ж��Ƿ��Ѿ�������word������ͬ��Concept��
		//����ǣ����׳��쳣�����������������ʵ�Concept����id�������ִ�id�ظ�.
		void AddConcept(const shared_ptr<DataCollection::Word> word,int id);
		//��word��Ӧ��conceptͬʱ��ӵ�_conceptset��_baseConceptset�С�
		void AddBaseConcept(const shared_ptr<DataCollection::Word> word,int id);
		//��<from>��<to>�������ӣ����߱�ʾ��ǰ�ߵĽ��͡�
		//��ǰֻ��Ϊһ��word��Ӧһ��Concept���������Բ�ͬ��word��ʹstring��ͬ��Ҳ��Ӧ����Concept
		//�ݶ����κδ��Ե�word��ֻ�ܺ������Լ�����������ͬ���Ե�word����
		void MakeConnection(const shared_ptr<DataCollection::Word> from,const shared_ptr<DataCollection::Word> to);
		//��from��to�����ӽ������δ�modification
		void AddModification(const shared_ptr<DataCollection::Word> from,const shared_ptr<DataCollection::Word> to,const shared_ptr<DataCollection::Word> modification);
		//���Conceptָ��Ŀ���������ֱ������˽�г�Ա��
		shared_ptr<Concept> GetConceptPtr(const shared_ptr<DataCollection::Word> word) const ;
		shared_ptr<Concept> GetConceptPtr(const Identity identity) const ;
		shared_ptr<BaseConcept> GetBaseConcept(const int id) const;
		shared_ptr<DataCollection::Word> SearchWord(const Identity identity);

		vector<shared_ptr<DataCollection::Word>> GetAllWordsOfPOS(const DataCollection::PartOfSpeech pos) const;

		int Count_ForwardAdjWord(const shared_ptr<DataCollection::Character> chara) const;
		int Count_ForwardAdjWord(const shared_ptr<DataCollection::Word> word) const;
		void GetForwardAdjWord(const shared_ptr<DataCollection::Character> chara,std::vector<std::string>& adjword) const;
		void GetForwardAdjWord(const shared_ptr<DataCollection::Word> word,std::vector<std::string>& adjword) const;
		void GetForwardAdjWord(const shared_ptr<DataCollection::Character> chara,std::vector<DataCollection::Word>& adjword) const;
		void GetForwardAdjWord(const shared_ptr<DataCollection::Word> word,std::vector<DataCollection::Word>& adjword) const;
		int MaxLength_AdjacentWord(const shared_ptr<DataCollection::Character> chara) const;
		int MaxLength_AdjacentWord(const shared_ptr<DataCollection::Word> word) const;
		int MaxLength_WordWithHead(const shared_ptr<DataCollection::Character> headChara) const;

		//��<_conceptset>���ҳ�<word>���ַ�����Ӧ�����д��Եĵ���
		std::vector<shared_ptr<DataCollection::Word>> GetAllKindsofWord(const shared_ptr<DataCollection::Word> word) const;

		vector<shared_ptr<Concept>> SearchForwardConcepts(const shared_ptr<Concept> concept) const;
		vector<shared_ptr<Concept>> SearchBackwardConcepts(const shared_ptr<Concept> concept) const;

		//�õ��໥���õ�����Concept�Ĺ�ϵ�����б�����໥���õ�ϸ�ڡ�
		//<from>��ʩ������<to>����������
		//���໥���ò�ͬ��ConceptEdge������ӣ�������ԭ�͵������ڴ��Ե����ӣ�
		//ǰ������ʱ�����ӣ������µ�����֪ʶ����
		shared_ptr<ConceptInteractTable> GetInteractTable(const shared_ptr<Concept> from,const shared_ptr<Concept> to,double level=0);
		shared_ptr<ConceptInteractTable> GetDeepInteractTable(const shared_ptr<Concept> from,const shared_ptr<Concept> to);

		int BaseConceptCount() const {return _baseConceptset.size();}

		void OutputConceptData() const;
	private:
		void Initialize();

		bool GetConcept(const shared_ptr<DataCollection::Word> word,Concept& concept) const;
		bool GetConcept(const Identity identity,Concept& concept) const;
		//���˽�г�Ա������
		shared_ptr<Concept> GetConceptRef(const shared_ptr<DataCollection::Word> word) const ;
		shared_ptr<Concept> GetConceptRef(const Identity identity) const ;
		shared_ptr<Concept> GetConceptRef(const shared_ptr<Concept> concept) const ;

		Identity GetIdentity(const Concept& concept) const;
		void CheckWordIDExist(const shared_ptr<DataCollection::Word> word,const int id,const ConceptMap& conceptset);
		void CheckBaseWordIDExist(const shared_ptr<DataCollection::Word> word, const int id,const BaseConceptMap& conceptset );

		vector<Concept> BreadthFirstSearch(const Identity identity) ;

		void OutputNonBaseConcept() const;
	};

	
}


