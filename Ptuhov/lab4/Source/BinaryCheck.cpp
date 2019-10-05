#include "BinaryTree.h"

void workWithStringTreeForm(std::string& currentCheckTree, std::ostream& out)
{
	//удаление пробелов
	currentCheckTree.erase(std::remove_if(currentCheckTree.begin(), currentCheckTree.end(), [](char c) {return c == ' '; }), currentCheckTree.end());

	if (!checkBracketsPlacement(currentCheckTree))
	{
		out << "Hmm, uncorect brackets statement\n";
		return;
	}

	//запись значения хранящегося в главном узле в переменную variableStringValue
	size_t stringIndex = 1;
	std::string variableStringValue;
	while (currentCheckTree[stringIndex] != '(' && currentCheckTree[stringIndex] != ')' &&
		stringIndex < currentCheckTree.size())
	{
		variableStringValue += currentCheckTree[stringIndex];
		stringIndex++;
	}
	//

	//если дерево состоит из одного узла, то в нем не может быть повторяющихся узлов
	if (currentCheckTree[stringIndex] == ')')
	{
		out << "NO" << std::endl;
		return;
	}
	//

	//Определение типа ранее считанного значения
	int variableType = getVariableType(variableStringValue);
	switch (variableType)
	{
	case 1:
		workWithTree<int>(currentCheckTree, out);
		break;

	case 2:
		workWithTree<double>(currentCheckTree, out);
		break;

	case 3:
		workWithTree<char>(currentCheckTree, out);
		break;

	case 4:
		workWithTree<std::string>(currentCheckTree, out);
		break;
	}
}

bool checkBracketsPlacement(std::string const& checkString)
{
	if (*checkString.begin() != '(' || *(checkString.end() - 1) != ')')
		return 0;

	size_t ocnt = 0;
	size_t ccnt = 0;

	for (char symb : checkString)
	{
		if (symb == '(')
			ocnt++;

		if (symb == ')')
			ccnt++;

		if (ccnt > ocnt)
			return 0;
	}

	return ccnt == ocnt;
}

std::string extractBracketsValue(std::string const& stringTreeForm, size_t* stringIndexPointer)
{
	//error - переменная необходимая для обработки данного случая (...(...)...) она позволяет получить значение 
	//лежащее точно от уже найденной открывающей до корректной закрывающей скобки
	size_t tmp_ind = *stringIndexPointer;
	int error = 0;
	std::string bracketsValue;

	while (1)
	{
		//запись очередного символа
		bracketsValue += stringTreeForm[tmp_ind];
		tmp_ind++;

		if (stringTreeForm[tmp_ind] == '(')
			error++;
		if (stringTreeForm[tmp_ind] == ')')
			error--;
		if (error < 0)
			break;
	}

	//запись ')'
	bracketsValue += stringTreeForm[tmp_ind];

	//перенос индекса за выражение в скобках дял считывания второго аргумента
	*stringIndexPointer = tmp_ind + 1;
	return bracketsValue;
}

int main(int argc, char** argv)
{
	if (argc > 2)
	{
		std::ifstream in(argv[1]);
		std::ofstream out(argv[2]);

		if (!in.is_open())
		{
			std::cout << "Hmmm, maybe you will give me input file that exist? Goodbye\n";
			return 0;
		}

		if (!out.is_open())
		{
			std::cout << "Hmmm, maybe you will give me output file that exist? Goodbye\n";
			return 0;
		}

		std::string currentCheckTree;
		while (std::getline(in, currentCheckTree))
		{
			if (!currentCheckTree.empty() && *(currentCheckTree.end() - 1) == '\r')
				currentCheckTree.erase(currentCheckTree.end() - 1);

			workWithStringTreeForm(currentCheckTree, out);
		}

		return 0;
	}

	std::string stringTreeForm;
	std::cout << "Enter binary tree:";
	std::getline(std::cin, stringTreeForm);

	workWithStringTreeForm(stringTreeForm, std::cout);

	return 0;
}
