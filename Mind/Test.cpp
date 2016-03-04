#include "Stdafx.h"

#include "InOut.h"

#include <iterator>
#include <iostream>
#include <algorithm>

#include "Cerebrum.h"
#include "Concept.h"
#include "Cerebrum.h"
#include "../DataCollection/GrammaPattern.h"

using namespace DataCollection;
using namespace Mind;
int __cdecl main()
{
// 	vector<GrammarPattern> sortedPatterns=Cerebrum::Instance()->GrammarPatternSortByFrequency();
// 	for (unsigned int i=0;i<sortedPatterns.size();++i)
// 	{
// 		vector<PartOfSpeech> pos=sortedPatterns[i].GetPattern();
// 		copy(pos.begin(),pos.end(),ostream_iterator<int>(cout," ")); 
// 		cout<<endl;
// 	}

	Cerebrum* brain=Cerebrum::Instance();

	Identity id;
	id.str="ĪĪ";
	id.id=0;
	shared_ptr<Concept> con=brain->GetConcept(id);
	shared_ptr<ConceptLevelTable> table=con->GetLevelTable();

	return 0;
}

