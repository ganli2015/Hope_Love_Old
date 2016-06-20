#pragma once
#include "../UTFacility/LeafCreator.h"
#include "../MindElement/MindElementCreator.h"
#include "../LogicSystem/LogicElementCreator.h"

class Initializer
{
public:
	Initializer()
	{
		LeafCreator::Init();
		shared_ptr<Mind::MindElementCreator> mindCreator(new Mind::MindElementCreator());
		Mind::iMindElementCreator::SetImp(mindCreator);

		shared_ptr<LogicSystem::LogicElementCreator> logicCreator(new LogicSystem::LogicElementCreator());
		LogicSystem::iLogicElementCreator::SetImp(logicCreator);
	};
	~Initializer() {};
};
