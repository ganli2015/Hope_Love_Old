#pragma once
#include "PublicHeader.h"
#include "../LogicSystem/Number.h"

#include <gmock/gmock.h>

class MockNumber : public LogicSystem::Number<Mind::iConcept>
{
public:
	
	MOCK_CONST_METHOD1(Match, bool(const shared_ptr<Mind::iConcept>));
};

