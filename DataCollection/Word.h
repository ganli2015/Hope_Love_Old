#pragma once
#include "InOut.h"
#include "Character.h"

namespace DataCollection
{
	///There are 12 type of part of speech. 
	///Usually I write POS short for PartOfSpeech.
	enum PartOfSpeech
	{
		Noun,
		Verb,
		Adjective,
		Numeral,
		Quantifier,
		Pronoun,
		Adverb,
		Preposition,
		Conjunction,
		Auxiliary,
		Onomatopoeia,
		Interjection,
		Ambiguous,//Ambiguous indicates a word is known by AI but has no definite POS temporarily.
		Unknown,//Unknown indicates a word is unknown.
		Punctuation
	};

	///The total number of POS referring to Encyclopedia.
	const int NUM_PARTOFSPEECH=12;

	///A Word constitutes of one or more characters.
	///It indicates the superficial meaning of a short string in a sentence.
	///Each word has no connection to other words.
	class _DATACOLLECTIONINOUT Word : public Obj<Word>
	{
		std::vector<shared_ptr<Character>> _word;

		bool _known;
	public:
		Word(void);
		~Word(void);
		Word(std::vector<shared_ptr<Character>> word);
		///Only Chinese string is welcome.
		Word(std::string word);
		///Copy <word>.
		Word(const Word& word);
		Word(const Character chara);

		///Number of character in the word.
		int NumOfChara() const {return _word.size();}
		bool IsSame(const shared_ptr<Word> word) const;
		std::string GetString() const ;

		///Append a character <right> to <me>.
		Word& operator+=(const Character right);
		Word& operator=(const Word right);

		///Get type of <me>.
		///There are twelve types.
		virtual PartOfSpeech Type() const ;

		///Each word has a state of whether Cerebrum knows it.
		///It is designed for convenient use for sentence analysis.
	    void KnowIt(){_known=true;};
		long long ToInt() const;

	private:

	};

	///Construct word by simply addition like arithmetic.
	_DATACOLLECTIONINOUT Word operator+(const Character left,const Character right);
	_DATACOLLECTIONINOUT Word operator+(const Word left,const Character right);
	_DATACOLLECTIONINOUT Word operator+(const Character left,const Word right);
	_DATACOLLECTIONINOUT Word operator+(const Word left,const Word right);

	class _DATACOLLECTIONINOUT noun: public Word
	{
	public:
		noun(std::string word):Word(word){ KnowIt();};
		virtual PartOfSpeech Type() const {return Noun;}
	};

	class _DATACOLLECTIONINOUT verb: public Word
	{
	public:
		verb(std::string word):Word(word){KnowIt();};
		virtual PartOfSpeech Type() const {return Verb;}
	};

	class _DATACOLLECTIONINOUT adjective: public Word
	{
	public:
		adjective(std::string word):Word(word){KnowIt();};
		virtual PartOfSpeech Type() const {return Adjective;}
	};

	class _DATACOLLECTIONINOUT numeral: public Word
	{
	public:
		numeral(std::string word):Word(word){KnowIt();};
		virtual PartOfSpeech Type() const {return Numeral;}
	};

	class _DATACOLLECTIONINOUT quantifier: public Word
	{
	public:
		quantifier(std::string word):Word(word){KnowIt();};
		virtual PartOfSpeech Type() const {return Quantifier;}
	};

	class _DATACOLLECTIONINOUT pronoun: public Word
	{
	public:
		pronoun(std::string word):Word(word){KnowIt();};
		virtual PartOfSpeech Type() const {return Pronoun;}
	};

	class _DATACOLLECTIONINOUT adverb: public Word
	{
	public:
		adverb(std::string word):Word(word){KnowIt();};
		virtual PartOfSpeech Type() const {return Adverb;}
	};

	class _DATACOLLECTIONINOUT preposition: public Word
	{
	public:
		preposition(std::string word):Word(word){KnowIt();};
		virtual PartOfSpeech Type() const {return Preposition;}
	};

	class _DATACOLLECTIONINOUT conjunction: public Word
	{
	public:
		conjunction(std::string word):Word(word){KnowIt();};
		virtual PartOfSpeech Type() const {return Conjunction;}
	};

	class _DATACOLLECTIONINOUT auxiliary: public Word
	{
	public:
		auxiliary(std::string word):Word(word){KnowIt();};
		virtual PartOfSpeech Type() const {return Auxiliary;}
	};

	class _DATACOLLECTIONINOUT onomatopoeia: public Word
	{
	public:
		onomatopoeia(std::string word):Word(word){KnowIt();};
		virtual PartOfSpeech Type() const {return Onomatopoeia;}
	};

	class _DATACOLLECTIONINOUT interjection: public Word
	{
	public:
		interjection(std::string word):Word(word){KnowIt();};
		virtual PartOfSpeech Type() const {return Interjection;}
	};

	class _DATACOLLECTIONINOUT puncture: public Word
	{
	public:
		puncture(std::string word):Word(word){KnowIt();};
		virtual PartOfSpeech Type() const {return Punctuation;}
	};



}



