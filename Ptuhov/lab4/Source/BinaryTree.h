#pragma once
#include <memory>
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>

using Node = struct Node;

void printTree(std::shared_ptr<Node> const& root, std::string const& mainRootName);
void checkTree(std::string& stringTreeForm, std::ostream& out);

//функция принимающая строку (из которой будет формироватся дерево) и ссылку на указатель на голову дерева
bool formTree(std::string const& stringTreeForm, std::shared_ptr<Node>& root);

//функция принимающая строку и указатель на положение открывающей скобки,
//она возвращает значение содержащееся от переданной открывающей до корректной закрывающей
std::string extractBracketsValue(std::string const& stringTreeForm, size_t* stringIndexPointer);

//функция принимающая два узла дерева и проверяющая их на равенство(проверяется не только значение в текущих узлах а еще и в дочерних)
bool checkElementsOnSameness(std::shared_ptr<Node> const& firstElement, std::shared_ptr<Node> const& secondElement);

//функция проверяет наличие переданного элемента в дереве с головой root
bool treeSearch(std::shared_ptr<Node> const& checkElement, std::shared_ptr<Node> const& root);

//функция осуществляющая перебор всех узлов дерева ищя два одинаковых при помощи 2-х вышеописанных ф-ий
bool findSameElements(std::shared_ptr<Node> const& checkElement, std::shared_ptr<Node> const& mainRoot);

struct Node
{
	Node() = default;
	std::string name;

	std::shared_ptr<Node> left;
	std::shared_ptr<Node> right;
};
