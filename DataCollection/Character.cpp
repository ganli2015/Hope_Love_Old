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
		//assert(strlen(character)==2);
		_character=character;
		//assert(_character.size()==2);
// 		if(_character.size()!=2)
// 			throw runtime_error("Invalid Character!");
	}

	// Character::Character( int charaInt )
	// {
	// 
	// }


	Character::~Character(void)
	{
	}

	int Character::ToInt()const 
	{
		int first=(int)(_character[0]);
		int second=(int)(_character[1]);
		return second*100+first;
	}

	bool Character::IsSame( Character chara ) const
	{
		if(chara.ToInt()==ToInt())
			return true;
		else return false;
	}

	bool operator==( Character lh,Character rh )
	{
		return lh.ToInt()==rh.ToInt();
	}
}

