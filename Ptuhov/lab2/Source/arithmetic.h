#pragma once

#include <iostream>
#include <string>
#include <map>
#include <regex>
#include <fstream>
#include <sstream>
#include <cmath>
#include <stack>
#include <variant>
#include <memory>

using StringPair = std::pair<std::string, std::string>;
using IntBoolPair = std::pair<int, bool>;
using Node = struct Node;
using NodePair = std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>>;

struct Node {
	Node() = default;
	int evaluate();

	//храним или пару следующих элементов для бинарного вызова, или следущий элемент для унарного
	std::variant<NodePair, std::shared_ptr<Node>> arguments;
	//храним или число - значение атома, или значение операции
	std::variant<int, char> value;
};

class Arithmetic
{
public:
	Arithmetic() = default;
	void SetStringValue(std::string const new_data_);
	void UpdateMap(std::string const key, int const value);
	std::string GetStringValue();
	int CheckBrackets();
	bool ExtractVariableValues(std::string value, std::ostream& out);
	bool InMap(const std::string value);
	bool RemakePowerToInt();
	bool ListFormation(std::shared_ptr<Node>& nd, std::string const s, std::ostream& out);
	IntBoolPair ExtractValueForListFormation(const std::string& s, size_t* ind);
	std::string ExtractBracketsValue(const std::string& s, size_t* ind);
	void operator<<(std::ostream& out);

	
private:
	IntBoolPair CheckVariable(std::string& VariableName);

	std::string data_;
	std::map<std::string, int> dict_;
};

