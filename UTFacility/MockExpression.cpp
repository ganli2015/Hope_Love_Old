#include "Stdafx.h"
#include "MockExpression.h"
#include "ConceptTableCreator.h"
#include "ConceptCreator.h"

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

shared_ptr<MockExpression> MockExpression::Create()
{
	shared_ptr<MockExpression> expre(new MockExpression());
	return expre;
}

shared_ptr<MockExpression> MockExpression::SimpleCreate( const string tableStr )
{
	shared_ptr<iConceptInteractTable> table=ConceptTableCreator::SimpleCreate(tableStr);

	shared_ptr<MockExpression> expre(new MockExpression());
	EXPECT_CALL(*expre,GetProtoInteractTable()).WillRepeatedly(testing::Return(table));
	EXPECT_CALL(*expre,GetBaseInteractTable()).Times(0);

	return expre;
}

void MockExpression::AddExpectCall_GetProtoConcept( const string concept )
{
	shared_ptr<iConcept> con=SimpleConceptCreator().Create(concept);
	EXPECT_CALL(*this,GetProtoConcept()).WillRepeatedly(testing::Return(con));
}
