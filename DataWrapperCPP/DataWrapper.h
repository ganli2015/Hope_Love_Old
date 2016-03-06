#pragma once
#include "InOut.h"

namespace DataCollection
{
	class Sentence;
}

namespace DataWrapperCPP
{
	template class _DATAWRAPPERINOUT std::allocator<std::string>;
	template class _DATAWRAPPERINOUT std::vector<std::string,std::allocator<char*> >;
	class  _DATAWRAPPERINOUT DataWrapper_Sentence
	{
	private:
		struct InputSenInfo
		{
			std::string sentence_str;
			std::vector<shared_ptr<DataCollection::Sentence>> parsed;
		};

		std::vector<InputSenInfo> _inputsentences;
		std::vector<shared_ptr<DataCollection::Sentence>> _outputsentences;

	public:
		DataWrapper_Sentence(void);
		~DataWrapper_Sentence(void);

		void AddInputSentence(std::string asentence);
		void AddOutputSentence(std::string asentence);
		std::string GetNewOutSentence();
		std::string GetInputSentence();
		void AddParsedInputSentence(const std::vector<shared_ptr<DataCollection::Sentence>>& parsedSentence);
	};
}


