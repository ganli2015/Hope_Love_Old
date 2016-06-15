#include "StdAfx.h"
#include "Manager_HopeLove.h"
#include "ConfigureManager.h"

#include "../DataWrapperCPP/DataWrapper.h"

#include "../CommandList/SpeakCommand.h"

#include "../CommonTools/MyObject.h"
#include "../CommonTools/LogWriter.h"

#include "../Mind/Cerebrum.h"

#include "../MindInterface/iCerebrum.h"

#include <string>

using namespace std;

namespace ManageWrapper
{

	Manager_HopeLove::Manager_HopeLove(void):_datawrappercpp(new DataWrapperCPP::DataWrapper_Sentence)
	{	
		ConfigureManager::Configure();
	}

	Manager_HopeLove::~Manager_HopeLove()
	{
		
	}

	void Manager_HopeLove::ConnectUI( UIForm^ form )
	{
		_form=form;
	}

	void Manager_HopeLove::Notify(DataWrapper^ data)
	{
		_form->UpdateUI(data);
	}

	void Manager_HopeLove::Execute( DataWrapper^ data )
	{
		CommonTool::LogWriter::ResetStartTime();

		UpdateDataWrapperCPP(data);

		LOG("Input sentence: "+_datawrappercpp->GetInputSentence());
		Command* acommand=new SpeakCommand(_datawrappercpp);
		acommand->Update();
		LOG("Output sentence: "+_datawrappercpp->GetNewOutSentence());

		UpdateDataWrapperCS(data);
		Notify(data);


		delete acommand;
	}

	void Manager_HopeLove::UpdateDataWrapperCPP( DataWrapper^ data )
	{
		String^ sentence=static_cast<String^>(data->GetData(DataType::InputString));
		if(sentence==nullptr)
		{
			_datawrappercpp->AddInputSentence("");
			return ;
		}

		IntPtr pString=Marshal::StringToHGlobalAnsi(sentence);

		char* pchString=static_cast<char*>(pString.ToPointer());
		string astring(pchString);
		_datawrappercpp->AddInputSentence(astring);
	}

	void Manager_HopeLove::UpdateDataWrapperCS( DataWrapper^ data )
	{
		string newsen=_datawrappercpp->GetNewOutSentence();
		String^ anew=gcnew String(newsen.c_str());
		data->SetData(DataType::OutputString,anew);
	}

	void Manager_HopeLove::Kill()
	{
		Mind::iCerebrum::KillInstance();
		delete _datawrappercpp;
	}

}
