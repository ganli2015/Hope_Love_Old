// DataProcessorCPP.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "GrammarSampleGenerator.h"
#include "GrammarPatternExtractor.h"

//#define GENERATE_GRAMMA_SAMPLES
#define GENERATE_GRAMMA_DISTRIBUTION

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

	logfile.close();

    return 0;
}

