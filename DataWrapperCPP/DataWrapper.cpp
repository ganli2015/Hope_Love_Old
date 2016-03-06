#include "StdAfx.h"
#include "DataWrapper.h"
#include "../DataCollection/DataBase.h"

//test
#include "../DataCollection/DataBaseProcessorTool.h"
#include "../DataCollection/Sentence.h"


using namespace DataCollection;

using namespace std;

DataWrapperCPP::DataWrapper_Sentence::DataWrapper_Sentence(void)
{
	////test
	//string a("我是谁？");
	//vector<shared_ptr<Character>> charas=DataBaseProcessorTool::ConvertStringToCharacter(a);
}


DataWrapperCPP::DataWrapper_Sentence::~DataWrapper_Sentence(void)
{
}

void DataWrapperCPP::DataWrapper_Sentence::AddInputSentence( string asentence )
{
	//_inputsentences_str.push_back(asentence);

	InputSenInfo info;
	info.sentence_str=asentence;
	_inputsentences.push_back(info);
}


string DataWrapperCPP::DataWrapper_Sentence::GetNewOutSentence()
{
	if(_outputsentences.empty())
	{
		return "";
	}
	else
		return _outputsentences.back()->GetString();
}

string DataWrapperCPP::DataWrapper_Sentence::GetInputSentence()
{
	if(_inputsentences.empty())
	{
		return NULL;
	}
	else
		return _inputsentences.back().sentence_str;
}

void DataWrapperCPP::DataWrapper_Sentence::AddOutputSentence( std::string asentence )
{
	//_outputsentences_str.push_back(asentence);

	shared_ptr<Sentence> sen(new Sentence(asentence));
	_outputsentences.push_back(sen);
}

void DataWrapperCPP::DataWrapper_Sentence::AddParsedInputSentence( const vector<shared_ptr<DataCollection::Sentence>>& parsedSentence )
{
	if(parsedSentence.empty()) return;
	if(_inputsentences.empty()) return;

	class FindInputInfo
	{
		std::string _str;
	public: 
		FindInputInfo(const std::string str):_str(str){}
		~FindInputInfo(){}
		bool operator()(const InputSenInfo& info)
		{
			if(info.sentence_str==_str)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	};


	string rawStr=parsedSentence[0]->GetString();
	InputSenInfo lastInfo=_inputsentences.back();
	if(lastInfo.sentence_str==rawStr)//先判断最后一个是不是要找的
	{
		lastInfo.parsed.insert(lastInfo.parsed.end(),parsedSentence.begin(),parsedSentence.end());
		_inputsentences.back()=lastInfo;
	}
	else
	{
		vector<InputSenInfo>::iterator it=find_if(_inputsentences.begin(),_inputsentences.end(),FindInputInfo(rawStr));
		if(it==_inputsentences.end())
		{
			assert("Not Find InputInfo!!"&&false);
			return;
		}
		else
		{
			it->parsed.insert(it->parsed.end(),parsedSentence.begin(),parsedSentence.end());
		}
	}
}
