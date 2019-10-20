#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <memory>
#include <algorithm>

enum Types
{
	IntType = 1,
	DoubleType,
	CharType,
	StringType,
};

template <typename T>
struct TransformPair
{
	TransformPair() = default;
	TransformPair(T newValue, bool newTransformResult) : value(newValue), transformResult(newTransformResult)
	{ }

	T value;
	bool transformResult = false;
};

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

//шаблонная функция принимабщая строку и извлеающее из нее значения типа T,
//в случае ошибки бросается исключение
template <typename T>
TransformPair<T> fromString(std::string const& checkString)
{
	std::istringstream stream(checkString);
	T value;
	stream >> value;

	if (stream.fail() || stream.peek() != EOF)
		return TransformPair<T>('0', false);

	return TransformPair<T>(value, true);
}

template <typename T>
bool formTree(std::string const& stringTreeForm, std::shared_ptr<Node<T>>& root)
{
	//первый символ - '(', нет необходимости его рассматривать
	size_t stringIndex = 1;

	//запись имени корня
	std::string rootStringValue;
	while (stringIndex < stringTreeForm.size() && (stringTreeForm[stringIndex] != '(' && stringTreeForm[stringIndex] != ')'))
	{
		rootStringValue += stringTreeForm[stringIndex];
		stringIndex++;
	}
	if (rootStringValue.empty())
		return false;

	//проверка на то, что тип содержащийся в узлах соответствует типу содержащемуся в голове дерева
	std::istringstream stream(rootStringValue);
	T rootValue;
	stream >> rootValue;
	if (stream.fail() || stream.peek() != EOF)
		return false;
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
BinaryTree<T> treeCreation(std::string const& stringTreeForm)
{
	auto root = std::make_shared<Node<T>>();
	bool formResult = formTree(stringTreeForm, root);

	return (formResult) ? BinaryTree<T>(root) : BinaryTree<T>(nullptr);
}

template <typename T>
int treeCheck(BinaryTree<T>&& binTree)
{
	std::shared_ptr<Node<T>> root = binTree.getRootsValue();
	if (!root)
		return -1;

	bool leftCheck = binTree.findSameElements(root->left);
	if (leftCheck)
		return 1;

	return binTree.findSameElements(root->right);
}

template <typename T>
class BinaryTree
{
public:
	BinaryTree(std::shared_ptr<Node<T>> const& root) : mainRoots(root)
	{ }

	std::shared_ptr<Node<T>> getRootsValue() const
	{
		return mainRoots;
	}

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
