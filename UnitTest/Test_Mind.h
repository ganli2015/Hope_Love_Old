#pragma once
#include "PublicHeader.h"

namespace Mind
{
	class iConceptInteractTable;

}

class Test_Mind
{
public:
	Test_Mind(void);
	~Test_Mind(void);

	static void RunTest();

private:
	static void Test_ConceptDeepInteraction();

	static void Test_BuildGrammarAssociation();

};

