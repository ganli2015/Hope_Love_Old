#include "StdAfx.h"
#include "DataWrapper.h"
#include "../DataCollection/DataBase.h"

//test
#include "../DataCollection/DataBaseProcessorTool.h"
using namespace DataCollection;

using namespace std;

DataWrapperCPP::DataWrapper::DataWrapper(void)
{
	////test
	//string a("Œ“ «À≠£ø");
	//vector<shared_ptr<Character>> charas=DataBaseProcessorTool::ConvertStringToCharacter(a);
}


DataWrapperCPP::DataWrapper::~DataWrapper(void)
{
}

void DataWrapperCPP::DataWrapper::Add( string asentence )
{
	_inputsentences.push_back(asentence);
}


string DataWrapperCPP::DataWrapper::GetNewSentence()
{
	if(_outputsentences.empty())
		return string("");
	else
	return _outputsentences[_outputsentences.size()-1];
}

std::string DataWrapperCPP::DataWrapper::GetInputSentence()
{
	if(_inputsentences.empty())
		return string("");
	else
		return _inputsentences[_inputsentences.size()-1];
}
