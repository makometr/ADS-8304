#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <memory>
#include <algorithm>

std::string extractBracketsValue(std::string const& stringTreeForm, size_t* stringIndexPointer);
bool checkBracketsPlacement(std::string const& checkString);

template <typename T>
class BinaryTree;

template <typename T>
struct Node
{
	Node() : left(nullptr), right(nullptr), value(T())
	{ }

	T value;

	std::shared_ptr<Node<T>> left;
	std::shared_ptr<Node<T>> right;
};

/*
	fromString       \
	                  -- функции необходимые для получения типа хранящихся значений в полученном дереве
	getVariableType  /
*/

template<class T>
T fromString(std::string const& checkString)
{
	std::istringstream stream(checkString);
	T tmp;
	stream >> tmp;

	if (stream.fail() || stream.peek() != EOF)
		throw std::invalid_argument("");

	return tmp;
}

//int - 1, double - 2, char - 3, string - 4
int getVariableType(std::string const& checkString)
{
	try
	{
		fromString<int>(checkString);
		return 1;
	}
	catch (std::invalid_argument&)
	{
		try
		{
			fromString<double>(checkString);
			return 2;
		}
		catch (std::invalid_argument&)
		{
			try
			{
				fromString<char>(checkString);
				return 3;
			}
			catch (std::invalid_argument&)
			{
				return 4;
			}
		}
	}
}

template <typename T>
bool formTree(std::string const& stringTreeForm, std::shared_ptr<Node<T>>& root)
{
	//первый символ - '(', нет необходимости его рассматривать
	size_t stringIndex = 1;

	//запись имени корня
	std::string rootStringValue;
	while (stringIndex < stringTreeForm.size() &&
		(stringTreeForm[stringIndex] != '(' && stringTreeForm[stringIndex] != ')'))
	{
		rootStringValue += stringTreeForm[stringIndex];
		stringIndex++;
	}
	if (rootStringValue.empty())
		return false;
	
	//проверка на то, что тип содержащийся в узлах соответствует типу содержащемуся в голове дерева
	T rootValue;
	try
	{
		rootValue = fromString<T>(rootStringValue);
	}
	catch (std::invalid_argument&)
	{
		return false;
	}
	//

	root->value = rootValue;

	//если был встречен конец строки, то левое и правое поддерево пустые
	if (stringTreeForm[stringIndex] == ')')
		return true;
	//

	auto leftTree = std::make_shared<Node<T>>();
	std::string bracketsValue = extractBracketsValue(stringTreeForm, &stringIndex);

	bool formLeftResult = formTree(bracketsValue, leftTree);
	if (!formLeftResult)
		return false;

	//если был встречен конец строки, то правое поддерево пустое
	if (stringTreeForm[stringIndex] == ')')
	{
		root->left = leftTree;
		return true;
	}
	//

	auto rightTree = std::make_shared<Node<T>>();
	bracketsValue = extractBracketsValue(stringTreeForm, &stringIndex);

	bool formRightResult = formTree(bracketsValue, rightTree);
	if (!formRightResult)
		return false;

	//проверка на корректность конечных символов
	if (stringTreeForm[stringIndex] != ')' || stringIndex + 1 != stringTreeForm.size())
		return false;
	//

	root->left = leftTree;
	root->right = rightTree;

	return true;
}

template <typename T>
void workWithTree(std::string const& stringTreeForm, std::ostream& out)
{
	auto root = std::make_shared<Node<T>>();
	bool formResult = formTree(stringTreeForm, root);
	if (!formResult)
	{
		out << "Incorrect tree form or it's not a binary tree\n";
		return;
	}

	BinaryTree<T> binTree(root);

	bool leftCheck = binTree.findSameElements(root->left);
	if (leftCheck)
	{
		out << "YES\n";
		return;
	}

	out << ((binTree.findSameElements(root->right)) ? "YES\n" : "NO\n");
}

template <typename T>
class BinaryTree
{
public:
	BinaryTree(std::shared_ptr<Node<T>> const& root) : mainRoots(root)
	{ }
	
	/*
		findSameElements        \
		treeSearch               -- функции осуществляющие поиск одинаковых узлов рассматриваемого дерева 
		checkElementsOnSameness /
	*/
	bool findSameElements(std::shared_ptr<Node<T>> const& checkElement)
	{
		if (checkElement == nullptr)
			return false;

		if (treeSearch(checkElement, mainRoots))
			return true;

		if (findSameElements(checkElement->left))
			return true;

		return findSameElements(checkElement->right);
	}

	bool treeSearch(std::shared_ptr<Node<T>> const& checkElement, std::shared_ptr<Node<T>> const& root)
	{
		if (!root)
			return false;

		if (&checkElement == &(root->left))
			return false;

		if (checkElementsOnSameness(checkElement, root->left))
			return true;

		if (&checkElement == &(root->right))
			return false;

		if (checkElementsOnSameness(checkElement, root->right))
			return true;

		if (treeSearch(checkElement, root->left))
			return true;

		return treeSearch(checkElement, root->right);
	}

	bool checkElementsOnSameness(std::shared_ptr<Node<T>> const& firstElement, std::shared_ptr<Node<T>> const& secondElement)
	{
		if (secondElement == nullptr && firstElement == nullptr)
			return true;

		if ((secondElement == nullptr && firstElement != nullptr) ||
			(secondElement != nullptr && firstElement == nullptr))
			return false;

		if (firstElement->value != secondElement->value)
			return false;

		bool leftPartCheck = checkElementsOnSameness(firstElement->left, secondElement->left);
		bool rightPartCheck = checkElementsOnSameness(firstElement->right, secondElement->right);

		return leftPartCheck && rightPartCheck;
	}

private:
	std::shared_ptr<Node<T>> mainRoots;
};
