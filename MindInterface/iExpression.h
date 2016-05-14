#pragma once
#include "InOut.h"

namespace Mind
{
	class iConceptInteractTable;
}

namespace LogicSystem
{
	class _MINDINTERFACEINOUT iExpression: public MyObject
	{
	public:
		iExpression(void);
		virtual ~iExpression(void);

		///Return the interact table that contain interactions between base concepts in <me>.
		virtual shared_ptr<Mind::iConceptInteractTable> GetBaseInteractTable() const =0;
		///Return the interact table that contain interactions between prototype concepts in <me>.
		virtual shared_ptr<Mind::iConceptInteractTable> GetProtoInteractTable() const =0;
	};
}

