#include "Stdafx.h"
#include "MockExpression.h"
#include "ConceptTableCreator.h"

#include "../MindInterface/iConceptInteractTable.h"

using namespace Mind;

shared_ptr<MockExpression> MockExpression::Create( const string tableStr )
{
	shared_ptr<iConceptInteractTable> table=ConceptTableCreator::Create(tableStr);

	shared_ptr<MockExpression> expre(new MockExpression());
	EXPECT_CALL(*expre,GetProtoInteractTable()).WillRepeatedly(testing::Return(table));
	EXPECT_CALL(*expre,GetBaseInteractTable()).Times(0);

	return expre;
}