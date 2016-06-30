#pragma once
#include "InOut.h"

namespace DataCollection
{
	class Sentence;
}

namespace DataWrapperCPP
{
	class  _DATAWRAPPERINOUT DataWrapper_Sentence
	{
	private:
		struct InputSenInfo
		{
			std::string sentence_str;
			std::shared_ptr<DataCollection::Sentence> parsed;
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
		void AddParsedInputSentence(const shared_ptr<DataCollection::Sentence>& parsedSentence);
	};
}


