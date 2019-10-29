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
	int h_index; // "иерархический номер" (c)

	std::string title; // "название" (c)

	std::variant < std::shared_ptr<Node>, std::string > list_or_text; // "либо несколько подчиненных записей, либо текст" (c)

	std::shared_ptr<Node> next;
}Node;

class h_content
{
public:
	h_content() = default;
	~h_content() = default;

	std::shared_ptr<Node> head;

	void load_h_content(std::vector<std::string> &sorted_nodes); // forms a h_list, sets head in h_content::head

	void print(std::shared_ptr<Node> head, std::string index_str);

	std::shared_ptr<Node> add(std::string &source_str);

	std::shared_ptr<Node> insert(std::string &source_str);


	void normalize(const std::string &start, bool recursive);

private:

	void normalize_row(std::shared_ptr<Node> start, bool recursive = false);

	std::shared_ptr<Node> parse_str_into_node(std::string &source_str);

};

