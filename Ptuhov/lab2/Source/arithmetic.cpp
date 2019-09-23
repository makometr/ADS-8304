#include "arithmetic.h"

//Выбор входного потока
std::string InputDialog();

//Выбор выходного потока
std::string OutputDialog();

//функция создает путь или если он не был передан заменяет его дефолтным
std::string MakePath(std::string s, std::string const default_path);

//вызов функций обработки строки
void CallAndCheck(StringPair data_, std::ostream& out);

//спуск вниз по списку или получение значения текущего атома
int Node::evaluate()
{
	if (std::holds_alternative<char>(value))
	{
		if (std::get<char>(value) == '+')
			return std::get<NodePair>(arguments).first->evaluate() + std::get<NodePair>(arguments).second->evaluate();
		if (std::get<char>(value) == '*')
			return std::get<NodePair>(arguments).first->evaluate() * std::get<NodePair>(arguments).second->evaluate();
		if (std::get<char>(value) == '-')
		{
			if (std::holds_alternative<NodePair>(arguments))
				return std::get<NodePair>(arguments).first->evaluate() - std::get<NodePair>(arguments).second->evaluate();
			else
				return (-1) * std::get<std::shared_ptr<Node>>(arguments)->evaluate();
		}
	}
	else
		return std::get<int>(value);
}

//изменение значения хранящегося в классе arithmetic
void Arithmetic::SetStringValue(std::string const new_data_)
{
	data_ = new_data_;
}

//получение значения хранящегося в классе arithmetic
std::string Arithmetic::GetStringValue()
{
	return data_;
}

//проверка расстановки скобок
int Arithmetic::CheckBrackets()
{
	//ocnt - open cnt, ccnt - close cnt
	int ocnt = 0, ccnt = 0;

	for (char i : data_)
	{
		if (i == '(')
			ocnt++;

		if (i == ')')
			ccnt++;
	}

	return ocnt - ccnt;
}

//добавление новой пары ключ/значение в словарь
void Arithmetic::UpdateMap(const std::string key, int value)
{
	dict[key] = value;
}

//проверка на нахождение переданного аргумента в словаре
bool Arithmetic::InMap(const std::string value)
{
	return dict.find(value) != dict.end();
}

//Замена строки вида power(a, b) на значение данной операции 
bool Arithmetic::RemakePowerToInt()
{
	//находим очередной подстроку вида power( использование rfind обусловлено возможностью такой записи: power(power(, ), )
	size_t PowerStartInd = data_.rfind("power(");

	//если на очередном вызове функции не было найдено power(, то осуществляется выход из рекурсии с результатом true
	if (PowerStartInd == std::string::npos)
		return 1;

	//если подстрока все-таки была найдена, то осуществляется запись значения вида power(..., ...) в переменную PowerData
	size_t tmp = PowerStartInd;
	while (data_[++tmp] != ')') {}

	size_t PowerEndInd = ++tmp;
	std::string PowerData(data_.begin() + PowerStartInd, data_.begin() + PowerEndInd);
	std::regex regular("power\\([a-zA-Z0-9_]+\\s*,\\s*[a-zA-Z0-9_]+\\)");

	//проверка на корректность ранее записанного power(,) при помощи регулярного выражения
	if (!std::regex_match(PowerData, regular))
		return 0;

	//запись возводимого значения в строку VariableName 
	std::string VariableName = "";
	tmp = 6;

	while (PowerData[tmp] != ' ' && PowerData[tmp] != ',') 
	{ 
		VariableName += PowerData[tmp]; 
		tmp++; 
	}
	std::cout << VariableName << std::endl;

	IntBoolPair value1 = PowerHelper(VariableName);
	if (!value1.second)
		return 0;

	//запись степени в строку VariableName
	VariableName.clear();
	tmp = PowerData.find(',');

	while (PowerData[++tmp] != ')') 
	{ 
		if (PowerData[tmp] != ' ') 
			VariableName += PowerData[tmp]; 
	}

	IntBoolPair value2 = PowerHelper(VariableName);
	if (!value2.second)
		return 0;

	//если оба числа удалось считать, то значение выражения высчитывается при помощи std::pow и заносится в переменную s
	std::string s = std::to_string(static_cast<int>(std::pow(value1.first, value2.first)));

	//на место power(,) вставляется ранее посчитанное значение
	data_.erase(data_.begin() + PowerStartInd, data_.begin() + PowerEndInd);
	data_.insert(data_.begin() + PowerStartInd, s.begin(), s.end());

	return RemakePowerToInt();

}

//данная функция пытается получить число из переданной строки, если все проходит успешно, то возвращается true и значение считанного числа
IntBoolPair Arithmetic::PowerHelper(std::string VariableName)
{
	int VariableValue;

	if (!InMap(VariableName))
	{
		std::istringstream stream(VariableName);
		stream >> VariableValue;
		if (stream.fail() || stream.peek() != EOF)
			return std::make_pair(0, 0);
	}
	else
		VariableValue = dict[VariableName];

	return std::make_pair(VariableValue, 1);


}

//ввод данных в список
bool Arithmetic::ListFormation(std::shared_ptr<Node> nd, const std::string s, std::ostream& out)
{
	out << "Next processed brackest value: " + s + "\r\n";
	size_t ind = 0, f;

	while (ind < s.size() && s[ind] == '(' || s[ind] == ' ') { ind++; }


	if ((s[ind] != '+' && s[ind + 1] == ' ') && s[ind] != '*' && (s[ind] != '-' && s[ind + 1] == ' '))
		return 0;

	auto arg1 = std::make_shared<Node>();
	nd->value = s[ind];

	ind++;
	while (ind < s.size() && s[ind] == ' ') { ind++; }

	if (s[ind] == '(')
	{
		f = ListFormation(arg1, ExtractBracketsValue(s, ind), out);
		if (!f)
			return 0;
	}
	else
	{
		IntBoolPair result = ExtractValueForListFormation(s, ind);
		if (!result.second)
			return 0;

		arg1->value = result.first;
	}

	while (ind < s.size() && s[ind] == ' ') { ind++; }

	if (s[ind] == ')')
	{
		if (std::get<char>(nd->value) == '-')
		{
			nd->arguments = arg1;
			return 1;
		}
		else
			return 0;
	}

	auto arg2 = std::make_shared<Node>();

	if (s[ind] == '(')
	{
		f = ListFormation(arg2, ExtractBracketsValue(s, ind), out);
		if (!f)
			return 0;
	}
	else
	{
		IntBoolPair result = ExtractValueForListFormation(s, ind);
		if (!result.second)
			return 0;

		arg2->value = result.first;
	}
	nd->arguments = std::make_pair(arg1, arg2);

	return 1;
}

//получение числа из строки для предыдущего метода
IntBoolPair Arithmetic::ExtractValueForListFormation(const std::string& s, size_t& ind)
{
	std::string tmp = "";

	//считывание значения в переменную tmp
	while (ind < s.size() && s[ind] != ' ' && s[ind] != ')')
	{
		tmp += s[ind];
		ind++;
	}

	//проверка на то, что считанное значение - переменная
	if (InMap(tmp))
		return std::make_pair(dict[tmp], 1);

	//Создаем строковый поток откуда пытаемся считать int
	std::istringstream stream(tmp);
	int result;
	stream >> result;

	//если поток "упал" или не дошел до конца в результате считывания int, то функция возвращает false
	if (stream.fail() || stream.peek() != EOF)
		return std::make_pair(0, 0);

	return std::make_pair(result, 1);
}

//получение значения хранящегося в очередных скобках для предпредыдущего метода
std::string Arithmetic::ExtractBracketsValue(const std::string& s, size_t& ind)
{
	//error - переменная необходимая для обработки данного случая (...(...)...) она позволяет получить значение лежащее точно от уже найденной открывающей до корректной закрывающей скобки
	int tmp_ind = ind, error = 0;
	std::string tmp_s = "";

	while (1)
	{
		//запись очередного символа
		tmp_s += s[tmp_ind];
		tmp_ind++;

		if (s[tmp_ind] == '(')
			error++;
		if (s[tmp_ind] == ')')
			error--;
		if (error < 0)
			break;
	}

	//запись )
	tmp_s += s[tmp_ind];

	//перенос индекса за выражение в скобках дял считывания второго аргумента
	ind = tmp_ind + 1;
	return tmp_s;
}

//вывод словаря
void Arithmetic::print_dict(std::ostream& out)
{
	for (auto i : dict)
		out << i.first << " = " << i.second << "\r\n";
}

//распаковка значений переменных
bool Arithmetic::ExtractVariableValues(std::string value, std::ostream& out)
{
	//выход из рекурсии
	if (value == "()")
		return 1;

	//поиск первого пробела
	size_t ind = value.find(' ');

	//составление имени переменной
	std::string VariableName(value.begin() + 2, value.begin() + ind);

	//проверка на коллизии
	if (InMap(VariableName))
	{
		out << "Incorrect data! One variable with two values!\r\n";
		return 0;
	}
	ind++;

	//запись значения переменной 
	std::string VariableValue;
	while (value[ind] != ')')
	{
		VariableValue += value[ind];
		ind++;
	}

	//использование функции stoi обусловлено проверкой регулярным выражением
	UpdateMap(VariableName, stoi(VariableValue));

	//удаление первой скобки вида (VariableName, VariableValue)
	value.erase(value.begin() + 1, value.begin() + ind + 1);

	//рекурсивный вызов от уже измененной строки
	return ExtractVariableValues(value, out);
}

std::string InputDialog()
{
	std::string ivar;
	std::cout << "Choose input format:\n\t1)Console\n\n\t2) Read from file (Default file is located along the path:"
		"TestInput.txt)\n\tIf you want to change file location, you have to enter path as second argument\n\t"
		"Don't forget to change all \'\\\' to \'/\'" << std::endl;
	std::getline(std::cin, ivar);
	return ivar;
}

std::string OutputDialog()
{
	std::string ovar;
	std::cout << "Choose output format:\n\t1)Console\n\n\t2)File (Default file is located along the path: TestOutput.txt)\n\t"
		"If you want to change file location, you have to enter path as second argument\n\t"
		"Remember that debagging output will be saved with programm result" << std::endl;
	std::getline(std::cin, ovar);
	return ovar;
}

std::string MakePath(std::string s, std::string const default_path)
{
	//Составление пути
	std::string path;

	//запись полученного пути в переменную path
	for (auto i = ++s.begin(); i != s.end(); i++)
		if (*i != ' ')
			path += *i;

	//проверка на то, что путь был введен
	if (path.empty())
		path = default_path;
	return path;
}

void CallAndCheck(StringPair data_, std::ostream& out)
{
	Arithmetic ar;

	//печать входных данных
	out << "\nEntered string: " + data_.first + ", Entered variable list: ";
	if (data_.second == "()")
		out << "empty\r\n";
	else
		out << data_.second + "\r\n";

	//Регулярное выражение, создаваемое с целью проверки корректности формата строки, сопоставляющей имена переменных и их значения
	std::regex regular("\\((\\([a-zA-Z0-9_]+ [0-9+-]+\\))+\\)");

	ar.SetStringValue(data_.first);

	//Проверка корректности расстановки скобок
	int CheckResult = ar.CheckBrackets();
	if (CheckResult)
	{
		out << ((CheckResult > 0) ? "Oops, you forgot about close bracket(s)\r\n\r\n" : "Oops you forgot about open bracket(s)\r\n\r\n");
		return;
	}

	//Проверка на корректность полученного списка переменных/значений
	if (data_.second != "()" && !std::regex_match(data_.second.c_str(), regular))
	{
		out << "Incorrect variable list!\r\n\r\n";
		return;
	}

	//Сопоставление именам переменных их значений
	if (!ar.ExtractVariableValues(data_.second, out))
		return;

	//печать словаря если он не пуст
	if (data_.second != "()")
	{
		out << "Variable list after unpacking:\r\n";
		ar.print_dict(out);
	}

	//Замена power на его значение, а заодно и проверка на корректность записи power
	if (!ar.RemakePowerToInt())
	{
		out << "Incorrect power option!\r\n\r\n";
		return;
	}
	out << "String version after remake power to int: " + ar.GetStringValue() + "\r\n";

	auto nd = std::make_shared<Node>();

	if (!ar.ListFormation(nd, ar.GetStringValue(), out))
	{
		out << "Incorrect expression!\r\n\r\n";
		return;
	}
	out << "Result: " << nd->evaluate() << "\r\n";
	out << "-----------------------------------------------------------------------------------\r\n\r\n";

}

int main(int argc, char** argv)
{
	//data_ - пара строк: первая - выражение, вторая - список с переменными и их значениями, iovar - input/outpur variant
	StringPair data_, iovar;

	//Для удобного запуска тестов на другом пк
	if (argc > 1)
	{
		//Создание потока ввода и чтение данных из него
		std::ifstream in(argv[1]);

		if (!in.is_open())
		{
			std::cout << "Bad way!\n";
			return 0;
		}

		if (in.eof())
		{
			std::cout << "File is empty!\n";
			return 0;
		}

		//Создание вектора дял хранения строк из файла
		std::vector<std::string> FileStrings;
		std::string tmp_s;

		//Считывание данных из файла
		while (std::getline(in, tmp_s))  
			if (!tmp_s.empty()) 
				FileStrings.push_back(tmp_s); 
		
		//Так как для решения подзадачи необходимо иметь 2 строки, то кол-во строк в файле не может быть нечетным
		if (FileStrings.size() % 2)
		{
			std::cout << "String count cannot be odd\n";
			return 0;
		}

		//of - output format
		int of = 0;
		std::ofstream outf;

		//Выбор способа вывода
		iovar.second = OutputDialog();
		switch ((iovar.second)[0])
		{
		case '1':
			//std::cout
			of = 0;
			break;

		case '2':
			//ofstream
			outf.open(MakePath(iovar.second, "TestOutput.txt"));
			if (!outf.is_open())
			{
				std::cout << "File doesn't exist!\n";
				return 0;
			}
			of = 1;
			break;

		default:
			std::cout << "Incorrect output format. Goodbye\n";
			return 0;
		}

		//выбор потока вывода
		std::ostream& out = (of) ? outf : std::cout;

		for (size_t i = 0; i < FileStrings.size(); i += 2)
			CallAndCheck(std::make_pair(FileStrings[i], FileStrings[i + 1]), out);

		if (outf.is_open())
			outf.close();

		return 0;
	}
	else
	{
		//если файл не был передан через командную строку, то необходимо определить формат ввода
		iovar.first = InputDialog();
		iovar.second = OutputDialog();
	}

	bool of = 0;
	std::ofstream outf;

	//Выбор формата ввода
	switch ((iovar.second)[0])
	{
	case '1':
		//std::cout
		of = 0;
		break;

	case '2':
		//ofstream
		of = 1;
		outf.open(MakePath(iovar.second, "TestOutput.txt"));
		if (!outf.is_open())
		{
			std::cout << "File doesn't exist!\n";
			return 0;
		}
		break;

	default:
		std::cout << "Incorrect output format. Goodbye\n";
		return 0;
	}

	std::ostream& out = !of ? std::cout : outf;

	//Выбор формата ввода(если запуск произошел без дополнительных аргументов)
	switch ((iovar.first)[0])
	{
	case '1':
		//std::cin
		std::cout << "Enter string and variable values (input format: ((x1 c1)(x2 c2)...) x1, x2, ... - variables, c1, c2,... - their values),\n"
			"If your variable list is empty left this ()\n";
		std::getline(std::cin, data_.first);
		std::getline(std::cin, data_.second);

		CallAndCheck(data_, out);

		break;

	case '2':
	{
	    //std::ifstream
		std::string path = MakePath(iovar.first, "TestInput.txt");
		std::ifstream in(path);
		if (!in.is_open())
		{
			std::cout << "File doesn't exist!\r\n";
			return 0;
		}

		//аналогично argv создается вектор хранящий в себе все строки файла
		std::vector<std::string> FileStrings;
		std::string tmp_s;
		while (std::getline(in, tmp_s)) 
			if (!tmp_s.empty()) 
				FileStrings.push_back(tmp_s);


		if (FileStrings.size() % 2)
		{
			std::cout << "String count cannot be odd\r\n";
			return 0;
		}

		for (size_t i = 0; i < FileStrings.size(); i += 2)
			CallAndCheck(std::make_pair(FileStrings[i], FileStrings[i + 1]), out);

		break;
	}
	default:
		std::cout << "Incorrect input format. Goodbye\n";
		break;
	}

	return 0;
}
