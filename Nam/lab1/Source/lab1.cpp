#include <iostream>
#include <string>
#include <fstream>

// Ôóíêöèÿ, âåäóùàÿ äèàëîã ñ ïîëüçîâàòåëåì ïî ïîâîäó ôîðìàòà âûâîäà(Ñäåëàíà äëÿ òîãî, ÷òîáû â ñëó÷àå îøèáêè, ïîëüçîâàòåëü ìîã ââåñòè äàííûå çàíîâî);
std::string outDialog(int option);

// Ôóíêöèÿ, âåäóùàÿ äèàëîã ñ ïîëüçîâàòåëåì ïî ïîâîäó ôîðìàòà ââîäà(Ñäåëàíà äëÿ òîãî, ÷òîáû â ñëó÷àå îøèáêè, ïîëüçîâàòåëü ìîã ââåñòè äàííûå çàíîâî);
std::string InDialog(int option);

// Ôóíêöèÿ, âåäóùàÿ îáùèé äèàëîã è îáúåäèíÿþùàÿ ââåäåííûå äàííûå èç outDialog è InDialog;
void Dialog();

// Ôóíêöèÿ, ïðîâåðÿþùàÿ ââåäåííóþ ñòðîêó íà íàëè÷èå íàøèõ ñèìâîëîâ;
bool CheckInputData(std::string inputData);

// Ôóíêöèÿ, âûâîäÿùàÿ ðåçóëüòàò, à òàê æå âûçûâàþùàÿ ôóíêöèþ Analyzer;
void Result(std::string _data_, std::ostream& out, int i);

// Ðåêóðñèâíàÿ ôóíöèÿ, îáðàáàòûâàþùàÿ ââåäåíóþ ïîëüçîâàòåëåì ñòðîêó;
bool Analyzer(std::string& _data_, std::ostream& out, int i);

std::string outDialog(int option) {
	std::cout << "\nChoise your output format(Press a number and after press Enter) :\n\n1)Console\n2)Your file(Write a path for your file or write name of file and it will be created in a directory with a code)\n3)Back\nYour choise: ";
	std::string inputData;
	std::cin >> option;
	// Âûâîä ñ êîíñîëè;
	if (option == 1)
	{
		return "cout";
	}
	// Âûâîä â ôàéë;
	else if (option == 2)
	{
		std::cout << "\nInput path for your file.txt and press Enter: ";
		std::cin.ignore();
		std::getline(std::cin, inputData);
		size_t pos = inputData.find(".txt");
		if (pos != std::string::npos)
			inputData.append(".txt");
		std::ofstream outFile;
		outFile.open(inputData);
		if (!(outFile.is_open()))
		{
			std::cout << "Incorrect path! Please, try again!\n";
			return outDialog(option);
		}
		return inputData;
	}
	// Âåðíóòüñÿ íàçàä, çíàþ, ÷òî ýòî íå î÷åíü õîðîøî, íî çàòî ðàáîòàåò è åñòü âîçìîæíîñòü ïåðåäóìàòü ;) P.S.: Òîëüêî ìíîãî ðàç íå íàæèìàéòå íà "3";
	else if (option == 3)
	{
		Dialog();
	}
}

std::string InDialog(int option)
{
	std::string inputData;
	// Âââîä ñ êîíñîëè;
	if (option == 1)
	{
		std::cout << "\nInput your string and press Enter: ";
		std::getline(std::cin, inputData);
		if (!CheckInputData(inputData))
		{
			std::cout << "\nIncorrect symbols, please, try again!\n";
			return InDialog(option);
		}
		else
			return inputData;
	}
	// Ââîä èç ôàéëà;
	else if (option == 2)
	{
		std::cout << "\nInput path for your file.txt and press Enter:";
		std::getline(std::cin, inputData);
		std::ifstream inputFile(inputData);
		if (!(inputFile.is_open()))
		{
			std::cout << "Incorrect path! Please, try again!\n";
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
	// Íóæíî, ÷òîáû std::getline() ðàáîòàë êîððåêòíî;
	std::cin.ignore(); 
	// Ââîä ñ êîíñîëè;
	if (inOption == 1)
	{
		inputData = InDialog(1);
		outPath = outDialog(outOption);
		if (outPath == "cout")
		{
			std::ostream& workStream = std::cout;
			Result(inputData, workStream, 0);
		}
		else
		{
			out.open(outPath);
			std::ostream& workStream = out;
			Result(inputData, workStream, 0);
		}
	}
	// Ââîä èç ôàéëà;
	else if (inOption == 2)
	{
		inputData = InDialog(2);
		std::string dataFile;
		std::ifstream inputFile(inputData);
		outPath = outDialog(outOption);
		if (outPath == "cout")
		{
			std::ostream& workStream = std::cout;
			while (std::getline(inputFile, dataFile))
			{
				if (!CheckInputData(dataFile))
				{
					workStream << std::endl << "____________________________________________________________________________" << std::endl << "Your input: " + dataFile << std::endl << "Result: False - incorrect symbols\n" << std::endl << "____________________________________________________________________________";
					continue;
				}
				Result(dataFile, workStream, 0);
			}
		}
		else
		{
			out.open(outPath);
			std::ostream& workStream = out;
			while (std::getline(inputFile, dataFile))
			{
				if (!CheckInputData(dataFile))
				{
					workStream << std::endl << "____________________________________________________________________________" << std::endl << "Your input: " + dataFile << std::endl << "Result: False - incorrect symbols\n" << std::endl << "____________________________________________________________________________";
					continue;
				}
				Result(dataFile, workStream, 0);
			}
		}

	}
	// Âûõîä èç ïðîãðàììû;
	else if (inOption == 3)
	{
		std::cout << "Goodbye, CYA later!";
		return;
	}
	// Â ñëó÷àå íåêêîðåêòíîé âûáðàííîé îïöèè;
	else
	{
		std::cout << "\nPlease press not like a dunmb, only four numbers're here -_-\n";
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
