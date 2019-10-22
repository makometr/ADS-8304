#include "h_content.h"

std::shared_ptr<Node> h_content::parse_str_into_node(std::string &source_str)
{
	std::string tmp_value_str = "";

	long long unsigned int tmp_index = 0;

	while (!isspace(source_str[tmp_index]))
	{
		if (source_str[tmp_index] != '.')
			tmp_value_str += source_str[tmp_index++];
		else {
			tmp_value_str = "";
			tmp_index++;
		}
	}

	int h_index_value = std::stoi(tmp_value_str); // нам нужно последнее число из подстроки формата "число.число.(и тд)"

	std::string title = "";
	std::string text = "";
	
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

		return result;
	} // либо у нас узел с текстовым содержимым

	else
	{
		while (tmp_index < source_str.size())
			text += source_str[tmp_index++];

		std::shared_ptr<Node> result(new Node);

		result->h_index = h_index_value;
		result->title = title;

		result->list_or_text = text;

		result->next = nullptr;

		return result;
	} // либо узел с подсписком
}

void h_content::load_h_content(std::vector<std::string> &sorted_nodes)
{
	head = parse_str_into_node(sorted_nodes[0]);

	for (long long unsigned int i=1; i < sorted_nodes.size(); i++)
	{
		if (!add(sorted_nodes[i]))
			std::cout << "failed to add" << std::endl; //просто выгрузка исходного содержимого в список добавлением
	}
}

std::shared_ptr<Node> h_content::insert(std::string &src_str)
{
	std::shared_ptr<Node> for_head_inserting;
	auto current_node = head;

	std::string tmp_value_str = "";

	int tmp_index = 0;

	while (!isspace(src_str[tmp_index])) // идем по текущему относительному индексу
	{
		if (src_str[tmp_index] != '.')
			tmp_value_str += src_str[tmp_index++];
		else
		{
			int current_h_index = std::stoi(tmp_value_str);

			while (current_node->h_index != current_h_index) {
				if (current_node->next == nullptr) //не нашли префиксный элемент и уперлись в конец
					return nullptr;
				current_node = current_node->next;
			}

			if (current_node->list_or_text.index() == 1) // пришли в нужный индекс, а это не подсписок
				return nullptr;

			if (!std::get<0>(current_node->list_or_text)) { 
				if ((std::find(src_str.begin() + tmp_index + 1, src_str.end(), '.')) < (std::find(src_str.begin() + tmp_index + 1, src_str.end(), ' ')))
					return nullptr; // если подсписок пустой, а нам ещё в нем после этого надо будет искать подсписки
				else
				{
					current_node->list_or_text = parse_str_into_node(src_str);
					return std::get<0>(current_node->list_or_text); //он пустой, и это последний индекс - ну тогда сюда и пишем
				}
			}
			for_head_inserting = current_node;
			current_node = std::get<0>(current_node->list_or_text); //останется случай, когда надо вставить перед головой подсписка, надо помнить адрес головы

			tmp_index++;
			tmp_value_str = "";
		}
	}

	int current_h_index = std::stoi(tmp_value_str); // последний порядковый индекс, which means мы на финишной прямой

	while (current_node->h_index < current_h_index)
	{
		if (current_node->next) {
			if (current_node->next->h_index < current_h_index) // *ищем*
				current_node = current_node->next;
			else if (current_node->next->h_index == current_h_index) {
				auto tmp = current_node->next;

				current_node->next = parse_str_into_node(src_str);

				current_node->next->next = tmp;

				auto res = current_node->next;

				current_node = current_node->next->next;

				while (current_node->next)
				{
					current_node->h_index++;
					current_node = current_node->next;
				}

				current_node->h_index++;

				return res; // нашли нужный - вставили - остальные инкрементировали
			}
			else if (current_node->next->h_index > current_h_index)
			{
				auto tmp = current_node->next;

				current_node->next = parse_str_into_node(src_str);

				current_node->next->next = tmp;

				return current_node->next; // нашли свободное место, припарковали сюда нашу запись
			}
		}

		else
		{
			current_node->next = parse_str_into_node(src_str);

			return current_node->next; //уперлись в стену, тогда добавляем в конец
		}
	}


	for_head_inserting->list_or_text = parse_str_into_node(src_str);

	std::get<0>(for_head_inserting->list_or_text)->next = current_node;

	return std::get<0>(for_head_inserting->list_or_text); // заменяем голову

}

void h_content::print(std::shared_ptr<Node> head, std::string index_str)
{
	if (!head)
		return;
	
	std::cout << index_str + '.' + std::to_string(head->h_index) << " " << head->title << " "; // собираем полный индекс из частичных
	
	if (head->list_or_text.index() == 1)
	{
		std::cout << std::get<1>(head->list_or_text) << std::endl;
		print(head->next, index_str);
	}
	else
	{
		std::cout << std::endl;
		print(std::get<0>(head->list_or_text), index_str + '.' + std::to_string(head->h_index));
		print(head->next, index_str);
	}
}


std::shared_ptr<Node> h_content::add(std::string &src_str) // работает ровно так же, как add, только бросает Failed,если
							   // запись уже есть, и не инкрементирует остальные после вставки
{
	std::shared_ptr<Node> for_head_inserting;
	auto current_node = head;

	std::string tmp_value_str = "";

	int tmp_index = 0;

	while (!isspace(src_str[tmp_index]))
	{
		if (src_str[tmp_index] != '.')
			tmp_value_str += src_str[tmp_index++];
		else
		{
			int current_h_index = std::stoi(tmp_value_str);

			while (current_node->h_index != current_h_index) {
				if (current_node->next == nullptr)
					return nullptr;
				current_node = current_node->next;
			}

			if (current_node->list_or_text.index() == 1)
				return nullptr;

			if (!std::get<0>(current_node->list_or_text)) {
				if ((std::find(src_str.begin() + tmp_index + 1, src_str.end(), '.')) < (std::find(src_str.begin() + tmp_index + 1, src_str.end(), ' ')))
					return nullptr;
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
				return nullptr;
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


	for_head_inserting->list_or_text = parse_str_into_node(src_str);
	
	std::get<0>(for_head_inserting->list_or_text)->next = current_node;

	return std::get<0>(for_head_inserting->list_or_text);
}

void h_content::normalize_row(std::shared_ptr<Node> start, bool recursive) // по сути эта штука просто принимает сразу указатель на
									   // узел и идет дальше по ним, а normalize ищет точку отсчета
{									   // и отправляет ее в normalize_row.. Ищет по все тем же
	if (!recursive) {						   // принципам - не нашел = fail, уперся в стену = fail и тд
		int i = 0;

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
		int i = 0;

		while (start->next)
		{
			start->h_index = i++;

			if ((start->list_or_text.index() == 0) && (std::get<0>(start->list_or_text)))
				normalize_row(std::get<0>(start->list_or_text), true);

			start = start->next;
		}

		start->h_index = i;

		return;
	}
}

void h_content::normalize(const std::string &start, bool recursive) 
{
	if (!head)
	{
		std::cout << "Failed" << std::endl;
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

		std::string tmp_value_str = "";

		long long unsigned int tmp_index = 0;

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
						std::cout << "Failed" << std::endl;
						return;
					}
					current_node = current_node->next;
				}

				if (current_node->list_or_text.index() == 1)
				{
					std::cout << "Failed" << std::endl;
					return;
				}

				if (!std::get<0>(current_node->list_or_text)) {
					if ((std::find(start.begin() + tmp_index + 1, start.end(), '.')) < (std::find(start.begin() + tmp_index + 1, start.end(), ' ')))
					{
						std::cout << "Failed" << std::endl;
						return;
					}
					else
					{
						std::cout << "Failed" << std::endl;
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

					head = std::get<0>(current_node->next->list_or_text);

					normalize("", recursive);

					head = tmp;
					return;
				}
				else if (current_node->next->h_index > current_h_index)
				{
					std::cout << "Failed" << std::endl;
					return;
				}
			}

			else
			{
				std::cout << "Failed" << std::endl;
				return;
			}
		}

		std::cout << "Failed" << std::endl;
		return;
	}
}
