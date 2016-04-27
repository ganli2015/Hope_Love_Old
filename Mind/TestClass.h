#pragma once
#include "InOut.h"

namespace Mind
{
	class iConceptInteractTable;

	class TestClass
	{
	public:
		TestClass(void);
		~TestClass(void);

		static void RunTest();

	private:
		static void Test_ConceptDeepInteraction();

		static void Test_BuildGrammarAssociation();

		static bool PairSameWithTable(const vector<pair<string,string>>& expect,const shared_ptr<iConceptInteractTable> table);
	};
}


