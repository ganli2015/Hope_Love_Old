#pragma once
#include "InOut.h"
#include <utility>

namespace DataCollection
{
	class Word;
	class GrammarPattern;
	class Character;
	class Punctures;
	enum PartOfSpeech;
	class _DATACOLLECTIONINOUT LanguageFunc
	{

		static shared_ptr<Punctures> _punctures;
	public:
		LanguageFunc(void);
		~LanguageFunc(void);

	//puncture
		static bool IsPuncEndofSentence(shared_ptr<Character> val);
		static bool IsPuncRightside(shared_ptr<Character> val); 
		//Cutter sentence to two part:sentence with no punctures and punctures.(Only support for sentence with punctures in the end)
		static pair<vector<shared_ptr<Character>>,vector<shared_ptr<Character>>> TrimEndPunctures(const vector<shared_ptr<Character>>& raw);
		static pair<vector<Character>,vector<Character>> TrimEndPunctures(const vector<Character>& raw);

	//character
		static std::vector<shared_ptr<Character>> ConvertStringToCharacter(std::string str);
		static std::string ConvertCharacterToString(std::vector<shared_ptr<Character>> charas);

	//word
		static shared_ptr<DataCollection::Word> GetParticularWord(const std::string str, const DataCollection::PartOfSpeech partofspeech );
		static vector<shared_ptr<Word>> ConvertPuncturesToWords(const vector<Character>& puncs);
		static pair<vector<shared_ptr<Word>>,vector<shared_ptr<Word>>> TrimEndPunctures(const vector<shared_ptr<Word>>& raw);
		static pair<vector<Word>,vector<Word>> TrimEndPunctures(const vector<Word>& raw);
		//如果没有找到，则返回-1.
		static int IndexOf(const vector<shared_ptr<Word>>& words,const shared_ptr<Word> word);
		static vector<shared_ptr<Word>> RemovePuncs(const vector<shared_ptr<Word>>& words);
		static bool IsPuncture(const shared_ptr<Word> word);
		static string ConvertWordsToString(const vector<shared_ptr<Word>> words);

	//grammar pattern
		static GrammarPattern ConvertToPattern(const vector<shared_ptr<DataCollection::Word>> words);
		static bool SameGrammarPattern(const GrammarPattern& left,const GrammarPattern& right);
	};
}


