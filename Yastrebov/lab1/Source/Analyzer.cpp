#include "BracketAnalyzer.h"


int main(int argc, char* argv[]) // пользуемся аргументами cmd для тестирования
{
	BracketAnalyzer analyzer; // создаем анализтор

	if (argc == 3)
		analyzer.Analyze(argv[1],argv[2]);
	else 
		analyzer.Analyze("SourceString.txt", "ParameterChars.txt"); // если не передали конкретные тестовые файлы, ищет дефолтные

	std::getchar();

	return 0;
}
