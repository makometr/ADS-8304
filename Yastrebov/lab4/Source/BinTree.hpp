#pragma once
#include <variant>
#include <memory>
#include <string>

typedef std::string::iterator sIter;

template <typename Elem>
class Node;

template <typename Elem>
class BinTree;

template<typename Elem>
using nodePtr = std::shared_ptr<Node<Elem>>;

sIter bracket_closer(sIter begin)
{
	size_t tmp = 1;

	while (tmp)
	{
		begin++;

		if (*begin == '(')
			tmp++;

		if (*begin == ')')
			tmp--;
	}

	return begin;
}



template <typename Elem>
class Node
{
public:
	Node(Elem value) {
		this->value = value;
	}

	Node(const Node<Elem> &copy) {
		left = copy.left;

		right = copy.right;

		value = copy.value;
	}

	Node<Elem>& operator=(const Node<Elem> &copy)
	{
		left = copy.left;

		right = copy.right;

		value = copy.value;

		return *this;
	}

	Node() = default;

	~Node() = default;

	Elem value;

	nodePtr<Elem> left;
	nodePtr<Elem> right;

};



template<typename Elem>
class BinTree
{
public:

	BinTree() = default;
	~BinTree() = default;

	BinTree(const BinTree<Elem> &copy) {
		head = copy.head;
	}

	BinTree<Elem>& operator=(const BinTree<Elem> &copy) {
		head = copy.head;

		return *this;
	}

	nodePtr<Elem> head;

	nodePtr<Elem> readTreeFromStringNLR(std::string&, sIter, sIter);
	nodePtr<Elem> readTreeFromStringLNR(std::string&, sIter, sIter);
	nodePtr<Elem> readTreeFromStringLRN(std::string&, sIter, sIter);

	void printTreeNLR(nodePtr<Elem>	root);
	void printTreeLNR(nodePtr<Elem> root);
	void printTreeLRN(nodePtr<Elem> root);
};

template<typename Elem>
nodePtr<Elem> BinTree<Elem>::readTreeFromStringNLR(std::string &source, sIter begin, sIter end)
{

	std::string root;

	sIter tmp = begin;


	while ((*tmp != '(') && (*tmp != '#') && (*tmp != ')'))
		root += *(tmp++);

	auto res = std::make_shared<Node<Elem>>();
	res->value = (Elem)root;


	if (*tmp == ')') {
		res->left = nullptr;
		res->right = nullptr;
		return res;
	}

	if (*tmp == '#')
		res->left = nullptr;

	else {
		sIter tmpCopy = tmp;
		tmp = bracket_closer(tmpCopy);
		res->left = readTreeFromStringNLR(source, tmpCopy + 1, tmp - 1);
	}

	++tmp;

	if (*tmp == '#')
		res->right = nullptr;

	else
	{
		res->right = readTreeFromStringNLR(source, tmp + 1, bracket_closer(tmp) - 1);
	}

	return res;
}

template<typename Elem>
nodePtr<Elem> BinTree<Elem>::readTreeFromStringLNR(std::string &source, sIter begin, sIter end)
{
	auto res = std::make_shared<Node<Elem>>();

	sIter tmp = begin;

	if (*tmp == '#')
		res->left = nullptr;

	else {
		sIter tmpCopy = tmp;
		tmp = bracket_closer(tmpCopy);

		res->left = readTreeFromStringLNR(source, tmpCopy + 1, tmp - 1);
	}

	++tmp;

	std::string root;

	while ((*tmp != '(') && (*tmp != '#'))
		root += *(tmp++);

	res->value = (Elem)root;

	if (*tmp == '#') {
		res->right = nullptr;
	}

	else {
		res->right = readTreeFromStringLNR(source, tmp + 1, bracket_closer(tmp) - 1);
	}

	return res;
}

template<typename Elem>
inline nodePtr<Elem> BinTree<Elem>::readTreeFromStringLRN(std::string &source, sIter begin, sIter end)
{
	sIter tmp = begin;

	auto res = std::make_shared<Node<Elem>>();


	if (*tmp == '#')
		res->left = nullptr;

	else {
		sIter tmpCopy = tmp;
		tmp = bracket_closer(tmpCopy);

		res->left = readTreeFromStringLRN(source, tmpCopy + 1, tmp - 1);
	}

	++tmp;

	if (*tmp == '#')
		res->right = nullptr;

	else
	{
		sIter tmpCopy = tmp;
		tmp = bracket_closer(tmpCopy);
		res->right = readTreeFromStringLRN(source, tmpCopy + 1, tmp - 1);
	}

	++tmp;

	std::string root;

	while ((tmp <= end) && (tmp < source.end()))
		root += *(tmp++);

	res->value = (Elem)root;

	return res;

}

template<typename Elem>
void BinTree<Elem>::printTreeLRN(nodePtr<Elem> root)
{
	if (!root) {
		std::cout << '#';
		return;
	}

	std::cout << '(';

	printTreeLRN(root->left);
	printTreeLRN(root->right);

	std::cout << root->value << ')';
}

template<typename Elem>
void BinTree<Elem>::printTreeLNR(nodePtr<Elem> root)
{
	if (!root) {
		std::cout << '#';
		return;
	}

	std::cout << '(';

	printTreeLNR(root->left);
	std::cout << root->value;
	printTreeLNR(root->right);

	std::cout << ')';
}

template<typename Elem>
void BinTree<Elem>::printTreeNLR(nodePtr<Elem> root)
{
	if (!root) {
		std::cout << '#';
		return;
	}

	std::cout << '(';

	std::cout << root->value;

	printTreeNLR(root->left);
	printTreeNLR(root->right);

	std::cout << ')';
}
