#include "StdAfx.h"
#include "Test_CommonTool.h"

#include "../Mind/Cerebrum.h"
#include "../Mind/ConceptSet.h"
#include "../Mind/GrammaSet.h"

#include <Windows.h>

using namespace Mind;

TEST(MemoryLeak,ConceptSet)
{
	int objCountStart=MyObject::GetObjectCount();
	ConceptSet* cs=new ConceptSet();
	int objCountInit=MyObject::GetObjectCount();
	delete cs;
	int objCountEnd=MyObject::GetObjectCount();

	ASSERT_EQ(objCountStart,objCountEnd);
}

TEST(MemoryLeak,GrammarSet)
{
	int objCountStart=MyObject::GetObjectCount();
	GrammarSet* cs=new GrammarSet();
	int objCountInit=MyObject::GetObjectCount();
	delete cs;
	int objCountEnd=MyObject::GetObjectCount();

	ASSERT_EQ(objCountStart,objCountEnd);
}
TEST(MemoryLeak,Cerebrum)
{
	int objCountStart=MyObject::GetObjectCount();
	iCerebrum::SetInstance(Cerebrum::Instance());
	int objCountInit=MyObject::GetObjectCount();
	iCerebrum::KillInstance();
	int objCountEnd=MyObject::GetObjectCount();


	ASSERT_EQ(objCountStart,objCountEnd);
}
