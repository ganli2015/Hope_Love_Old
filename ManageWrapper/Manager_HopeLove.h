#pragma once
#include "InOut.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace GlobalInterface;

namespace DataWrapperCPP
{
	class DataWrapper_Sentence;
}

namespace ManageWrapper
{
	public ref class Manager_HopeLove : public CPPManager
	{
		UIForm^ _form;

		DataWrapperCPP::DataWrapper_Sentence* _datawrappercpp;

	public:
		Manager_HopeLove(void);

		virtual void ConnectUI(UIForm^ form);

		virtual void Notify(DataWrapper^ data);

		virtual void Execute(DataWrapper^ data);

	private:

		void UpdateDataWrapperCPP(DataWrapper^ data);

		void UpdateDataWrapperCS(DataWrapper^ data);
	};
}


