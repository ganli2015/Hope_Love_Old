#include "StdAfx.h"
#include "ConceptSetInitializer.h"
#include "ConceptSet.h"
#include <fstream>

#include "../DataCollection/Word.h"
#include "../DataCollection/DataBaseProcessorTool.h"

using namespace DataCollection;

namespace Mind
{

	ConceptSetInitializer::ConceptSetInitializer(void)
	{
	}


	ConceptSetInitializer::~ConceptSetInitializer(void)
	{
	}

	void ConceptSetInitializer::InitializeNonBaseConcept( ConceptSet* conceptSet,const string filename_concept)
	{
		//建立独立的Concept
		class buildConcept
		{
			ConceptSet* _val;
		public: 
			buildConcept(ConceptSet* val):_val(val){};
			~buildConcept(){}

			void operator()(const Word_ID word_id)
			{
				shared_ptr<Word> word=word_id.word;
				string str=word->GetString();

				if(str.empty()) return;

				_val->AddConcept(word,word_id.id);

// 				if(str.size()>2)//insert guide word
// 				{
// 					string tmpstr("");
// 					tmpstr+=str[0];
// 					tmpstr+=str[1];
// 					if(_val->IsConceptExist(tmpstr))
// 					{
// 						return;
// 					}
// 					else
// 					{
// 						_val->AddConcept(shared_ptr<Word>(new Word(tmpstr)),-1);//导航词的id是-1
// 					}
// 
// 				}
			}

		};

		vector<Word_ID> totalConceptWords=InputWordFromFile(filename_concept);

		for_each(totalConceptWords.begin(),totalConceptWords.end(),buildConcept(conceptSet));
	}

	void ConceptSetInitializer::InitializeBaseConcept( ConceptSet* conceptSet,const string filename )
	{
		//建立独立的Concept
		class buildConcept
		{
			ConceptSet* _val;
		public: 
			buildConcept(ConceptSet* val):_val(val){};
			~buildConcept(){}

			void operator()(const Word_ID word_id)
			{
				shared_ptr<Word> word=word_id.word;
				string str=word->GetString();

				if(str.empty()) return;

				_val->AddBaseConcept(word,word_id.id);
			}
		};

		vector<Word_ID> baseConceptWords=InputWordFromFile(filename);

		for_each(baseConceptWords.begin(),baseConceptWords.end(),buildConcept(conceptSet));
	}

	void ConceptSetInitializer::InitializeConceptConnection( ConceptSet* conceptSet,string filename )
	{
		class BuildConceptConnection
		{
			ConceptSet* _val;
		public: 
			BuildConceptConnection(ConceptSet* val):_val(val){};
			~BuildConceptConnection(){};

			void operator()(const Connection_Info connection_info)
			{
				//找到当前单词对应的Word（含有词性）
				shared_ptr<Word> word_me=_val->SearchWord(connection_info.me);

				for (unsigned int i=0;i<connection_info.edge_infos.size();++i)
				{
					//找到依赖单词对应的Word（含有词性）
					shared_ptr<Word> word_to=_val->SearchWord(connection_info.edge_infos[i].to);

					_val->MakeConnection(word_me,word_to);
					//为每一个依赖单词添加修饰词
					for (unsigned int j=0;j<connection_info.edge_infos[i].modifications.size();++j)
					{
						shared_ptr<Word> word_mod=_val->SearchWord(connection_info.edge_infos[i].modifications[j]);

						_val->AddModification(word_me,
							word_to,
							word_mod);
					}
				}
			}
		};

		vector<Connection_Info> connections=CommonFunction::InputConnectionFromFile(filename);
		for_each(connections.begin(),connections.end(),BuildConceptConnection(conceptSet));
	}

	vector<ConceptSetInitializer::Word_ID> ConceptSetInitializer::InputWordFromFile( string filename )
	{
		ifstream in(filename);
		vector<Word_ID> words_id;
		while(!in.eof())
		{
			int id;
			string str;
			int POS;
			in>>id;
			in>>str;
			in>>POS;
			Word_ID word_id;
			word_id.id=id;
			word_id.word=DataBaseProcessorTool::GetParticularWord(str,PartOfSpeech(POS));
			words_id.push_back(word_id);

		}

		return words_id;
	}

	void ConceptSetInitializer::CheckInitialConceptData()
	{
		ofstream out("CheckInitialConceptData.txt");

		vector<Word_ID> nonBase_word_ids=InputWordFromFile(GetHopeLoveMindPath()+NonBaseConceptString_InitialFilename);
		vector<Connection_Info> connectionInfos=CommonFunction::InputConnectionFromFile(GetHopeLoveMindPath()+ConceptConnections_InitialFilename);
		vector<Word_ID> base_word_ids=InputWordFromFile(GetHopeLoveMindPath()+BaseConceptsStringFilename);
		vector<Word_ID> whole_word_ids=base_word_ids;whole_word_ids.insert(whole_word_ids.end(),nonBase_word_ids.begin(),nonBase_word_ids.end());

		CheckNonBaseConceptString(nonBase_word_ids,out);
		CheckConceptConnection(connectionInfos,whole_word_ids,base_word_ids,out);
		CheckBaseConcept(base_word_ids,nonBase_word_ids,out);
	}

	bool ConceptSetInitializer::ExistDuplicatedIDAndPOS(const Word_ID word_id,const int index,const vector<Word_ID>& list,Word_ID& duplicated)
	{
		for (unsigned int i=0;i<list.size();++i)
		{
			if(i==index) continue;

			if(word_id.word->GetString()==list[i].word->GetString())//找到相同字符串的词语
			{
				if(word_id.id==list[i].id || word_id.word->Type()==list[i].word->Type())
				{
					duplicated=list[i];
					return true;
				}
			}
		}

		return false;
	}

	bool ConceptSetInitializer::IdentityExist(const Identity identity,const vector<Word_ID>& list)
	{
		for (unsigned int i=0;i<list.size();++i)
		{
			if(list[i].id==identity.id && list[i].word->GetString()==identity.str)
			{
				return true;
			}
		}

		return false;
	}

	void ConceptSetInitializer::OutputWordID( const Word_ID w_i,std::ofstream& out )
	{
		cout<<w_i.id<<" "<<w_i.word->GetString()<<" "<<w_i.word->Type()<<" ";
	}

	void ConceptSetInitializer::OutputIdentity( const Identity identity,std::ofstream& out )
	{
		cout<<identity.id<<" "<<identity.str<<" ";
	}

	void ConceptSetInitializer::CheckNonBaseConceptString(const vector<Word_ID>& wholeConcepts, ofstream& out )
	{
		for (unsigned int i=0;i<wholeConcepts.size();++i)
		{
			Word_ID duplicated;
			if(ExistDuplicatedIDAndPOS(wholeConcepts[i],i,wholeConcepts,duplicated))
			{
				cout<<"ExistDuplicatedIDAndPOS:WholeConcept"<<endl;

				Word_ID cur=wholeConcepts[i];
				OutputWordID(cur,out);
				OutputWordID(duplicated,out);
				cout<<endl;

				throw runtime_error("CheckInitialConceptData");
			}
		}
	}

	void ConceptSetInitializer::CheckConceptConnection(const vector<Connection_Info>& connectionInfos, const vector<Word_ID>& wholeConcepts,const vector<Word_ID>& baseConcepts, ofstream& out )
	{
		//检查ConceptConnection里的concept是否存在于读取的word_id中。
		for (unsigned int i=0;i<connectionInfos.size();++i)
		{
			if(!IdentityExist(connectionInfos[i].me,wholeConcepts))
			{
				cout<<"Identity not Exist"<<endl;

				OutputIdentity(connectionInfos[i].me,out);

				throw runtime_error("CheckInitialConceptData");
			}

			//确保<me>不在base concepts中.
			if(IdentityExist(connectionInfos[i].me,baseConcepts))
			{
				cout<<"NonBase concept exists in base concepts!"<<endl;

				OutputIdentity(connectionInfos[i].me,out);

				throw runtime_error("CheckInitialConceptData");
			}


			//检查Edge
			for (unsigned int j=0;j<connectionInfos[i].edge_infos.size();++j)
			{
				if(!IdentityExist(connectionInfos[i].edge_infos[j].to,wholeConcepts))
				{
					cout<<"Identity not Exist"<<endl;

					OutputIdentity(connectionInfos[i].edge_infos[j].to,out);

					throw runtime_error("CheckInitialConceptData");
				}

				//检查Modification
				for (unsigned int k=0;k<connectionInfos[i].edge_infos[j].modifications.size();++k)
				{
					if(!IdentityExist(connectionInfos[i].edge_infos[j].modifications[k],wholeConcepts))
					{
						cout<<"Identity not Exist"<<endl;

						OutputIdentity(connectionInfos[i].edge_infos[j].modifications[k],out);

						throw runtime_error("CheckInitialConceptData");
					}

				}
			}

		}
	}

	void ConceptSetInitializer::CheckBaseConcept( const vector<Word_ID>& base,const vector<Word_ID>& nonBaseConcepts,ofstream& out )
	{
		for (unsigned int i=0;i<base.size();++i)
		{
			Word_ID duplicated;
			if(ExistDuplicatedIDAndPOS(base[i],i,base,duplicated))
			{
				cout<<"ExistDuplicatedIDAndPOS:BaseConcept"<<endl;

				Word_ID cur=base[i];
				OutputWordID(cur,out);
				OutputWordID(duplicated,out);
				cout<<endl;

				throw runtime_error("CheckInitialConceptData");
			}

			if(WordIDExist(base[i],nonBaseConcepts))
			{
				cout<<"WordID not Exist:BaseConcept"<<endl;

				Word_ID cur=base[i];
				OutputWordID(cur,out);
				cout<<endl;

				throw runtime_error("CheckInitialConceptData");
			}
		}


	}

	bool ConceptSetInitializer::WordIDExist( const Word_ID word_id,const vector<Word_ID>& list )
	{
		for (unsigned int i=0;i<list.size();++i)
		{
			if(list[i].id==word_id.id && list[i].word->IsSame(word_id.word))
			{
				return true;
			}
		}

		return false;
	}

}

