
/*
11 Рассматривается выражение следующего вида:
< выражение >::= < терм > | < терм > + < выражение > | < терм > - < выражение >
< терм > ::= < множитель > | < множитель > * < терм >
< множитель > ::= < число > | ( < выражение > ) | < множитель > ^ < число >
< число > ::= < цифра >
*/



#include <iostream>
#include <string>
#include <fstream>
#include "Vec_Stack.hpp"


nInt EvaluatePostfix(std::string &expression);

nInt PerformOperation(char &operation, int &operand1, int &operand2);

bool IsOperator(char &C);

int main(int argc, char* argv[])
{
	std::ifstream input;

	if(argc == 1)
		input.open("postfix.txt");

	else
		input.open(argv[1]);

	if (!input)
	{
		std::cout << "Couldn't open source file" << std::endl;

		return 0;
	}

	std::string expression;


	while (std::getline(input, expression)) {

		nInt result = EvaluatePostfix(expression);

		if (result != std::nullopt)
			std::cout << "_________\nExpression : " << expression << "\nResult : " << result.value() << std::endl;

		else
			std::cout << "Failed to calculate" << std::endl;
	}

	return 0;
}

nInt EvaluatePostfix(std::string &expression)
{
	Vec_Stack vecStack;

	for (size_t i = 0; i < expression.size(); ++i)
	{
		if (expression[i] == ' ')
			continue;

		if (IsOperator(expression[i])) {
			nInt rightOperand = vecStack.pop();

			if (rightOperand == std::nullopt) {
				std::cout << "________________________\nExpression : " << expression << "\n wrong input" << std::endl;

				return std::nullopt;
			}

			nInt leftOperand = vecStack.pop();

			if (leftOperand == std::nullopt) {
				std::cout << "________________________\nExpression : " << expression << "\n wrong input" << std::endl;

				return std::nullopt;
			}

			nInt result = PerformOperation(expression[i], leftOperand.value(), rightOperand.value());

			if (result == std::nullopt)
				return std::nullopt;

			else
				vecStack.push(result.value());
		}

		else if (isdigit(expression[i])) {
			int operand(0);

			while (i < expression.size() && isdigit(expression[i])) {
				operand = operand * 10 + (expression[i] - '0');

				++i;
			}

			--i;

			vecStack.push(operand);
		}

		else {
			std::cout << "______________________\nIncorrect input" << std::endl;

			return std::nullopt;
		}
	}

	return vecStack.pop();
}

bool IsOperator(char &c)
{
	return (c == '+' ||
		c == '-' ||
		c == '*' ||
		c == '^');
}

nInt PerformOperation(char &operation, int &operand1, int &operand2)
{
	if (operation == '+')
		return operand1 + operand2;

	else if (operation == '-')
		return operand1 - operand2;

	else if (operation == '*')
		return operand1 * operand2;

	else if (operation == '^')
		return (int)pow(operand1, operand2);

	else
		return std::nullopt;
}