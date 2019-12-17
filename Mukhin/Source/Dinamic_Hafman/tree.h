#pragma once
#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <locale>
#include <windows.h>
#include <unordered_map>
#include <ctime>
#include <fstream>
#include <sstream>
#include <map>
#include <queue>
#include <set>
#include <vector>

/*!
 * @brief Функция запускающая процедуру динамического кодирования и декодирования
 * @param argс количество аргументов командной строки
 * @param argv массив имён этих элементов
 * @return 0, если всё хорошо, иначе быть не может
 */
int use_dinamic(std::string);

/*!
 * @brief Структура <i>(родитель - левый ребёнок - правый ребёнок)</i>
 * @details Используется при кодировании и дальнейнем декодировании
 * инфорамции с помощью адаптивного (динамического) алгоритма Хаффмана,
 * играет роль единичной структуры в построении дерева Хаффмана.
 * @var Node::Node() конструктор по умолчанию
 * @var Node::parent умный указатель на родительский элемент
 * @var Node::left умнный указатель на левого ребёнка
 * @var Node::right умный указатель на правого ребёнка
 * @var Node::weight вес текущего элемента, сумма весов левого и правого ребёнка
 * @var Node::symbol символ текущего элемента
 */
struct Node {
    Node() = default;
	std::shared_ptr<Node> parent = nullptr;
    std::shared_ptr<Node> left = nullptr;
    std::shared_ptr<Node> right = nullptr;
	int weight = 0;
	char symbol = '\0';
};

/*!
 * @brief Класс, реализующий такую структуру данных, как дерево с размеченными листьями
 * @var Tree::decode_string переменная в которую будет записываться декодированная строка
 * @var Tree::code_string переменная в которую будет записываться закодированное сообщение
 * @var Tree::special_code словарь <char, std::string>, представляющий собой используемый алфавит
 * необходимый для кодировщика и декодировщика
 * @var Tree::first переменная, указывающая на элемент который стоит не на своём месте, нужна
 * для переставноки
 * @var Tree::second переменная, указывающая на элемент который стоит не на своём месте, нужна
 * для переставноки
 * @var Tree::root переменная, указывающая на корень дерева
 * @var Tree::for_new переменная, указывающая на пустой символ, для удобства вставки новых элементов
 * @var Tree::symbol_ptr словарь <char, std::shared_ptr<Node>>, для удобства контроля встречался ли
 * раньше символ или нет
 */
class Tree {
private:
    std::string get_path_by_ptr(std::shared_ptr<Node>);
    std::shared_ptr<Node> first = nullptr;
    std::shared_ptr<Node> second = nullptr;
	std::unordered_map<char, std::string> special_code = {};
    std::shared_ptr<Node> root = nullptr;
    std::shared_ptr<Node> for_new = nullptr;
    std::map<char, std::shared_ptr<Node>> symbol_ptr = {};
public:
	Tree();
	std::string decode_string = {};
	void insert(char);
	bool check_ascending(std::vector<std::pair<int, std::shared_ptr<Node>>>);
	void restructure();
	void decode();
    std::vector<std::pair<int, std::shared_ptr<Node>>> get_order();
    std::string code_string = {};
};
