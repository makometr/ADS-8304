#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

class BracketAnalyzer
{
public:
	BracketAnalyzer();
	~BracketAnalyzer();

	std::vector<char> parameters;
	std::vector<char> text;

	void Analyze(const char* textfile,const char* parametersfile);

private:
	std::vector<char> GetTextData(const char* filename);

	bool brackets(std::vector<char>::iterator, std::vector<char>::iterator);
	bool element(std::vector<char>::iterator);
	bool list(std::vector<char>::iterator, std::vector<char>::iterator);
	bool row(std::vector<char>::iterator, std::vector<char>::iterator);
};

