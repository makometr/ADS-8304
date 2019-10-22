#pragma once
#include <string>
#include <variant>
#include <memory>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>

typedef struct Node {
	int h_index; // относительный индекс
	
	std::string title; // название

	std::variant < std::shared_ptr<Node>, std::string > list_or_text; // текст или подсписок

	std::shared_ptr<Node> next;
}Node;

class h_content
{
public:
	h_content() = default;
	~h_content() = default;

	std::shared_ptr<Node> head;

	void load_h_content(std::vector<std::string> &sorted_nodes); //  загружаем файл в список

	void print(std::shared_ptr<Node> head, std::string index_str); // печатание списка

	std::shared_ptr<Node> add(std::string &source_str); // добавление

	std::shared_ptr<Node> insert(std::string &source_str); // вставка


	void normalize(const std::string &start, bool recursive); // нормализация индексов

private:
	
	void normalize_row(std::shared_ptr<Node> start, bool recursive = false); // служебный ф-я для нормализации 

	std::shared_ptr<Node> parse_str_into_node(std::string &source_str); // парсер строки в Node

};

