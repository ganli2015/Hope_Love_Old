#pragma once
#include "InOut.h"

namespace DataCollection
{
	class DataBase;
}

namespace DataWrapperCPP
{
	template class _DATAWRAPPERINOUT std::allocator<std::string>;
	template class _DATAWRAPPERINOUT std::vector<std::string,std::allocator<char*> >;
	class  _DATAWRAPPERINOUT DataWrapper
	{
		std::vector<std::string>  _inputsentences;
		std::vector<std::string>  _outputsentences;
		

	public:
		DataWrapper(void);
		~DataWrapper(void);

		void AddInputSentence(std::string asentence);
		void AddOutputSentence(std::string asentence);
		std::string GetNewSentence();
		std::string GetInputSentence();
	};
}


