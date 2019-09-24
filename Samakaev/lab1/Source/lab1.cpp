#include <iostream>
#include <string>
#include <fstream>


using namespace std;

//является ли начало строки оператором
int is_operand(string s)
{
	if (!s.compare(0, 3, "AND"))
		return 3;
	else if (!s.compare(0, 2, "OR"))
		return 2;
	else return 0;
}
//находит позицию оператора AND или OR
int operand_pos_search(string s)
{
	int len = s.length();
	string side_str;
	int n = 0;
	for (int i = 0; i < len; i++)
	{
		side_str = s;
		if (s[i] == '(')
			n++;
		else if (s[i] == ')')
			n--;
		if (n == 0 && is_operand(side_str.erase(0, i + 1)))
			return i + 1;
	}
	return -1;
}

//основная функция
bool is_prime_logical(string s)
{
	string side_str = s;
	int len = s.length();
	if ((isalpha(s[0]) && len == 1) ||
		(s == "TRUE") ||
		(s == "FALSE"))
		return true;
	else if (!(s.compare(0, 3, "NOT")))
	{
		return is_prime_logical(side_str.erase(0, 3));
	}
	else if (s[0] == '(' && s[len - 1] == ')')
	{
		s.erase(len - 1, 1);
		s.erase(0, 1);
		side_str = s;
		len -= 2;
		int operand_pos = operand_pos_search(s);
		if (operand_pos == -1)
			return false;
		side_str.erase(operand_pos);
		if (is_prime_logical(side_str))
		{
			side_str = s;
			int operand_len = is_operand(side_str.erase(0, operand_pos));
			side_str = s;
			if (is_prime_logical(side_str.erase(0, operand_len + operand_pos)))
				return true;
			else return false;
		}
		else return false;
	}
	else return false;
}

void file_input() {
	string testfile = "C:/Users/admin/Documents/GitHub/ADS-8304/Samakaev/lab1/Tests/Test.txt";
	
	ifstream file;
	file.open(testfile);
	if (!file.is_open()) 
		std::cout << "Error! File isn't open" << endl;
	string str;
	while (!file.eof()) {
		getline(file, str);
		if (is_prime_logical(str))
			std::cout << str << "   is prime logical" << endl;
		else std::cout << str << "   is not prime logical" << endl;
	}
	file.close();
}

void console_input()
{
	string s;
	std::cout << "Enter the pattern to check" << endl;
	cin >> s;
	if (is_prime_logical(s))
		std::cout << s << "   is prime logical" << endl;
	else std::cout << s << "   is not prime logical" << endl;
}

void menu()
{
	int choice = 0;
	std::cout << "-------------------------" << endl;
	std::cout << "Press 1 for file input" << endl;
	std::cout << "Press 2 for console input" << endl;
	std::cout << "Press 3 to quit" << endl;
	std::cout << "-------------------------" << endl;
	cin >> choice;
	switch (choice)
	{
	case 1:
		file_input();
		menu();
		break;
	case 2:
	{
		console_input();
		menu();
		break;
	}
	case 3:
		break;
	default:
		break;
	}
}

int main()
{
	menu();
	return 0;
}
