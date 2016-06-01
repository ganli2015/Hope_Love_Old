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
		Puncture
	};

	const int NUM_PARTOFSPEECH=12;

	///A Word constitutes of one or more characters.
	class _DATACOLLECTIONINOUT Word : public Obj<Word>
	{
		std::vector<shared_ptr<Character>> _word;

		bool _known;
	public:
		Word(void);
		~Word(void);
		Word(std::vector<shared_ptr<Character>> word);
		Word(std::string word);
		Word(const Word& word);
		Word(const Character chara);

		int NumOfChara() const {return _word.size();}
		bool IsSame(const shared_ptr<Word> word) const;
		std::string GetString() const ;

		Word& operator+=(const Character right);
		Word& operator=(const Word right);

		virtual PartOfSpeech Type() const ;

	    void KnowIt(){_known=true;};
        //void UnknowIt(){_known=false;};
        //bool DoWeKnow() const {return _known;}
		long long ToInt() const;

	private:

	};

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
		virtual PartOfSpeech Type() const {return Puncture;}
	};



}



