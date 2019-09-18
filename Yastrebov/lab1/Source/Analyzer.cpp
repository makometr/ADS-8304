#include "BracketAnalyzer.h"
#include <cstdio>

int main()
{
	BracketAnalyzer analyzer;

	analyzer.Analyze("Tests/SourceString.txt","Tests/ParameterChars.txt");
	
	return 0;
}
