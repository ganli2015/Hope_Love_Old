#pragma once
#include "InOut.h"

namespace DataCollection
{
	class Character;
	class _DATACOLLECTIONINOUT Punctures : public MyObject
	{
		std::vector<shared_ptr<Character>> _punctures;
		std::vector<shared_ptr<Character>> _puncEndofSentence;
		std::vector<shared_ptr<Character>> _puncRightside;

		void Initialize();
	public:
		Punctures(void);
		~Punctures(void);

		bool IsPuncEndofSentence(shared_ptr<Character> val) const;
		bool IsPuncRightside(shared_ptr<Character> val) const;
	};
}


