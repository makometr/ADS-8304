#include "pch.h"
#include "BracketAnalyzer.h"


int main()
{
	BracketAnalyzer analyzer;

	analyzer.Analyze("SourceString.txt","ParameterChars.txt");

	std::getchar();

	return 0;
}
