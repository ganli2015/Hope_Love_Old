#include "StdAfx.h"
#include "Character.h"
#include <assert.h>

using namespace std;

namespace DataCollection
{
	Character::Character(void)
	{
	}

	Character::Character( string character )
	{
		_character=character;
	}


	Character::~Character(void)
	{
	}

	int Character::ToInt()const 
	{
		//Assume it is a Chinese character and has two chars in <_character>.
		int first=(int)(_character[0]);
		int second=(int)(_character[1]);
		return second*100+first;
	}

	bool Character::IsSame( Character chara ) const
	{
		//Compare their integer values to check whether they are the same.
		if(chara.ToInt()==ToInt())
			return true;
		else return false;
	}

	bool operator==( Character lh,Character rh )
	{
		return lh.ToInt()==rh.ToInt();
	}
}

