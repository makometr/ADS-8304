#include <iostream> // std::cin, std::cout, std::ostream
#include <string> // std::string и сопутствующие функции
#include <fstream> // std::ofsrteam

//Функция, ведущая диалог с пользователем
void Dialog();

//Функция, проверяющая отсутсвие нешаблонных символов в принятой строке
bool check_strElements(std::string s);

//Функция, которая возвращает извлеченный из принять строки путь до файла сохранения
std::string make_path(std::string var, std::string default_path);

//Функция, вызывающая для полученной строки s функцию check
void call(std::string s, std::ostream& out);

//Рекурсивная функция, осуществляющая проверку введенной пользователем строки
bool check(std::string& terminate, std::ostream& out, size_t n = 0);

//Функция преобразующая значение типа bool в значение типа std::string
std::string bool_to_string(bool a);


void Dialog()
{
	//of - output format
	int  of;
	// ivar - input variant, ovar - output variant
	std::string ivar, ovar;
	//out - поток вывод, зависящий от выбора пользователя
	std::ofstream out;

	//Считывание введенной пользователем команды, использование std::getline обусловлено возможным наличием пробельных символов в считываемой строке 
	std::getline(std::cin, ivar);

	std::cout << "Choose output format:\n\t1)Console\n\n\t2)File (Default file is located along the path: D:/LAB1_SOURCE/OutputSource.txt)\n\t"
		"If you want to change file location, you have to enter path as second argument\n\t"
		"Remember that debagging output will be saved with programm result\n";
	std::getline(std::cin, ovar);

	switch (ovar[0])
	{
	case '1':
		//создание стандартного потока вывода
		of = 0;
		break;

	case '2':
		//создание файлового потока вывода с сопутствующей проверкой
		out.open(make_path(ovar, "/mnt/c/Users/denis/ADS-8304/Ptuhov/lab1/Tests/TestResult.txt"));
		if (!(out.is_open()))
		{
			std::cout << "Incorrect path!!!\n";
			return;
		}
		of = 1;
		break;

		//иные случаи
	default:
		std::cout << "Goodbye\n" << std::endl;
		return;
	}

	//считывание входных данных через консоль
	if (ivar[0] == '1')
	{
		std::string s;

		std::cout << "Enter string:\n";
		std::getline(std::cin, s);
		std::cout << std::endl;

		//выбор потока вывода
		std::ostream& tmp = !of ? std::cout : out;

		//проверка на отсутствие "лишних" символов
		if (!check_strElements(s))
		{
			tmp << "Entered string: " + s + "\nResult: False - Incorrect symbols\r\n";
			tmp << "---------------------------------------------------------------------------------------------------\r\n";
			return;
		}

		call(s, tmp);
	}
	//считывание входных данных через файл
	else if (ivar[0] == '2')
	{
		std::string data_;

		//открытие потока
		std::ifstream f(make_path(ivar, "/mnt/c/Users/denis/ADS-8304/Ptuhov/lab1/Tests/TestFile.txt"));

		//выбор потока вывода
		std::ostream& tmp = !of ? std::cout : out;

		//проверка на то, что поток действительно был открыт
		if (!(f.is_open()))
		{
			std::cout << "Incorrect path!!!\r\n";
			return;
		}

		//считывание данных из файла

		while (std::getline(f, data_))
		{
			//удаление символа конца строки 
			data_.erase(data_.end() - 1);

			//проверка на отсутствие "лишних" символов
			if (!check_strElements(data_))
			{
				tmp << "Entered string: " + data_ + "\nResult: False - Incorrect symbols\r\n";
				tmp << "---------------------------------------------------------------------------------------------------------------\r\n";
				continue;
			}

			call(data_, tmp);
		}
	}
	//иные случаи
	else
	{
		std::cout << "Goodbye!\n";
		return;
	}

}

bool check_strElements(std::string s)
{
	for (int i = 0; i < s.size(); i++)
		if (s[i] != 'A' && s[i] != 'B' && s[i] != '(' && s[i] != ')' && s[i] != ' ')
			return 0;
	return 1;
}

std::string make_path(std::string var, std::string default_path)
{
	std::string path;
	std::string data_;

	//запись полученного пути в переменную path
	for (auto i = ++var.begin(); i != var.end(); i++)
		if (*i != ' ')
			path += *i;

	//проверка на то, что путь был введен
	if (path.empty())
		path = default_path;
	return path;
}

void call(std::string s, std::ostream& out)
{
	std::string message = "Entered string: " + s;
	out << message + "\r\n" << "Result: " + bool_to_string(check(s, out)) << "\r\n";
	out << "---------------------------------------------------------------------------------------------------\r\n";
}

bool check(std::string& terminate, std::ostream& out, size_t n)
{
	//Отладочные выводы
	out << "Value of the check-string after the next function call : " << terminate + "\r\n\r\n";
	out << "Recursion depth: \r\n" << "------------------\r\n";

	//Выход из рекурсии, если дальнейшая замена подстроки (B A A) на подстроку А бесполезно
	if (terminate == "A")
		return 1;

	//Нахождение очередной подстроки (B A A)
	size_t it = terminate.find("(B A A)");

	//Проверка на наличие вышеуказанной подстроки
	if (it == std::string::npos)
		return 0;

	//Удаление подстроки (B A A) из ввденной пользователем строки
	terminate.erase(it + terminate.begin(), it + terminate.begin() + 7);

	//Вставка на место удаленной подстроки символа А
	terminate.insert(it + terminate.begin(), 'A');

	//Рекурсивный вызов функции от измененной строки
	return check(terminate, out, ++n);
}

std::string bool_to_string(bool a)
{
	return a ? "True" : "False";
}

int main()
{
	std::cout << "Choose input format:\n\t1)Enter string\n\n\t2) Read from file (Default file is located along the path:"
		"D:/LAB1_SOURCE/InputSource.txt)\n\tIf you want to change file location, you have to enter path as second argument\n\t"
		"Don't forget to change all \'\\\' to \'/\'\n";
	//Чтение входной строки (использование getline обусловлено возможностью присутсвия пробелов во входной строке)
	Dialog();

	return 0;

}
