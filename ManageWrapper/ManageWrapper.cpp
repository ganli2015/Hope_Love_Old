// 这是主 DLL 文件。

#include "stdafx.h"
#include <stddef.h>
#include <string>
#include "ManageWrapper.h"
#include "../DataCollection/DataBase.h"
#include "../DataWrapperCPP/DataWrapper.h"
#include "../CommandList/SpeakCommand.h"
#include "../Mind/Cerebrum.h"


using namespace std;
ManageWrapper::ManageClass::ManageClass():_datawrappercpp(new DataWrapperCPP::DataWrapper_Sentence()),
	_database(DataCollection::DataBase::GetInstance())
{
	Mind::Cerebrum::Instance();
}

ManageWrapper::ManageClass::~ManageClass()
{
	delete _datawrappercpp;
	_datawrappercpp=NULL;
}

void ManageWrapper::ManageClass::TransportDataFromCStoCPP()
{
	String^ sentence=this->inputsentence;
	IntPtr pString=Marshal::StringToHGlobalAnsi(sentence);
	
	char* pchString=static_cast<char*>(pString.ToPointer());
	string astring(pchString);
	_datawrappercpp->AddInputSentence(astring);
}

void ManageWrapper::ManageClass::UpdateCommand()
{
	TransportDataFromCStoCPP();
	Command* acommand=new SpeakCommand(_datawrappercpp);
	acommand->Update();
	TransportDataFromCPPtoCS();
}

void ManageWrapper::ManageClass::UpdateUI()
{
	NotifyObservers();
}

void ManageWrapper::ManageClass::TransportDataFromCPPtoCS()
{
	string newsen=_datawrappercpp->GetNewOutSentence();
	String^ anew=gcnew String(newsen.c_str());
	this->outputsentence=anew;
}


