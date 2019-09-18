#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <string>

typedef std::string::iterator iter;

class BracketAnalyzer
{
public:
	BracketAnalyzer();
	~BracketAnalyzer();

	std::vector<std::string> parameters;
	std::vector<std::string> text;

	void Analyze(const char* textfile,const char* parametersfile);

private:
	std::vector<std::string> GetTextData(const char* filename);

	bool brackets(iter&, iter&);
	bool element(iter&);
	bool list(iter&, iter&);
	bool row(iter&, iter&);
};

