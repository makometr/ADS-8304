
#include "BracketAnalyzer.h"


BracketAnalyzer::BracketAnalyzer()
{
}


BracketAnalyzer::~BracketAnalyzer()
{
}

std::vector<std::vector<char>> BracketAnalyzer::GetTextData(const char * filename)
{
	std::vector<std::vector<char>> textdata;

	std::vector<char> tmp_vect;

	textdata.push_back(tmp_vect);

	std::ifstream input;

	input.open(filename); //открываем файлик

	if (!input) {
		std::cout << "Couldn't open source file";
		exit(1);
	} //не открываем файлик

	char tmp;

	while (input.get(tmp))
	{
		if (tmp!='\n')
			textdata.back().push_back(tmp);
		else {
			textdata.push_back(tmp_vect); // строка кончилась - заводим новую
		}
	}
	input.close(); 

	return textdata; // возвращаем вектор char-векторов
} 

void BracketAnalyzer::Analyze(const char* textfile, const char* parametersfile)
{
	text = BracketAnalyzer::GetTextData(textfile);
	parameters = BracketAnalyzer::GetTextData(parametersfile); //Начинаем движение. Сначала достали анализируемые строки, потом достали параметры

	while (text.size()) { // пока есть что анализировать

		std::vector<char>::iterator left = text.back().begin();
		std::vector<char>::iterator right = text.back().end(); right--; //всем дальнейшим функциям передаем строку как два итератора 
																		// - один указывает на начало, второй на конец

		if (brackets(left, right)) {
			std::cout << "This is a correct Bracket(T) sequence" << std::endl; //самый внешний вызов
		}
		else {
			std::cout << "This is NOT a correct Bracket(T) sequence" << std::endl; //   -//-
		}

		text.pop_back(); //проанализировали - убрали, идем дальше
		parameters.pop_back();
	}
}

bool BracketAnalyzer::brackets(std::vector<char>::iterator left, std::vector<char>::iterator right)
{
	return (element(left) && (left == right)) || list(left, right);

}

bool BracketAnalyzer::element(std::vector<char>::iterator left)
{
	return (std::find(parameters.back().begin(), parameters.back().end(), *left) != parameters.back().end());
}

bool BracketAnalyzer::list(std::vector<char>::iterator left, std::vector<char>::iterator right)
{
	return ((*left == 'N') && (left == right)) || ((*left == '[') && (*right == ']') && row(left + 1, right - 1)); 
}
//три функции выше совсем дословно повторяет условие задачи - взаимнорекурсивные определения
bool BracketAnalyzer::row(std::vector<char>::iterator left, std::vector<char>::iterator right)
{
	bool result = true;

	while (left != right + 1) {
		if (*left != '[') {
			result = result && brackets(left, left);
			left++;
		}

		else {
			auto tmp_iter = left + 1;
			int cnt = 1;

			while (tmp_iter != right + 1) {
				if (*tmp_iter == '[')
					cnt++;
				if (*tmp_iter == ']')
					cnt--;

				if (!cnt) {
					result = result && row(left + 1, tmp_iter - 1);
					left = tmp_iter + 1;
					break;
				}

				tmp_iter++;
			}

			if (tmp_iter == right + 1)
				return false;
		}
	}
	// если коротко - я знаю, что для меня true_обьект это набор разрешенных символов или true_объект в квадратных скобках
	// поэтому я иду итеративно вправо по строке, смотря на каждый символ, пока не уткнусь в '[' . В этот момент ищу ей пару и отправляю 
	// на анализ содержимое, если пара нашлась
	return result;
}