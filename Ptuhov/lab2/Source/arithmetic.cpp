#include "arithmetic.h"

std::string InputDialog();

std::string OutputDialog();

//функция создает путь или если он не был передан заменяет его дефолтным
std::string MakePath(std::string& s, const std::string default_path);

//вызов функций обработки строки
bool Check(StringPair data_, std::ostream& out, std::shared_ptr<Node>& nd);

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
	return 0;
}

void Arithmetic::SetStringValue(const std::string& new_data)
{
	data_ = new_data;
}

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
void Arithmetic::UpdateMap(const std::string& key, int value)
{
	dict_[key] = value;
}

//проверка на нахождение переданного аргумента в словаре
bool Arithmetic::InMap(const std::string& value)
{
	return dict_.find(value) != dict_.end();
}

//Замена строки вида power(a, b) на значение данной операции 
bool Arithmetic::RemakePowerToInt()
{
	size_t PowerStartInd = data_.rfind("power(");

	//если на очередном вызове функции не было найдено power(, то осуществляется выход из рекурсии с результатом true
	if (PowerStartInd == std::string::npos)
		return true;

	//если подстрока все-таки была найдена, то осуществляется запись значения вида power(..., ...) в переменную PowerData
	size_t CurrentInd = PowerStartInd;
	while (data_[CurrentInd] != ')')
		CurrentInd++;

	size_t PowerEndInd = ++CurrentInd;
	std::string PowerData(data_.begin() + PowerStartInd, data_.begin() + PowerEndInd);
	std::regex regular("power\\([a-zA-Z0-9_]+\\s*,\\s*[a-zA-Z0-9_]+\\)");

	//проверка на корректность ранее записанного power(,) при помощи регулярного выражения
	if (!std::regex_match(PowerData, regular))
		return false;

	//запись возводимого значения в строку VariableName 
	std::string VariableName = "";
	size_t IndexPowerOpenBracket = 6;
	CurrentInd = IndexPowerOpenBracket;

	while (PowerData[CurrentInd] != ' ' && PowerData[CurrentInd] != ',')
	{
		VariableName += PowerData[CurrentInd];
		CurrentInd++;
	}
	std::cout << VariableName << std::endl;

	IntBoolPair value1 = CheckVariable(VariableName);
	if (!value1.second)
		return false;

	//запись степени в строку VariableName
	VariableName.clear();
	CurrentInd = PowerData.find(',');

	while (PowerData[++CurrentInd] != ')')
	{
		if (PowerData[CurrentInd] != ' ')
			VariableName += PowerData[CurrentInd];
	}

	IntBoolPair value2 = CheckVariable(VariableName);
	if (!value2.second)
		return false;

	//если оба числа удалось считать, то значение выражения высчитывается при помощи std::pow и заносится в переменную s
	std::string s = std::to_string(static_cast<int>(std::pow(value1.first, value2.first)));

	//на место power(,) вставляется ранее посчитанное значение
	data_.erase(data_.begin() + PowerStartInd, data_.begin() + PowerEndInd);
	data_.insert(data_.begin() + PowerStartInd, s.begin(), s.end());

	return RemakePowerToInt();
}

//данная функция пытается получить число из переданной строки, если все проходит успешно, то возвращается true и значение считанного числа
IntBoolPair Arithmetic::CheckVariable(std::string& VariableName)
{
	int VariableValue = -1;

	if (!InMap(VariableName))
	{
		std::istringstream stream(VariableName);
		stream >> VariableValue;
		if (stream.fail() || stream.peek() != EOF)
			return std::make_pair(0, false);
	}
	else
		VariableValue = dict_[VariableName];

	return std::make_pair(VariableValue, true);
}

//ввод данных в список
bool Arithmetic::ListFormation(std::shared_ptr<Node>& currentHead, const std::string& currentBracketValue, std::ostream& out)
{

	out << "Next processed brackest value: " + currentBracketValue + "\r\n";
	size_t ind = 0;

	//считывание операции
	while (ind < currentBracketValue.size() && (currentBracketValue[ind] == '(' || currentBracketValue[ind] == ' '))
		ind++;

	//проверка ее на корректность
	if ((currentBracketValue[ind] != '+' && currentBracketValue[ind + 1] == ' ') &&
		currentBracketValue[ind] != '*' &&
		(currentBracketValue[ind] != '-' && currentBracketValue[ind + 1] == ' '))
		return false;

	//создание первого аргумента для оператора
	auto FirstOperatorArg = std::make_shared<Node>();
	currentHead->value = currentBracketValue[ind];

	//переход к следующему элементу
	ind++;
	while (ind < currentBracketValue.size() && currentBracketValue[ind] == ' ')
		ind++;

	//если аргументом оказалось еще одно выражение
	if (currentBracketValue[ind] == '(')
	{
		bool check = ListFormation(FirstOperatorArg, ExtractBracketsValue(currentBracketValue, &ind), out);
		if (!check)
			return false;
	}
	// если аргументом оказалось что-то похожее на число
	else
	{
		IntBoolPair result = ExtractValueForListFormation(currentBracketValue, &ind);
		if (!result.second)
			return false;

		FirstOperatorArg->value = result.first;
	}

	//переход ко второму аргументу
	while (ind < currentBracketValue.size() && currentBracketValue[ind] == ' ')
		ind++;

	//встретили закрывающую скобку - выражение закончено, а значит операция унарная
	if (currentBracketValue[ind] == ')')
	{
		if (std::get<char>(currentHead->value) == '-')
		{
			currentHead->arguments = FirstOperatorArg;
			return true;
		}
		else
			return false;
	}

	//создание второго аргумента для оператора
	auto SecondOperatorArg = std::make_shared<Node>();

	//если вторым аргументом оказалось другое выражение
	if (currentBracketValue[ind] == '(')
	{
		bool check = ListFormation(SecondOperatorArg, ExtractBracketsValue(currentBracketValue, &ind), out);
		if (!check)
			return false;
	}
	//если вторым аргументом оказалось что-то похожее на число
	else
	{
		IntBoolPair result = ExtractValueForListFormation(currentBracketValue, &ind);
		if (!result.second)
			return false;

		SecondOperatorArg->value = result.first;
	}
	//в случае успешного составления обоих аргументов прикрепляем их к нашей операции
	currentHead->arguments = std::make_pair(FirstOperatorArg, SecondOperatorArg);
	return true;
}

//получение числа из строки для предыдущего метода
IntBoolPair Arithmetic::ExtractValueForListFormation(const std::string& s, size_t* indPointer)
{
	std::string tmp = "";

	size_t& ind = *indPointer;
	//считывание значения в переменную tmp
	while (ind < s.size() && s[ind] != ' ' && s[ind] != '(' && s[ind] != ')')
	{
		tmp += s[ind];
		ind++;
	}

	//проверка на то, что считанное значение - переменная
	if (InMap(tmp))
		return std::make_pair(dict_[tmp], 1);

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
std::string Arithmetic::ExtractBracketsValue(const std::string& s, size_t* indPointer)
{
	size_t& ind = *indPointer;
	//error - переменная необходимая для обработки данного случая (...(...)...) она позволяет получить значение 
	//лежащее точно от уже найденной открывающей до корректной закрывающей скобки
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
void Arithmetic::operator<<(std::ostream& out)
{
	for (auto i : dict_)
		out << i.first << " = " << i.second << "\r\n";
}

//распаковка значений переменных
bool Arithmetic::ExtractVariableValues(std::string& value, std::ostream& out)
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
		return 2;

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

std::string MakePath(std::string& s, const std::string default_path)
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

bool Check(StringPair data_, std::ostream& out, std::shared_ptr<Node>& nd)
{
	Arithmetic arithmetic;

	std::string VariableList = data_.second,
		Expression = data_.first;

	//печать входных данных
	out << "\nEntered string: " + Expression + ", Entered variable list: ";
	if (VariableList == "()")
		out << "empty\r\n";
	else
		out << data_.second + "\r\n";

	//Регулярное выражение, создаваемое с целью проверки корректности формата строки, сопоставляющей имена переменных и их значения
	std::regex regular("\\((\\([a-zA-Z0-9_]+ [0-9+-]+\\))+\\)");

	arithmetic.SetStringValue(Expression);

	//Проверка корректности расстановки скобок
	int CheckResult = arithmetic.CheckBrackets();
	if (CheckResult)
	{
		out << ((CheckResult > 0) ? "Oops, you forgot about close bracket(s)\r\n\r\n" : "Oops you forgot about open bracket(s)\r\n\r\n");
		return false;
	}

	//Проверка на корректность полученного списка переменных/значений
	if (VariableList != "()" && !std::regex_match(VariableList.c_str(), regular))
	{
		out << "Incorrect variable list!\r\n\r\n";
		return false;
	}

	//Сопоставление именам переменных их значений
	int check = arithmetic.ExtractVariableValues(VariableList, out);
	if (!check)
		return 0;
	if (check == 2)
	{
		out << "Error - one variable with two values!\n";
		return false;
	}

	//печать словаря если он не пуст
	if (VariableList != "()")
	{
		out << "Variable list after unpacking:\r\n";
		arithmetic << out;
	}

	//Замена power на его значение, а заодно и проверка на корректность записи power
	if (!arithmetic.RemakePowerToInt())
	{
		out << "Incorrect power option!\r\n\r\n";
		return false;
	}
	out << "String version after remake power to int: " + arithmetic.GetStringValue() + "\r\n";

	if (!arithmetic.ListFormation(nd, arithmetic.GetStringValue(), out))
	{
		out << "Incorrect expression!\r\n\r\n";
		return false;
	}

	return true;
}

int main(int argc, char** argv)
{
	//data_ - пара строк: первая - выражение, вторая - список с переменными и их значениями, iovar - input/outpur variant
	StringPair data_, iovar;

	auto nd = std::make_shared<Node>();

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
		{
			if (Check(std::make_pair(FileStrings[i], FileStrings[i + 1]), out, nd))
			{
				out << "Result: " << nd->evaluate() << "\r\n";
				out << "-----------------------------------------------------------------------------------\r\n\r\n";
			}
		}

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

		Check(data_, out, nd);

		out << "Result: " << nd->evaluate() << "\r\n";
		out << "-----------------------------------------------------------------------------------\r\n\r\n";
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
		{
			if (Check(std::make_pair(FileStrings[i], FileStrings[i + 1]), out, nd))
			{
				out << "Result: " << nd->evaluate() << "\r\n";
				out << "-----------------------------------------------------------------------------------\r\n\r\n";
			}
		}
		break;
	}
	default:
		std::cout << "Incorrect input format. Goodbye\n";
		break;
	}

	return 0;
}