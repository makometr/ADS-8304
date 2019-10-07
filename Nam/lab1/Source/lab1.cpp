#include <iostream>
#include <string>
#include <fstream>

<<<<<<< HEAD
// Элементы для пользовательского интерфейса;
std::string longLine = "____________________________________________________________________________";
std::string shortLine = "_______________________";

// Вместо тысячи комментариев(Переменные, чтобы не писать лишние комментарии);
std::string enterDialog = "0";
std::string fromConsole = "1";
std::string fromFile = "2";
std::string exit_or_back = "3";
std::string finishProgramm = "100";

/* Функция для ведения диалога с пользователем по поводу формата вывода
(Сделана для того, чтобы в случае ошибки пользователь мог ввести данные еще раз); */
std::string outDialog(std::string option, int flag);

/* Функция для ведения диалога с пользователем по поводу формата ввода
(Сделана для того, чтобы в случае ошибки пользователь мог ввести данные еще раз); */
std::string inDialog(std::string option, int flag);

// Функция, ведущая общий диалог с пользователем и объединяющая данные из outDialog и inDialog;
std::string dialog(std::string inOption, int flag);

// Функция, проверяющая введеную строку на соотвествующие символы
bool checkInputData(std::string inputData);

// Функция, выводящая результат и запускающая функцию analyzer;
void output(std::string workData, std::ostream& out, int i);

// Рекурсивная функция, обрабатывающая введеную пользователем строку;
bool analyzer(std::string& workData, std::ostream& out, int i);

std::string outDialog(std::string option, int flag) {
	std::cout << "\nChoise your output format(Press a number and after press Enter) :\n\n";
	std::cout << "1)Console\n";
	std::cout << "2)Your file(Write a path for your file or write name of file and it will be created in a directory with a code)\n";
	std::cout << "3)Back\n";
	std::cout << "Your choise: ";

	std::string inputData;
	if(flag == 1)
		option = fromFile;
	else
		std::cin >> option;

	if (option == fromConsole)
		return "cout";
	else if (option == fromFile)
	{
		std::cout << "\nInput path for your file.txt and press Enter: ";
		if(flag == 1)
			inputData = "./Tests/TestResult.txt";
		else
		{
			std::cin.ignore();
			std::getline(std::cin, inputData);
			size_t pos = inputData.find(".txt");
			if (pos != std::string::npos)
				inputData.append(".txt");
		}

=======
// Функция для ведения диалога с пользователем по поводу формата вывода(Сделана для того, чтобы в случае ошибки пользователь мог ввести данные заново);
std::string outDialog(int option);

// Функция для ведения диалога с пользователем по поводу формата ввода(Сделана для того, чтобы в случае ошибки пользователь мог ввести данные заново);
std::string InDialog(int option);

// Функция, ведущая общий диалог с пользователем и объединяющая данные с inDialog и outDialog;
void Dialog();

// Функция, проверяющая введенную строку на соотвестующие символы;
bool CheckInputData(std::string inputData);

// Функция, выводящая результат и запускающая функцию  Analyzer;
void Result(std::string _data_, std::ostream& out, int i);

// Рекурсивная функция, обрабатывающая введенную пользователем строку;
bool Analyzer(std::string& _data_, std::ostream& out, int i);

std::string outDialog(int option) {
	std::cout << "\nChoise your output format(Press a number and after press Enter) :\n\n1)Console\n2)Your file(Write a path for your file or write name of file and it will be created in a directory with a code)\n3)Back\nYour choise: ";
	std::string inputData;
	std::cin >> option;
	// Вывод с консоли;
	if (option == 1)
	{
		return "cout";
	}
	// Вывод в файл;
	else if (option == 2)
	{
		std::cout << "\nInput path for your file.txt and press Enter: ";
		std::cin.ignore();
		std::getline(std::cin, inputData);
		size_t pos = inputData.find(".txt");
		if (pos != std::string::npos)
			inputData.append(".txt");
>>>>>>> c8e73a02502d69b9b3383712e43bc214aaae1251
		std::ofstream outFile;
		outFile.open(inputData);
		if (!(outFile.is_open()))
		{
			std::cout << "Incorrect path! Please, try again!\n";
<<<<<<< HEAD
			std::cout << std::endl << longLine;
			return outDialog(option, flag);
		}
		return inputData;
	}
	else if (option == exit_or_back)
	{
		std::cout << std::endl << longLine << std::endl;
		return dialog(enterDialog, flag);
	}
	else
	{
		std::cout << longLine << std::endl  << "Please press not like a dunmb, only three numbers're here -_-" << std::endl << longLine ;
		return outDialog(enterDialog, flag);
	}
}

std::string inDialog(std::string option, int flag)
{
	std::string inputData;
	if (option == fromConsole)
	{
		std::cout << "\nInput your string and press Enter: ";
		std::getline(std::cin, inputData);
		std::cout << longLine;

		if (!checkInputData(inputData))
		{
			std::cout << "\nIncorrect symbols, please, try again!\n";
			std::cout << std::endl << longLine;
			return inDialog(option, flag);
=======
			return outDialog(option);
		}
		return inputData;
	}
	// Вернуться назад, знаю что не очень, но позволяет передумать с вводом :) P.S.: не нажимайте часто  "3";
	else if (option == 3)
	{
		Dialog();
	}
}

std::string InDialog(int option)
{
	std::string inputData;
	// Ввод с консоли;
	if (option == 1)
	{
		std::cout << "\nInput your string and press Enter: ";
		std::getline(std::cin, inputData);
		if (!CheckInputData(inputData))
		{
			std::cout << "\nIncorrect symbols, please, try again!\n";
			return InDialog(option);
>>>>>>> c8e73a02502d69b9b3383712e43bc214aaae1251
		}
		else
			return inputData;
	}
<<<<<<< HEAD
	else if (option == fromFile)
	{
		std::cout << "\nInput path for your file.txt and press Enter:";
		if(flag == 1)
			inputData = "./Tests/TestFile.txt";
		else 
			std::getline(std::cin, inputData);
=======
	// Ввод из файла;
	else if (option == 2)
	{
		std::cout << "\nInput path for your file.txt and press Enter:";
		std::getline(std::cin, inputData);
>>>>>>> c8e73a02502d69b9b3383712e43bc214aaae1251
		std::ifstream inputFile(inputData);
		if (!(inputFile.is_open()))
		{
			std::cout << "Incorrect path! Please, try again!\n";
<<<<<<< HEAD
			std::cout << std::endl << longLine;
			return inDialog(option,flag);
		}
		else
		{
			std::cout << std::endl << longLine << std::endl  << "IT WORKS!" << std::endl << longLine;
			return inputData;
		}
	}
}

std::string dialog(std::string inOption, int flag)
{
	std::cout << "Choise your input format(Press a number and after press Enter):\n\n";
	std::cout << "1)Console\n";
	std::cout << "2)Open your file(Write the path to your file)\n";
	std::cout << "3)Exit\n";
	std::cout << "Your choise: ";

	std::string outOption = "0";
	std::ofstream out;
	std::string inputData;
	std::string outPath;
	
	if(flag == 1)
		inOption = fromFile;
	else 
	{
		std::cin >> inOption;
		// Чтобы функция std::getline() работала корректо;
		std::cin.ignore();
		std::cout << longLine;
	}
	
	if (inOption == fromConsole)
	{
		inputData = inDialog(fromConsole, flag);
		outPath = outDialog(outOption, flag);
		
		if (outPath == "cout")
		{
			std::ostream& workStream = std::cout;
			output(inputData, workStream, 0);
=======
			return InDialog(option);
		}
		else return inputData;
	}
}

void Dialog()
{
	std::cout << "Choise your input format(Press a number and after press Enter):\n\n1)Console\n2)Open your file(Write the path to your file)\n3)Exit\n4)For sensei ;)\nYour choise:";
	int inOption = 0;
	int outOption = 0;
	std::ofstream out;
	std::string inputData;
	std::string outPath;
	std::cin >> inOption;
	// Нужно, чтобы  std::getline() работал корректно во всех случаях;
	std::cin.ignore();
	// Ввод с консоли;
	if (inOption == 1)
	{
		inputData = InDialog(1);
		outPath = outDialog(outOption);
		if (outPath == "cout")
		{
			std::ostream& workStream = std::cout;
			Result(inputData, workStream, 0);
>>>>>>> c8e73a02502d69b9b3383712e43bc214aaae1251
		}
		else
		{
			out.open(outPath);
			std::ostream& workStream = out;
<<<<<<< HEAD
			output(inputData, workStream, 0);
		}
	}
	else if (inOption == fromFile)
	{
		inputData = inDialog(inOption, flag);
		std::string dataFile;
		std::ifstream inputFile(inputData);
		outPath = outDialog(outOption, flag);
		
=======
			Result(inputData, workStream, 0);
		}
	}
	// Ввод из файла;
	else if (inOption == 2)
	{
		inputData = InDialog(2);
		std::string dataFile;
		std::ifstream inputFile(inputData);
		outPath = outDialog(outOption);
>>>>>>> c8e73a02502d69b9b3383712e43bc214aaae1251
		if (outPath == "cout")
		{
			std::ostream& workStream = std::cout;
			while (std::getline(inputFile, dataFile))
			{
<<<<<<< HEAD
				if (!checkInputData(dataFile))
				{
					workStream << std::endl << longLine << std::endl << "Your input: " + dataFile << std::endl << "Result: False - incorrect symbols\n" << std::endl << longLine;
					continue;
				}
				output(dataFile, workStream, 0);
=======
				if (!CheckInputData(dataFile))
				{
					workStream << std::endl << "____________________________________________________________________________" << std::endl << "Your input: " + dataFile << std::endl << "Result: False - incorrect symbols\n" << std::endl << "____________________________________________________________________________";
					continue;
				}
				Result(dataFile, workStream, 0);
>>>>>>> c8e73a02502d69b9b3383712e43bc214aaae1251
			}
		}
		else
		{
			out.open(outPath);
			std::ostream& workStream = out;
			while (std::getline(inputFile, dataFile))
			{
<<<<<<< HEAD
				if (!checkInputData(dataFile))
				{
					workStream << std::endl << longLine << std::endl << "Your input: " + dataFile << std::endl << "Result: False - incorrect symbols\n" << std::endl << longLine;
					continue;
				}
				output(dataFile, workStream, 0);
=======
				if (!CheckInputData(dataFile))
				{
					workStream << std::endl << "____________________________________________________________________________" << std::endl << "Your input: " + dataFile << std::endl << "Result: False - incorrect symbols\n" << std::endl << "____________________________________________________________________________";
					continue;
				}
				Result(dataFile, workStream, 0);
>>>>>>> c8e73a02502d69b9b3383712e43bc214aaae1251
			}
		}

	}
<<<<<<< HEAD
	else if (inOption == exit_or_back)
	{
		return finishProgramm;
	}
	// В случае неккоректного выбора параметра(опции);
	else
	{
		std::cout << std::endl << "\nPlease press not like a dunmb, only three numbers're here -_-\n"  << std::endl << longLine << std::endl;
		return dialog(enterDialog, flag);
	}

	char quest;
	std::cout << std::endl << "Mission complete!" << std::endl;
	std::cout << std::endl << "Do you want to retry?(y/n)" << std::endl;
	
	std::cin >> quest;
	std::cout << longLine << std::endl << std::endl;
	
	if (quest == 'y')
		return dialog(enterDialog, flag);
	else
		return finishProgramm;
}

bool checkInputData(std::string inputData)
{
	for (int i = 0; i < inputData.size(); i++)
		if (inputData[i] != 'A' && inputData[i] != 'B' && inputData[i] != '(' && inputData[i] != ')' && inputData[i] != ' ' && inputData[i] != '\0')
			return false;
	return true;
}

void output(std::string workData, std::ostream& out, int i)
{
	out << std::endl << longLine << std::endl;
	out << std::endl << "Your string is " + workData + "\nResult: " << std::boolalpha << analyzer(workData, out, i);
	out << std::endl << longLine << std::endl;
}

bool analyzer(std::string& workData, std::ostream& out, int i)
{
	out << std::endl << "Depth:" << i << std::endl << "String looks:" << workData << std::endl << shortLine;
	if (workData == "x")
		return true;
	
	std::size_t objA = workData.find("A");
	std::size_t objB = workData.find("B");
	
	if (objA != std::string::npos)
	{
		workData.erase(objA + workData.begin(), objA + workData.begin() + 1);
		workData.insert(objA + workData.begin(), 'x');
		return analyzer(workData, out, ++i);
	}
	else if (objB != std::string::npos)
	{
		workData.erase(objB + workData.begin(), objB + workData.begin() + 1);
		workData.insert(objB + workData.begin(), 'x');
		return analyzer(workData, out, ++i);
	}
	else
	{
		size_t obj = workData.find("(x x)");
		if (obj == std::string::npos)
			return false;
		
		workData.erase(obj + workData.begin(), obj + workData.begin() + 5);
		workData.insert(obj + workData.begin(), 'x');
		return analyzer(workData, out, ++i);
	}

}

int main(int argc, char* argv[])
{
	std::cout << "\tHELLO! THIS IS SUPER SYNTAX ANALYZER!" << "THIS IS PROGRAMM FOR ANALYZE YOUR STRING IF IT IS x::= A|B|(xx)\n\n";
	int flag = 0;
	
	if(argc == 2)
		flag = 1;

	if (dialog(enterDialog, flag) == finishProgramm)
		std::cout << "Goodbye, CYA later!";
	else
		std::cout << "Impooooosible, errroooorrrrr";
	
	return 0;
}
=======
	// В случае выхода из программы;
	else if (inOption == 3)
	{
		std::cout << "Goodbye, CYA later!";
		return;
	}
	// В случае, если пользователь промахнулся или дурак;
	else
	{
		std::cout << "\nPlease press not like a dumb, only four numbers're here -_-\n";
		Dialog();
	}

	char quest;
	std::cout << "Mission complete!" << std::endl;
	std::cout << std::endl << "Do you want to retry?(y/n)" << std::endl;
	std::cin >> quest;
	if (quest == 'y')
		Dialog();
	else
		std::cout << std::endl << "Goodbye!=)";
}

bool CheckInputData(std::string inputData)
{
	for (int i = 0; i < inputData.size(); i++)
		if (inputData[i] != 'A' && inputData[i] != 'B' && inputData[i] != '(' && inputData[i] != ')' && inputData[i] != ' ')
			return 0;
	return 1;
}

void Result(std::string _data_, std::ostream& out, int i)
{
	out << std::endl << "____________________________________________________________________________" << std::endl;
	out << std::endl << "Your string is " + _data_ + "\nResult: " << std::boolalpha << Analyzer(_data_, out, i);
	out << std::endl << "____________________________________________________________________________" << std::endl;
}

bool Analyzer(std::string& _data_, std::ostream& out, int i)
{
	// Отладочные выводы
	out << std::endl << "Depth:" << i << std::endl << "String looks:" << _data_ << std::endl << "_______________________";
	if (_data_ == "x")
		return 1;
	std::size_t objA = _data_.find("A");
	std::size_t objB = _data_.find("B");
	if (objA != std::string::npos)
	{
		_data_.erase(objA + _data_.begin(), objA + _data_.begin() + 1);
		_data_.insert(objA + _data_.begin(), 'x');
	}
	else if (objB != std::string::npos)
	{
		_data_.erase(objB + _data_.begin(), objB + _data_.begin() + 1);
		_data_.insert(objB + _data_.begin(), 'x');
	}
	else
	{
		size_t obj = _data_.find("(x x)");
		if (obj == std::string::npos)
			return 0;
		_data_.erase(obj + _data_.begin(), obj + _data_.begin() + 5);
		_data_.insert(obj + _data_.begin(), 'x');
	}
	return Analyzer(_data_, out, ++i);
}

int main()
{
	std::cout << "\tHELLO! THIS IS SUPER SYNTAX ANALYZER!" << "THIS IS PROGRAMM FOR ANALYZE YOUR STRING IF IT IS x::= A|B|(xx)\n\n";
	Dialog();
	return 0;
}
>>>>>>> c8e73a02502d69b9b3383712e43bc214aaae1251
