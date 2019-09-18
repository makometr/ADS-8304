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

	std::vector<std::vector<char>> parameters; // множество строк, которые алфавиты
	std::vector<std::vector<char>> text; // множество строк, которые надо проанализировать

	void Analyze(const char* textfile,const char* parametersfile); // собсна функция-анализатор

private:
	std::vector<std::vector<char>> GetTextData(const char* filename); // смотрит в файл, достает все что можно построчно

	bool brackets(std::vector<char>::iterator, std::vector<char>::iterator); 
	bool element(std::vector<char>::iterator);
	bool list(std::vector<char>::iterator, std::vector<char>::iterator);
	bool row(std::vector<char>::iterator, std::vector<char>::iterator); // 4 рекурсивных брата-акробата
};

