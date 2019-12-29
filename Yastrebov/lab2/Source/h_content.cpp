
#include "h_content.h"

std::shared_ptr<Node> h_content::parse_str_into_node(std::string &source_str)
{
	std::string tmp_value_str;

	size_t tmp_index = 0;

	while (!isspace(source_str[tmp_index]))
	{
		if (source_str[tmp_index] != '.')
			tmp_value_str += source_str[tmp_index++];
		else {
			tmp_value_str = "";
			tmp_index++;
		}
	}

	int h_index_value = std::stoi(tmp_value_str);

	std::string title;
	std::string text;

	while ((tmp_index < source_str.size()) && (source_str[tmp_index] != '['))
		title += source_str[tmp_index++];

	if (tmp_index == source_str.size())
	{
		std::shared_ptr<Node> result(new Node);

		result->h_index = h_index_value;
		result->title = title;

		std::shared_ptr<Node> nullpntr;
		result->list_or_text = nullpntr;

		result->next = nullptr;

		std::cout << "Parsed line : " << source_str << std::endl;
		return result;
	}

	else
	{
		while (tmp_index < source_str.size())
			text += source_str[tmp_index++];

		std::shared_ptr<Node> result(new Node);

		result->h_index = h_index_value;
		result->title = title;

		result->list_or_text = text;

		result->next = nullptr;

		std::cout << "Parsed line : " << source_str << std::endl;
		return result;
	}
}

void h_content::load_h_content(std::vector<std::string> &sorted_nodes)
{
	if (std::find(sorted_nodes[0].begin(), sorted_nodes[0].end(), '.')
		<= std::find(sorted_nodes[0].begin(), sorted_nodes[0].end(), ' ')) {

		std::cout << "Input must contain at least one zero-level head node" << std::endl;
		return;
	}

	head = parse_str_into_node(sorted_nodes[0]);

	for (size_t i = 1; i < sorted_nodes.size(); i++)
	{
		if (!add(sorted_nodes[i]))
			std::cout << "failed to add" << std::endl;
	}
}

std::shared_ptr<Node> h_content::insert(std::string &src_str)
{
	if (!head) {
		if (std::find(src_str.begin(), src_str.end(), '.')
			< std::find(src_str.begin(), src_str.end(), ' ')) {

			std::cout << "Non-zero-level  node cant be inserted as head (empty list)" << std::endl;
			return nullptr;
		}

		head = parse_str_into_node(src_str);

		return head;
	}

	std::shared_ptr<Node> for_head_inserting;
	auto current_node = head;

	std::string tmp_value_str;

	int tmp_index = 0;

	while (!isspace(src_str[tmp_index]))
	{
		if (src_str[tmp_index] != '.')
			tmp_value_str += src_str[tmp_index++];
		else
		{
			int current_h_index = std::stoi(tmp_value_str);

			while (current_node->h_index != current_h_index) {
				if (current_node->next == nullptr) {

					std::cout << "Non-existent prefix" << std::endl;
					return nullptr;
				}
				current_node = current_node->next;
			}

			if (current_node->list_or_text.index() == 1) {

				std::cout << "Prefix is not a list" << std::endl;
				return nullptr;
			}
			if (!std::get<0>(current_node->list_or_text)) {
				if ((std::find(src_str.begin() + tmp_index + 1, src_str.end(), '.')) < (std::find(src_str.begin() + tmp_index + 1, src_str.end(), ' ')))
				{
					std::cout << "Non-existent prefix" << std::endl;
					return nullptr;
				}
				else
				{
					current_node->list_or_text = parse_str_into_node(src_str);
					return std::get<0>(current_node->list_or_text);
				}
			}

			for_head_inserting = current_node;
			current_node = std::get<0>(current_node->list_or_text);

			tmp_index++;
			tmp_value_str = "";
		}
	}

	int current_h_index = std::stoi(tmp_value_str);

	while (current_node->h_index < current_h_index)
	{
		if (current_node->next) {
			if (current_node->next->h_index < current_h_index)
				current_node = current_node->next;
			else if (current_node->next->h_index == current_h_index) {
				auto tmp = current_node->next;

				current_node->next = parse_str_into_node(src_str);

				current_node->next->next = tmp;

				auto res = current_node->next;

				current_node = current_node->next;

				while (current_node->next && (current_node->next->h_index == current_node->h_index))
				{
					current_node = current_node->next;
					current_node->h_index++;
				}

				return res;
			}
			else if (current_node->next->h_index > current_h_index)
			{
				auto tmp = current_node->next;

				current_node->next = parse_str_into_node(src_str);

				current_node->next->next = tmp;

				return current_node->next;
			}
		}

		else
		{
			current_node->next = parse_str_into_node(src_str);

			return current_node->next;
		}
	}

	if (for_head_inserting) {
		for_head_inserting->list_or_text = parse_str_into_node(src_str);

		std::get<0>(for_head_inserting->list_or_text)->next = current_node;

		current_node = std::get<0>(for_head_inserting->list_or_text);

		while (current_node->next && (current_node->next->h_index == current_node->h_index))
		{
			current_node = current_node->next;
			current_node->h_index++;
		}

		return std::get<0>(for_head_inserting->list_or_text);
	}
	else {
		auto tmp = head;

		head = parse_str_into_node(src_str);

		head->next = tmp;

		current_node = head;

		while (current_node->next && (current_node->next->h_index == current_node->h_index))
		{
			current_node = current_node->next;
			current_node->h_index++;
		}

		return head;
	}
}

void h_content::print(std::shared_ptr<Node> head, std::string index_str)
{
	if (!head) {
		return;
	}

	if (index_str.size())
		std::cout << index_str + '.' + std::to_string(head->h_index) << " " << head->title << " ";
	else
		std::cout << std::to_string(head->h_index) << " " << head->title << " ";

	if (head->list_or_text.index() == 1)
	{
		std::cout << std::get<1>(head->list_or_text) << std::endl;
		print(head->next, index_str);
	}
	else
	{
		std::cout << std::endl;
		if (index_str.size())
			print(std::get<0>(head->list_or_text), index_str + '.' + std::to_string(head->h_index));
		else
			print(std::get<0>(head->list_or_text), std::to_string(head->h_index));

		print(head->next, index_str);
	}
}


std::shared_ptr<Node> h_content::add(std::string &src_str)
{
	if (!head) {
		if (std::find(src_str.begin(), src_str.end(), '.')
			<= std::find(src_str.begin(), src_str.end(), ' ')) {

			std::cout << "Head must be a zero-leve node" << std::endl;
			return nullptr;
		}

		head = parse_str_into_node(src_str);

		return head;
	}

	std::shared_ptr<Node> for_head_inserting;
	auto current_node = head;

	std::string tmp_value_str;

	int tmp_index = 0;

	while (!isspace(src_str[tmp_index]))
	{
		if (src_str[tmp_index] != '.')
			tmp_value_str += src_str[tmp_index++];
		else
		{
			int current_h_index = std::stoi(tmp_value_str);

			while (current_node->h_index != current_h_index) {
				if (current_node->next == nullptr) {

					std::cout << "Non-existent prefix";
					return nullptr;
				}
				current_node = current_node->next;
			}

			if (current_node->list_or_text.index() == 1)
			{
				std::cout << "Non-existent prefix" << std::endl;
				return nullptr;
			}

			if (!std::get<0>(current_node->list_or_text)) {
				if ((std::find(src_str.begin() + tmp_index + 1, src_str.end(), '.')) < (std::find(src_str.begin() + tmp_index + 1, src_str.end(), ' ')))
				{
					std::cout << "Non-existent prefix" << std::endl;
					return nullptr;
				}
				else
				{
					current_node->list_or_text = parse_str_into_node(src_str);
					return std::get<0>(current_node->list_or_text);
				}
			}

			for_head_inserting = current_node;
			current_node = std::get<0>(current_node->list_or_text);

			tmp_index++;
			tmp_value_str = "";
		}
	}

	int current_h_index = std::stoi(tmp_value_str);

	while (current_node->h_index < current_h_index)
	{
		if (current_node->next) {
			if (current_node->next->h_index < current_h_index)
				current_node = current_node->next;
			else if (current_node->next->h_index == current_h_index)
			{
				std::cout << "Node already exists" << std::endl;
				return nullptr;
			}
			else if (current_node->next->h_index > current_h_index)
			{
				auto tmp = current_node->next;

				current_node->next = parse_str_into_node(src_str);

				current_node->next->next = tmp;

				return current_node->next;
			}
		}

		else
		{
			current_node->next = parse_str_into_node(src_str);

			return current_node->next;
		}
	}


	if (for_head_inserting) {

		if (current_node->h_index == current_h_index)
		{
			std::cout << "Node already exists" << std::endl;
			return nullptr;
		}

		for_head_inserting->list_or_text = parse_str_into_node(src_str);

		std::get<0>(for_head_inserting->list_or_text)->next = current_node;

		return std::get<0>(for_head_inserting->list_or_text);
	}
	else {
		if (head->h_index == current_h_index)
		{
			std::cout << "Node already exists" << std::endl;
			return nullptr;
		}
		auto tmp = head;

		head = parse_str_into_node(src_str);

		head->next = tmp;

		return head;
	}
}

void h_content::normalize_row(std::shared_ptr<Node> start, bool recursive)
{
	if (!recursive) {
		int i = 1;

		while (start->next)
		{
			start->h_index = i++;
			start = start->next;
		}

		start->h_index = i;

		return;
	}
	else
	{
		int i = 1;

		while (start->next)
		{
			start->h_index = i++;

			if ((start->list_or_text.index() == 0) && (std::get<0>(start->list_or_text)))
				normalize_row(std::get<0>(start->list_or_text), true);

			start = start->next;
		}

		start->h_index = i;

		if ((start->list_or_text.index() == 0) && (std::get<0>(start->list_or_text)))
			normalize_row(std::get<0>(start->list_or_text), true);

		return;
	}
}

void h_content::normalize(const std::string &start, bool recursive)
{
	if (!head)
	{
		std::cout << "Failed, empty list" << std::endl;
		return;
	}
	if (!start.size())
	{
		if (!recursive) {
			normalize_row(head);
		}

		else {
			normalize_row(head, recursive);
			return;
		}
	}

	else {
		auto current_node = head;

		std::string tmp_value_str;

		size_t tmp_index = 0;

		while (tmp_index < start.size())
		{
			if (start[tmp_index] != '.')
				tmp_value_str += start[tmp_index++];
			else
			{
				int current_h_index = std::stoi(tmp_value_str);

				while (current_node->h_index != current_h_index) {
					if (current_node->next == nullptr)
					{
						std::cout << "Non-existent prefix" << std::endl;
						return;
					}
					current_node = current_node->next;
				}

				if (current_node->list_or_text.index() == 1)
				{
					std::cout << "Non-existent prefix" << std::endl;
					return;
				}

				if (!std::get<0>(current_node->list_or_text)) {
					if ((std::find(start.begin() + tmp_index + 1, start.end(), '.')) < (std::find(start.begin() + tmp_index + 1, start.end(), ' ')))
					{
						std::cout << "Non-existent prefix" << std::endl;
						return;
					}
					else
					{
						std::cout << "Non-existent prefix" << std::endl;
						return;
					}
				}

				current_node = std::get<0>(current_node->list_or_text);

				tmp_index++;
				tmp_value_str = "";
			}
		}

		int current_h_index = std::stoi(tmp_value_str);

		while (current_node->h_index < current_h_index)
		{
			if (current_node->next) {
				if (current_node->next->h_index < current_h_index)
					current_node = current_node->next;
				else if (current_node->next->h_index == current_h_index)
				{
					auto tmp = head;

					head = current_node->next;

					normalize("", recursive);

					head = tmp;
					return;
				}
				else if (current_node->next->h_index > current_h_index)
				{
					std::cout << "Non-existent prefix" << std::endl;
					return;
				}
			}

			else
			{
				std::cout << "Non-existent prefix" << std::endl;
				return;
			}
		}

		normalize_row(head, recursive);
		return;
	}
}
