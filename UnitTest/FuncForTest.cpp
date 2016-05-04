#include "StdAfx.h"
#include "FuncForTest.h"

#include "../MindElement/Concept.h"

#include "../DataCollection/Word.h"

using namespace Mind;
using namespace DataCollection;

namespace FuncForTest
{

	shared_ptr<iConcept> SimpleConcept( const string str )
	{
		shared_ptr<Word> w(new Word(str));
		shared_ptr<Concept> res(new Concept(w)); 

		return res;
	}

}
