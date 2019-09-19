#include "BracketAnalyzer.h"


int main(int argc, char* argv[])
{
	BracketAnalyzer analyzer;
	if (argc == 3)
		analyzer.Analyze(argv[1],argv[2]);
	else 
		analyzer.Analyze("SourceString.txt", "ParameterChars.txt");

	std::getchar();

	return 0;
}
