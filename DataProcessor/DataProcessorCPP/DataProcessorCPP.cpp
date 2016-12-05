// DataProcessorCPP.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "GrammarSampleGenerator.h"
#include "GrammarPatternExtractor.h"
#include "GrammarLocalDistributionExtractor.h"

#include "TestSegmentation.h"

//#define GENERATE_GRAMMA_SAMPLES
//#define GENERATE_GRAMMA_DISTRIBUTION
//#define EXTRACT_GRAMMARLOCAL_DISTRIBUTION

int main()
{
#ifdef GENERATE_GRAMMA_SAMPLES
	GrammarSampleGenerator gsg;
	gsg.Run();
#endif // GENERATE_GRAMMA_SAMPLES
	
#ifdef GENERATE_GRAMMA_DISTRIBUTION
	GrammarPatternExtractor gpe;
	gpe.Run();
#endif // GENERATE_GRAMMA_DISTRIBUTION

#ifdef EXTRACT_GRAMMARLOCAL_DISTRIBUTION
	GrammarLocalDistributionExtractor glde;
	glde.Run();

#endif // EXTRACT_GRAMMARLOCAL_DISTRIBUTION



	TestSegmentation ts;
	ts.Run();

	logfile.close();

	system("pause");

    return 0;
}

