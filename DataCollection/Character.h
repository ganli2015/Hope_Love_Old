#pragma once
#include "InOut.h"

namespace DataCollection
{
	class _DATACOLLECTIONINOUT Character
	{
		std::string _character;
	public:
		Character(void);
		~Character(void);
		Character(std::string character);
		//Character(int charaInt);

		int ToInt() const;
		bool IsSame(Character chara) const ;
		std::string GetString() const {return _character;}

		_DATACOLLECTIONINOUT inline friend bool operator==(Character lh,Character rh);
	};
}


