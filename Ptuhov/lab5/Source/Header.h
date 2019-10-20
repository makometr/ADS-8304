#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <variant>
#include <memory>
#include <map>
#include <regex>


using StringVector = std::vector<std::string>;
using CharactersCodeMap = std::map<char, std::string>;

enum class ReturnCode
{
	IncorrectSymbols,
	IncorrectMapStringForm,
	BadPreffixForm,
	CollisionError,
	Correct
};

struct Node
{
	Node() = default;

	char character = 0;

	std::shared_ptr<Node> left;
	std::shared_ptr<Node> right;
};

struct DecodePair
{
	DecodePair(std::string newValue, bool res) : value(newValue), decodeResult(res)
	{}
	
	std::string value;
	bool decodeResult = true;
};


