#pragma once
#include "InOut.h"

namespace DataCollection
{
	///A Character is a Chinese character or a punctuation.
	///It is a fundamental element of a sentence.
	class _DATACOLLECTIONINOUT Character : public Obj<Character>
	{
		std::string _character;
	public:
		Character(void);
		~Character(void);
		///The size of <character> should be two if it is a Chinese character.
		Character(std::string character);

		///Convert <me> to an integer.
		int ToInt() const;
		bool IsSame(Character chara) const ;
		std::string GetString() const {return _character;}

		_DATACOLLECTIONINOUT inline friend bool operator==(Character lh,Character rh);
	};
}


