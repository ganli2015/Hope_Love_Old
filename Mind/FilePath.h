#pragma  once
#include "InOut.h"
#include <string>

namespace Mind
{
	const static std::string NonBaseConceptString_InitialFilename="NonBaseConceptString_Initial.txt";
	const static std::string ConceptConnections_InitialFilename="ConceptConnections_Initial.txt";
	const static std::string BaseConceptsStringFilename="BaseConceptsString.txt";

	const static std::string GrammaPatterns_InitialFilename="GrammaPatterns_Initial.txt";
	const static std::string StringGrammar_InitialFilename="str_sample.txt";
	const static std::string GrammarLocal_InitialFilename = "GrammarLocal_Initial.txt";

	const static std::string ConceptReactor_InitialFilename="ReactorIO_Initial.txt";
	const static std::string ConceptReactorNetworkFilename="network.txt";

	static std::string DataDir = "HopeLoveData\\";
	_declspec(dllexport) std::string GetHopeLoveMindPath();
	_declspec(dllexport) void SetHopeLoveMindPath(const std::string str);
}
