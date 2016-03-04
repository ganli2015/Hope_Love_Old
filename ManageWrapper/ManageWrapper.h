// ManageWrapper.h

#pragma once
#include "InOut.h"

using namespace System;
using namespace DataWrapperCS;
using namespace System::Runtime::InteropServices;

namespace DataWrapperCPP
{
	class DataWrapper;
}

namespace DataCollection
{
	class DataBase;
}

namespace ManageWrapper
{
	public ref class ManageClass: public DataWrapperCS::DataWrapper
	{
		DataWrapperCPP::DataWrapper* _datawrappercpp;
		DataCollection::DataBase* _database;
	public:
		ManageClass();
		~ManageClass();

		void TransportDataFromCStoCPP();
		void TransportDataFromCPPtoCS();
		void UpdateCommand();
		void UpdateUI();
	};
}