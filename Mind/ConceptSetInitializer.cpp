#include "StdAfx.h"
#include "ConceptSetInitializer.h"
#include "ConceptSet.h"
#include <fstream>

#include "../DataCollection/Word.h"
#include "../DataCollection/LanguageFunc.h"

#include "../MindInterface/iMindElementCreator.h"
#include "../MindInterface/iConceptInteractTable.h"

#include "../CommonTools/CommonStringFunction.h"

using namespace DataCollection;
using namespace Mind;

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
				Identity meID=connection_info.me;
				shared_ptr<Word> word_me=_val->SearchWord(meID);

				for (unsigned int i=0;i<connection_info.edge_infos.size();++i)
				{
					//找到依赖单词对应的Word（含有词性）
					Identity toID=connection_info.edge_infos[i].to;
					shared_ptr<Word> word_to=_val->SearchWord(toID);

					_val->MakeConnection(word_me,word_to);
					//Add modification table.
					shared_ptr<iConceptInteractTable> modTable=connection_info.edge_infos[i].modifications;
					if(modTable==NULL) continue;
					_val->AddModification(meID,toID,modTable);
				}
			}
		};

		vector<Connection_Info> connections=InputConnectionFromFile(filename,conceptSet);
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
			word_id.word=LanguageFunc::GetParticularWord(str,PartOfSpeech(POS));
			words_id.push_back(word_id);

		}

		return words_id;
	}

	void ConceptSetInitializer::CheckInitialConceptData(const ConceptSet* conceptSet)
	{
		ofstream out("CheckInitialConceptData.txt");

		vector<Word_ID> nonBase_word_ids=InputWordFromFile(GetHopeLoveMindPath()+NonBaseConceptString_InitialFilename);
		vector<Connection_Info> connectionInfos=InputConnectionFromFile(GetHopeLoveMindPath()+ConceptConnections_InitialFilename,conceptSet);
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
				shared_ptr<iConceptInteractTable> modTable=connectionInfos[i].edge_infos[j].modifications;
				if(modTable==NULL) continue;
				vector<MindType::ConceptPair> pairs=modTable->GetAllRelations();
				for (unsigned int k=0;k<pairs.size();++k)
				{
					Identity fromID=pairs[k].first->GetIdentity();
					Identity toD=pairs[k].second->GetIdentity();

					if(!IdentityExist(fromID,wholeConcepts))
					{
						cout<<"Identity not Exist"<<endl;

						OutputIdentity(fromID,out);

						throw runtime_error("CheckInitialConceptData");
					}
					if(!IdentityExist(toD,wholeConcepts))
					{
						cout<<"Identity not Exist"<<endl;

						OutputIdentity(toD,out);

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

	shared_ptr<iConceptInteractTable> ConceptSetInitializer::ParseStrToTable( const string str,const ConceptSet* conceptSet )
	{
		shared_ptr<Mind::iConceptInteractTable> res=iMindElementCreator::CreateConceptInteractTable(/*iMindElementCreator::ConceptInteractTable_IdentityBased*/);

		//split ','
		vector<string> pariStr=CommonTool::SplitString(str,',');
		for (unsigned int i=0;i<pariStr.size();++i)
		{
			//split '-'
			vector<string> fromTo=CommonTool::SplitString(pariStr[i],'-');
			Check(fromTo.size()==2);

			Identity idFrom=ParseStrToIdentity(fromTo[0]);
			shared_ptr<iConcept> from=conceptSet->GetConceptPtr(idFrom);

			Identity idTo=ParseStrToIdentity(fromTo[1]);
			shared_ptr<iConcept> to=conceptSet->GetConceptPtr(idTo);

			res->Add(from,to);
		}

		return res;
	}

	Mind::Identity ConceptSetInitializer::ParseStrToIdentity( const string str )
	{
		vector<string> w_i=CommonTool::SplitString(str,'@');
		Check(w_i.size()==2);

		Identity res;
		res.id=CommonTool::StrToInt(w_i[0]);
		res.str=w_i[1];

		return res;
	}

	vector<Connection_Info> ConceptSetInitializer::InputConnectionFromFile( string filename ,const ConceptSet* conceptSet)
	{
		ifstream in(filename);
		vector<Connection_Info> res;
		string str;
		while(getline(in,str))
		{
			Connection_Info connnection_info=ParseStrToConnectionInfo(str,conceptSet);

			res.push_back(connnection_info);
		}

		return res;
	}

	Mind::Connection_Info ConceptSetInitializer::ParseStrToConnectionInfo( const string line,const ConceptSet* conceptSet )
	{
		vector<string> split=CommonTool::SplitString(line,' ');

		if(split.size()<2)
		{
			throw logic_error("Error in InputConnectionFromFile");
		}

		Connection_Info connnection_info;
		//读取当前的word和id
		connnection_info.me=CommonFunction::TransformToIdentity(split[0],split[1]);

		if(split.size()==2)//没有ConceptEdge就继续下个循环
		{
			return connnection_info;
		}

		//读取Edge
		int index=2;//开始遍历后面的string
		while(true)
		{
			if(split[index]!="to")
			{
				throw runtime_error("Error in InputConnectionFromFile");
			}
			else
			{
				index++;
			}

			//读取依赖的word及其id
			Edge_Info edge_info;
			edge_info.to=CommonFunction::TransformToIdentity(split[index],split[index+1]);
			index+=2;

			if(split.begin()+index==split.end())
			{
				connnection_info.edge_infos.push_back(edge_info);
				break;
			}

			//读取修饰词
			vector<string>::iterator find_next_to=find(split.begin()+index,split.end(),"to");

			shared_ptr<iConceptInteractTable> modifications;
			if(IsConceptTableStr(split.begin()+index,split.end()))
			{
				modifications=ParseStrToTable(*(split.begin()+index),conceptSet);
			}
			else
			{
				modifications=ParseSingleMod(split.begin()+index,split.end(),edge_info.to,conceptSet);
			}
			edge_info.modifications=modifications;

			connnection_info.edge_infos.push_back(edge_info);

			if(find_next_to==split.end())
			{
				break;
			}

			index+=distance(split.begin()+index,find_next_to);//移动index到下一个to的位置。
		}

		return connnection_info;
	}

	shared_ptr<iConceptInteractTable> ConceptSetInitializer::ParseSingleMod( const vector<string>::iterator& beg,const vector<string>::iterator& end ,const Identity& toID,const ConceptSet* conceptSet)
	{
		if(distance(beg,end)%2!=0)//string的个数必须是偶数，因为word和id总是成对出现
		{
			throw runtime_error("Error in InputConnectionFromFile");
		}
		shared_ptr<iConceptInteractTable> res= iMindElementCreator::CreateConceptInteractTable(/*iMindElementCreator::ConceptInteractTable_IdentityBased*/);
		shared_ptr<iConcept> to=conceptSet->GetConceptPtr(toID);

		for (vector<string>::iterator it=beg;it!=end;it+=2)
		{
			Identity modID=CommonFunction::TransformToIdentity(*it,*(it+1));
			shared_ptr<iConcept> mod=conceptSet->GetConceptPtr(modID);
			res->Add(mod,to);
		}

		return res;
	}

	bool ConceptSetInitializer::IsConceptTableStr( const vector<string>::iterator& beg,const vector<string>::iterator& end )
	{
		if(distance(beg,end)==1 && beg->find('-')!=string::npos)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

}

