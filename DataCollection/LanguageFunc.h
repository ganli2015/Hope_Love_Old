#pragma once
#include "InOut.h"
#include <utility>

namespace DataCollection
{
	class Word;
	class GrammarPattern;
	class Character;
	class Punctuations;
	enum PartOfSpeech;
	class _DATACOLLECTIONINOUT LanguageFunc
	{

		static shared_ptr<Punctuations> _punctures;
	public:
		LanguageFunc(void);
		~LanguageFunc(void);

	//puncture
		static bool IsPuncEndofSentence(shared_ptr<Character> val);
		static bool IsPuncRightside(shared_ptr<Character> val); 
		///Cutter sentence to two part:sentence with no punctures and punctures.
		///(Only support for sentence with punctures in the end)
		static pair<vector<shared_ptr<Character>>,vector<shared_ptr<Character>>> TrimEndPunctures(const vector<shared_ptr<Character>>& raw);
		static pair<vector<Character>,vector<Character>> TrimEndPunctures(const vector<Character>& raw);

	//character
		static std::vector<shared_ptr<Character>> ConvertStringToCharacter(std::string str);
		static std::string ConvertCharacterToString(std::vector<shared_ptr<Character>> charas);

	//word
		///Get a particular word that is a word of definite POS.
		///It is a derived class of word.
		static shared_ptr<DataCollection::Word> GetParticularWord(const std::string str, const DataCollection::PartOfSpeech partofspeech );
		static vector<shared_ptr<Word>> ConvertPuncturesToWords(const vector<Character>& puncs);
		static pair<vector<shared_ptr<Word>>,vector<shared_ptr<Word>>> TrimEndPunctures(const vector<shared_ptr<Word>>& raw);
		static pair<vector<Word>,vector<Word>> TrimEndPunctures(const vector<Word>& raw);
		///In <words> find a word that is the same with <word>.
		///Return the index of the word if exists,otherwise return -1.
		static int IndexOf(const vector<shared_ptr<Word>>& words,const shared_ptr<Word> word);
		///Remove punctuations in <words> no matter which location they are in <words>.
		static vector<shared_ptr<Word>> RemovePuncs(const vector<shared_ptr<Word>>& words);
		static bool IsPuncture(const shared_ptr<Word> word);
		static string ConvertWordsToString(const vector<shared_ptr<Word>> words);

	//grammar pattern
		//////////////////////////////////////////////////////////////////////////
		///Get POS of <words> and connect them into a grammar pattern.
		//////////////////////////////////////////////////////////////////////////
		static GrammarPattern ConvertToPattern(const vector<shared_ptr<DataCollection::Word>> words);
		static GrammarPattern ConvertToPattern(const vector<int> posInt);

		static bool SameGrammarPattern(const GrammarPattern& left,const GrammarPattern& right);
	};
}


