#include "StdAfx.h"
#include "Manager_HopeLove.h"

#include "../DataWrapperCPP/DataWrapper.h"

#include "../CommandList/SpeakCommand.h"

#include "../Mind/Cerebrum.h"

#include "../MindInterface/iCerebrum.h"

#include <string>

using namespace std;

namespace ManageWrapper
{
	Manager_HopeLove::Manager_HopeLove(void):_datawrappercpp(new DataWrapperCPP::DataWrapper_Sentence)
	{	
		Mind::iCerebrum::SetInstance(Mind::Cerebrum::Instance());
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
		UpdateDataWrapperCPP(data);
		Command* acommand=new SpeakCommand(_datawrappercpp);
		acommand->Update();
		UpdateDataWrapperCS(data);
		Notify(data);
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

}
