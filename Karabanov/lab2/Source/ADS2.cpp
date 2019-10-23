#include <iostream>
#include <string>
#include <fstream>

using namespace std;
typedef char base;

struct list {
	base ellem;
	list* next;
	list* parent;
	list* child;
};

list* readlist(std::string s1, unsigned int *i, list* parent) {
	list* head = new list;
	list* cur = head;
	while (*i < s1.length()) {
		if (s1[*i] == '(') {
			(*i) += 1;
			cur->child = readlist(s1, i, cur);
			cur->ellem = '1';
		}
		else if (s1[*i] == ')') {
			(*i)++;
			cur->next = nullptr;
			return head;
		}
		else {
			cur->ellem = s1[*i];
			cur->child = nullptr;
			cur->parent = parent;
			(*i)++;
		}
		if (*i < s1.length() && s1[*i] != ')') {
			cur->next = new list;
			cur = cur->next;
		}
	}
	cur->next = nullptr;
	return head;
}

list* deleteellem(list** head, list** cur) {
	list* ptr;
	if (*cur == *head) {
		(*head) = (*head)->next;
		delete(*cur);
		(*cur) = nullptr;
		*cur = *head;
	}
	else {
		ptr = *head;
		while (ptr->next != *cur) {
			ptr = ptr->next;
		}
		ptr->next = (*cur)->next;
		delete(*cur);
		*cur = ptr;
	}
	return *head;
}

list* checklist(list* head, char ellemfordel) {
	//list* ptr;
	list* cur = head;
	while (cur != NULL) {
		if (cur->ellem == ellemfordel) {
			if (cur == head) {
				head = deleteellem(&head, &cur);
				continue;
			}
			else {
				head = deleteellem(&head, &cur);
			}
		}
		else if (cur->child != nullptr) {
			cur->child = checklist(cur->child, ellemfordel);
			if (cur->child == nullptr) {
				if (cur == head) {
					head = deleteellem(&head, &cur);
					continue;
				}
				else {
					head = deleteellem(&head, &cur);
				}
			}
		}
		cur = cur->next;
	}
	return head;
}


void printlist(list* head) {
	list* cur = head;
	while (cur != nullptr) {
		if (cur->child != nullptr) {
			std::cout << '(';
			printlist(cur->child);
			std::cout << ')';
		}
		else {
			std::cout << cur->ellem;
		}
		cur = cur->next;
	}
}

void destroy(list** head) {
	list* cur = *head;
	while (*head != nullptr) {
		if ((*head)->child != nullptr) {
			destroy(&(cur->child));
		}
		else {
			cur = (*head)->next;
			delete(*head);
			*head = cur;
		}
	}
}

void execute(std::string listStr) {
	unsigned int i = 0;
	list* head = readlist(listStr, &i, nullptr);
	std::cout << "> Enter ellement for delete : ";
	char ellemfordel;
	std::cin >> ellemfordel;
	head = checklist(head, ellemfordel);
	std::cout << "> list after delete : \"";
	printlist(head);
	std::cout << "\"" << std::endl;
	destroy(&head);
}

void ReadFromFile(std::string filename)
{
	std::ifstream file(filename);

	if (file.is_open())
	{
		std::cout << "Reading from file:" << "\n\n";
		int count = 0;
		std::string listStr;
		while (getline(file, listStr))
		{
			count++;
			std::cout << "test #" << count << " \"" + listStr + "\"" << "\n";
			execute(listStr);
		}
	}
	else
	{
		std::cout << "File not opened" << "\n";
	}
}



int main(int argc, char* argv[])
{
	std::cout << "> Choose your input" << std::endl;
	std::cout << "> 0 - from console" << std::endl;
	std::cout << "> 1 - from file" << std::endl;
	std::cout << "> Any other to Exit" << std::endl;
	std::cout << "> ";
	char command = '3';
	std::cin >> command;

	switch (command) {
	case '0': {
		std::string input;
		std::cout << "> Enter List: ";
		std::cin >> input;
		execute(input);
		break;
	}
	case '1': {
		std::cout << "> FilePath: ";
		std::string filePath = argv[1];
		ReadFromFile(filePath);
		break;

	}
	case '3':
	default:
		std::cout << "> Error comand \n> end\n";
	}
	return 0;
}
