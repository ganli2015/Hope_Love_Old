#include "StdAfx.h"
#include "ConceptSet.h"
#include "../MindElement/BaseConcept.h"
#include "CommonFunction.h"
#include "../MindElement/ConceptInteractTable.h"
#include "ConceptSetInitializer.h"
#include "FindConnectConcept.h"
#include <fstream>
#include <deque>
#include <sstream>

#include "../CommonTools/IOFunction.h"
#include "../CommonTools/CommonStringFunction.h"

#include "../DataCollection/Character.h"
#include "../DataCollection/Word.h"
#include "../DataCollection/DataBaseProcessorTool.h"
#include "../DataCollection/CommonFunctions.h"

using namespace std;
using namespace DataCollection;

int ToInt(char str)
{
	return (int)str;
}

namespace Mind
{

	ConceptSet::ConceptSet(void)
	{
		Initialize();
	}


	ConceptSet::~ConceptSet(void)
	{
	}

	bool ConceptSet::IsConceptExist( const std::string str ) const
	{
		if(_conceptset.find(str)!=_conceptset.end())
			return true;
		else return false;
	}

	int ConceptSet::Count_ForwardAdjWord(const shared_ptr<DataCollection::Character> chara ) const
	{
		int count(0);

		string str=chara->GetString();
		const_conceptIter it=_conceptset.find(str);
		if(it==_conceptset.end())
			return count;//count =0
		else 
		{
			size_t step=_conceptset.count(str);
			advance(it,step);
			++count;
			if(it==_conceptset.end())
				return count;//count =1

			do 
			{
				string str_next=it->first;
				
				if(ToInt(str[0])==ToInt(str_next[0]) && ToInt(str[1])==ToInt(str_next[1]))
				{
					++count;
				}
				else
					break;

				step=_conceptset.count(str_next);
				advance(it,step);

			} while (it!=_conceptset.end());
		}

		return count;
	}

	int ConceptSet::Count_ForwardAdjWord(const shared_ptr<DataCollection::Word> word ) const
	{
		int count(0);

		string str=word->GetString();
		const_conceptIter it=_conceptset.find(str);
		if(it==_conceptset.end())
			return count;//count =0
		else 
		{
			size_t step=_conceptset.count(str);
			advance(it,step);//跳过相同的str
			++count;
			if(it==_conceptset.end())
				return count;//count =1

			do 
			{
				string str_next=it->first;//取下一个同根字符串

				if(str_next.size()<str.size())//默认长度是从小到大排列的
				{
					return count;
				}

				bool isAdj(true);//判断是否同根
				for (unsigned int i=0;i<str.size();++i)
				{
					if(str[i]!=str_next[i])
					{
						isAdj=false;
						break;
					}
				}

				if(!isAdj)//不是同根的话立即跳出
					break;
				else
				{
					++count;
				}
				
				step=_conceptset.count(str_next);
				advance(it,step);//跳过相同的str_next
			} while (it!=_conceptset.end());
		}

		return count;
	}

	void ConceptSet::GetForwardAdjWord(const shared_ptr<DataCollection::Character> chara,std::vector<std::string>& adjword ) const
	{
		shared_ptr<Word> aword(new Word(chara->GetString()));
		GetForwardAdjWord(aword,adjword);
	}

	void ConceptSet::GetForwardAdjWord(const shared_ptr<DataCollection::Word> word,std::vector<std::string>& adjword ) const
	{
		adjword.clear();

		string str=word->GetString();
		const_conceptIter it=_conceptset.find(str);
		if(it==_conceptset.end())
		{
			return;
		}

		int num=Count_ForwardAdjWord(word);
		for (int i=0;i<num;++i)
		{
			adjword.push_back(it->first);
			size_t step=_conceptset.count(it->first);
			advance(it,step);
		}
	}

	void ConceptSet::GetForwardAdjWord(const shared_ptr<DataCollection::Word> word,std::vector<DataCollection::Word>& adjword ) const
	{
		adjword.clear();

		string str=word->GetString();
		const_conceptIter it=_conceptset.find(str);
		if(it==_conceptset.end())
		{
			return;
		}

		int num=Count_ForwardAdjWord(word);
		for (int i=0;i<num;++i)
		{
			Word aword(it->first);
			adjword.push_back(aword);
			size_t step=_conceptset.count(it->first);
			advance(it,step);
		}
	}

	void ConceptSet::GetForwardAdjWord(const shared_ptr<DataCollection::Character> chara,std::vector<DataCollection::Word>& adjword ) const
	{
		shared_ptr<Word> aword(new Word(chara->GetString()));
		GetForwardAdjWord(aword,adjword);
	}

	int ConceptSet::MaxLength_AdjacentWord(const shared_ptr<DataCollection::Character> chara ) const
	{
		shared_ptr<Word> aword(new Word(chara->GetString()));
		int length=MaxLength_AdjacentWord(aword);
		return length;
	}

	int ConceptSet::MaxLength_AdjacentWord(const shared_ptr<DataCollection::Word> word ) const
	{
		vector<Word> adjword;
		GetForwardAdjWord(word,adjword);
		int maxLength(0);
		for (unsigned int i=0;i<adjword.size();++i)
		{
			int curlength=adjword[i].NumOfChara();
			if(curlength>maxLength)
			{
				maxLength=curlength;
			}
		}

		return maxLength;
	}

	int ConceptSet::MaxLength_WordWithHead( const shared_ptr<DataCollection::Character> headChara ) const
	{
		int maxLength=0;
		string str=headChara->GetString();
		for (const_conceptIter it=_conceptset.begin();it!=_conceptset.end();++it)
		{
			string conceptStr=it->first;
			if(str[0]==conceptStr[0] && str[1]==conceptStr[1])//第一个字是否相同
			{
				int length=it->second->GetWord()->NumOfChara();
				if(length>maxLength)
				{
					maxLength=length;
				}
			}			
		}

		return maxLength;
	}

	void ConceptSet::Initialize()
	{
#ifdef _CheckInitialConceptData
		try
		{
			ConceptSetInitializer::CheckInitialConceptData();
		}
		catch(...)
		{
			system("pause");
		}
#endif

		ConceptSetInitializer::InitializeBaseConcept(this,GetHopeLoveMindPath()+BaseConceptsStringFilename);

		ConceptSetInitializer::InitializeNonBaseConcept(this,GetHopeLoveMindPath()+NonBaseConceptString_InitialFilename);

		ConceptSetInitializer::InitializeConceptConnection(this,GetHopeLoveMindPath()+ConceptConnections_InitialFilename);
	}

	std::vector<shared_ptr<DataCollection::Word>> ConceptSet::GetAllKindsofWord(const shared_ptr<DataCollection::Word> word) const
	{
		string str=word->GetString();
		const_conceptIter it=_conceptset.find(str);
		
		vector<shared_ptr<Word>> rep;
		if(it==_conceptset.end())
		{
			return rep;
		}

		const_conceptIter beg=_conceptset.lower_bound(str);
		const_conceptIter end=_conceptset.upper_bound(str);
		while(beg!=end)
		{
			shared_ptr<Word> aword=DataBaseProcessorTool::GetParticularWord(str,beg->second->GetPartOfSpeech());
			if(aword!=NULL)
			{
				rep.push_back(aword);
			}
			beg++;
		}

		return rep;
	}

	vector<shared_ptr<iConcept>> ConceptSet::SearchForwardConcepts( const shared_ptr<iConcept> concept ) const
	{
		shared_ptr<Concept> myConcept=GetConceptRef(concept);
		if(myConcept==NULL)
		{
			throw runtime_error("Error in SearchForwardConcepts");
		}

		FindConnectConcept findConnectConcept;
		return findConnectConcept.FindForward(myConcept);
	}

	vector<shared_ptr<iConcept>> ConceptSet::SearchBackwardConcepts( const shared_ptr<iConcept> concept ) const
	{
		shared_ptr<Concept> myConcept=GetConceptRef(concept);
		if(myConcept==NULL)
		{
			throw runtime_error("Error in SearchForwardConcepts");
		}

		FindConnectConcept findConnectConcept;
		return findConnectConcept.FindBackward(myConcept);
	}

	void ConceptSet::AddConcept(const shared_ptr<DataCollection::Word> word)
	{
		string str=word->GetString();
		if(_conceptset.find(str)==_conceptset.end())
		{
			_conceptset.insert(make_pair(str,shared_ptr<Concept>(new Concept(word))));
		}
		else//如果存在这个字符串的单词，判断是否已经存在该词性单词的Concept。
			//如果是，则抛出异常；否则新添加这个单词的Concept，其id为当前的最大id+1.
		{
			conceptIter beg=_conceptset.lower_bound(str);
			conceptIter end=_conceptset.upper_bound(str);
			int maxId(-1);
			while(beg!=end)
			{
				if(word->Type()==beg->second->GetPartOfSpeech())
				{
					throw runtime_error("Error in AddConcept:One POS of the word can only have one concept!");
				}

				int id=beg->second->GetId();
				if(id>maxId)
				{
					maxId=id;
				}
				beg++;
			}
			assert(maxId>=0);

			shared_ptr<Concept> newConcept(new Concept(word));
			newConcept->SetId(maxId+1);
			_conceptset.insert(make_pair(str,newConcept));
		}
	}

	void ConceptSet::AddConcept(const shared_ptr<DataCollection::Word> word,int id)
	{
		CheckWordIDExist(word,id,_conceptset);			

		shared_ptr<Concept> newConcept(new Concept(word));
		newConcept->SetId(id);
		string str=word->GetString();
		_conceptset.insert(make_pair(str,newConcept));

	}

	void ConceptSet::AddBaseConcept(const shared_ptr<DataCollection::Word> word,int id )
	{
		//Add to _baseConceptset
		CheckBaseWordIDExist(word,id,_baseConceptset);
		shared_ptr<BaseConcept> newConcept(new BaseConcept(word));
		newConcept->SetId(id);
		newConcept->SetBaseId(_baseConceptset.size());
		string str=word->GetString();
		_baseConceptset.insert(make_pair(str,newConcept));

		//Add to _conceptset
		CheckWordIDExist(word,id,_conceptset);
		_conceptset.insert(make_pair(str,newConcept));
	}

	void ConceptSet::MakeConnection( const shared_ptr<Word> from,const shared_ptr<Word> to )
	{
		Concept fromConcept,toConcept;
		if(!GetConcept(from,fromConcept) || !GetConcept(to,toConcept))
		{
			throw runtime_error("Error in MakeConnection: Cannot find the concept!");
		}

		if(from->Type()!=to->Type() && to->Type()!=Noun)
		{
			throw runtime_error("Error in MakeConnection: POS not matched!");
		}

		Identity fromIdentity=GetIdentity(fromConcept);
		Identity toIdentity=GetIdentity(toConcept);
		
		shared_ptr<Concept> pfromConcept=GetConceptRef(fromIdentity);
		shared_ptr<Concept> ptoConcept=GetConceptRef(toIdentity);
		pfromConcept->AddForwardConcept(ptoConcept);
		ptoConcept->AddBackwardConcept(pfromConcept);
	}

	void ConceptSet::AddModification(const shared_ptr<DataCollection::Word> from, const shared_ptr<DataCollection::Word> to,const shared_ptr<DataCollection::Word> modification )
	{
		shared_ptr<Concept> pfromConcept=GetConceptRef(from);
		shared_ptr<Concept> ptoConcept=GetConceptRef(to);
		shared_ptr<Concept> pmodConcept=GetConceptRef(modification);
		if(pfromConcept==NULL || ptoConcept==NULL || pmodConcept==NULL)
		{
			throw runtime_error("Error in MakeConnection: Cannot find the concept!");
		}

		pfromConcept->AddForwardModification(ptoConcept,pmodConcept);
		ptoConcept->AddBackwardModification(pfromConcept,pmodConcept);
	}

	bool ConceptSet::GetConcept( const Identity identity,Concept& concept ) const  
	{
		const_conceptIter beg=_conceptset.lower_bound(identity.str);
		const_conceptIter end=_conceptset.upper_bound(identity.str);
		if(beg==_conceptset.end() && end==_conceptset.end())
		{
			return false;
		}

		while(beg!=end)
		{
			if(beg->second->GetId()==identity.id)
			{
				concept=*beg->second;
				return true;
			}
			beg++;
		}

		return false;
	}

	bool ConceptSet::GetConcept( const shared_ptr<Word> word,Concept& concept ) const 
	{
		const_conceptIter beg=_conceptset.lower_bound(word->GetString());
		const_conceptIter end=_conceptset.upper_bound(word->GetString());
		if(beg==_conceptset.end() && end==_conceptset.end())
		{
			return false;
		}

		while(beg!=end)
		{
			if(beg->second->GetPartOfSpeech()==word->Type())
			{
				concept=*beg->second;
				return true;
			}
			beg++;
		}

		return false;
	}

	shared_ptr<Concept> ConceptSet::GetConceptRef(const shared_ptr<DataCollection::Word> word) const 
	{
		Concept toConcept;
		if(!GetConcept(word,toConcept))
		{
			return NULL;
		}

		Identity toIdentity=GetIdentity(toConcept);
		shared_ptr<Concept> ptoConcept=GetConceptRef(toIdentity);
		return ptoConcept;
	}

	shared_ptr<Concept> ConceptSet::GetConceptRef( const Identity identity ) const
	{
		const_conceptIter beg=_conceptset.lower_bound(identity.str);
		const_conceptIter end=_conceptset.upper_bound(identity.str);
		if(beg==_conceptset.end() && end==_conceptset.end())
		{
			return NULL;
		}

		while(beg!=end)
		{
			if(beg->second->GetId()==identity.id)
			{
				return beg->second;
			}
			beg++;
		}

		return NULL;
	}

	shared_ptr<Concept> ConceptSet::GetConceptRef(const shared_ptr<iConcept> concept) const 
	{
		Identity identity;
		identity.str=concept->GetString();
		identity.id=concept->GetId();

		return GetConceptRef(identity);
	}

	Mind::Identity ConceptSet::GetIdentity( const Concept& concept ) const
	{
		Identity res;
		res.str=concept.GetString();
		res.id=concept.GetId();
		return res;
	}

	shared_ptr<DataCollection::Word> ConceptSet::SearchWord( Identity identity )
	{
		shared_ptr<iConcept> concept_me=GetConceptPtr(identity);
		if(concept_me==NULL)
		{
			throw runtime_error("Error in BuildConceptConnection");
		}

		shared_ptr<Word> teset= concept_me->GetWord();

		return teset;
	}

	shared_ptr<iConceptInteractTable> ConceptSet::GetInteractTable( const shared_ptr<iConcept> from,const shared_ptr<iConcept> to,double level )
	{
		shared_ptr<iConceptInteractTable> res=from->InteractWith(to);
		
		for (int i=0;i<level;++i)
		{
			res->InteractDeeper();
		}

		return res;
	}

	shared_ptr<iConceptInteractTable> ConceptSet::GetDeepInteractTable( const shared_ptr<iConcept> from,const shared_ptr<iConcept> to )
	{
		shared_ptr<iConceptInteractTable> res=from->DeepInteractWith(to);

		return res;
	}

	vector<shared_ptr<DataCollection::Word>> ConceptSet::GetAllWordsOfPOS( const PartOfSpeech pos ) const
	{
		vector<shared_ptr<Word>> res;

		for (const_conceptIter iter=_conceptset.begin();iter!=_conceptset.end();++iter)
		{
			if(iter->second->GetPartOfSpeech()==pos)
			{
				res.push_back(iter->second->GetWord());
			}
		}

		return res;
	}

	void ConceptSet::CheckWordIDExist(const shared_ptr<DataCollection::Word> word, const int id,const ConceptMap& conceptset )
	{
		string str=word->GetString();
		const_conceptIter beg=conceptset.lower_bound(str);
		const_conceptIter end=conceptset.upper_bound(str);
		while(beg!=end)
		{
			if(word->Type()==beg->second->GetPartOfSpeech())
			{
				throw runtime_error("Error in AddConcept:One POS of the word can only have one concept!");
			}

			int id_exist=beg->second->GetId();
			if(id==id_exist)
			{
				throw logic_error("Error in AddConcept: id exists!");
			}
			beg++;
		}
	}

	void ConceptSet::CheckBaseWordIDExist(const shared_ptr<DataCollection::Word> word, const int id,const BaseConceptMap& conceptset )
	{
		string str=word->GetString();
		const_baseConceptIter beg=conceptset.lower_bound(str);
		const_baseConceptIter end=conceptset.upper_bound(str);
		while(beg!=end)
		{
			if(word->Type()==beg->second->GetPartOfSpeech())
			{
				throw runtime_error("Error in AddConcept:One POS of the word can only have one concept!");
			}

			int id_exist=beg->second->GetId();
			if(id==id_exist)
			{
				throw logic_error("Error in AddConcept: id exists!");
			}
			beg++;
		}
	}

	shared_ptr<BaseConcept> ConceptSet::GetBaseConcept( const int id ) const
	{
		for (const_baseConceptIter it=_baseConceptset.begin();it!=_baseConceptset.end();++it)
		{
			if(it->second->GetBaseId()==id)
			{
				return it->second;
			}
		}

		return NULL;
	}

	shared_ptr<iConcept> ConceptSet::GetConceptPtr( const shared_ptr<DataCollection::Word> word ) const
	{
		shared_ptr<Concept> ref=GetConceptRef(word);
		if(ref==NULL)
		{
			return NULL;
		}
		else
		{
			return ref->Copy();
		}
	}

	shared_ptr<iConcept> ConceptSet::GetConceptPtr( const Identity identity ) const
	{
		shared_ptr<Concept> ref=GetConceptRef(identity);
		if(ref==NULL)
		{
			return NULL;
		}
		else
		{
			return ref->Copy();
		}
	}

	void ConceptSet::OutputConceptData() const
	{

	}

	void ConceptSet::OutputNonBaseConcept() const
	{

	}

}

