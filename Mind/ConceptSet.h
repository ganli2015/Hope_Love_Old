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
		//根据word添加一个Concept。
		//如果存在这个字符串的单词，判断是否已经存在与word词性相同的Concept。
		//如果是，则抛出异常；否则新添加这个单词的Concept，其id为当前的最大id+1.
		void AddConcept(const shared_ptr<DataCollection::Word> word);
		//根据word添加一个Concept。
		//如果存在这个字符串的单词，判断是否已经存在与word词性相同的Concept。
		//如果是，则抛出异常；否则新添加这个单词的Concept，其id不能与现存id重复.
		void AddConcept(const shared_ptr<DataCollection::Word> word,int id);
		//把word对应的concept同时添加到_conceptset和_baseConceptset中。
		void AddBaseConcept(const shared_ptr<DataCollection::Word> word,int id);
		//对<from>和<to>建立连接，后者表示对前者的解释。
		//当前只认为一个word对应一个Concept，两个词性不同的word即使string相同，也对应两个Concept
		//暂定：任何词性的word都只能和名词以及与其自身相同词性的word连接
		void MakeConnection(const shared_ptr<DataCollection::Word> from,const shared_ptr<DataCollection::Word> to);
		//对from和to的连接建立修饰词modification
		void AddModification(const shared_ptr<DataCollection::Word> from,const shared_ptr<DataCollection::Word> to,const shared_ptr<DataCollection::Word> modification);
		//获得Concept指针的拷贝，不是直接引用私有成员。
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

		//从<_conceptset>里找出<word>的字符串对应的所有词性的单词
		std::vector<shared_ptr<DataCollection::Word>> GetAllKindsofWord(const shared_ptr<DataCollection::Word> word) const;

		vector<shared_ptr<Concept>> SearchForwardConcepts(const shared_ptr<Concept> concept) const;
		vector<shared_ptr<Concept>> SearchBackwardConcepts(const shared_ptr<Concept> concept) const;

		//得到相互作用的两个Concept的关系表，该列表包含相互作用的细节。
		//<from>是施力方，<to>是受力方。
		//该相互作用不同于ConceptEdge里的连接，后者是原型的依存于大脑的连接，
		//前者是临时的连接（比如新的语句和知识）。
		shared_ptr<ConceptInteractTable> GetInteractTable(const shared_ptr<Concept> from,const shared_ptr<Concept> to,double level=0);
		shared_ptr<ConceptInteractTable> GetDeepInteractTable(const shared_ptr<Concept> from,const shared_ptr<Concept> to);

		int BaseConceptCount() const {return _baseConceptset.size();}

		void OutputConceptData() const;
	private:
		void Initialize();

		bool GetConcept(const shared_ptr<DataCollection::Word> word,Concept& concept) const;
		bool GetConcept(const Identity identity,Concept& concept) const;
		//获得私有成员的引用
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


