#include "bin_tree.h"

void code(std::ifstream& in, std::ofstream& out, std::ofstream& dem);
bool decode(std::ifstream& in, std::ofstream& out, std::ofstream& dem);
void readFile(std::string&, std::ifstream&);

int main(int argc, char* argv[])
{
	if(argc == 3) {
		std::ifstream in(argv[1]);
		std::ofstream out(argv[2]);
		std::ofstream dem("Demonstration");
		if(!in.is_open() || !out.is_open() || !dem.is_open()) {
			std::cout << "Не удалось открыть файл:(" << std::endl;
			return 0;
		}
		std::cout << "Выберите что сделать?\n1)Кодировать из " << argv[1] << " в " << argv[2] << "\n2)Декодировать из " << argv[1] << " в " << argv[2] << std::endl;
		int option;
		std::cin >> option;
		std::cout << std::endl;
		switch(option) {
			case 1:
				code(in , out, dem);
				std::cout << "Данные файла " << argv[1] << " были закодированы в файл " << argv[2] << std::endl;
				std::cout << "Демонстрацию кодирования смотри в файле Demonstration" << std::endl;
				break;
			case 2:
				if(decode(in , out, dem)) {
					std::cout << "Данные файла " << argv[1] << " были декодированы в файл " << argv[2] << std::endl;
					std::cout << "Демонстрацию декодирования смотри в файле Demonstration" << std::endl;
				}
				else {
					std::cout << "Файл " << argv[1] << " не является закодированным текстом" << std::endl;
					return 0;
				}
				break;
			default:
				std::cout << "Опции с таким номером нет(" << std::endl;
				break;
		}
	}
	else {
		std::cout << "Введите имена файлов, откуда и куда кодировать/декодировать!" << std::endl;
	}
	return 0;
}

void readFile(std::string& str, std::ifstream& in) {
		std::string cur_str;
		while (std::getline(in, cur_str)) {
			str += cur_str;
			str += '\n';
		}
		if(str.size()) {
			str.pop_back();
		}
}

void code(std::ifstream& in, std::ofstream& out, std::ofstream& dem) {
		bin_tree my_tree;
		dem << "Начальное состояние дерева" << std::endl;
		my_tree.print(0, 0, dem);
		std::string cur_text;
		readFile(cur_text, in);
		int cur_parent, num;

		for(char ch: cur_text) {
			num = my_tree.find(ch);
			if(my_tree.size() == (size_t)num + 1) {
				dem << std::endl << "Следующего символа '"<< ch <<"' нет в дереве => добавляем элемент (Выводим: ";
			}
			else {
				dem << std::endl << "Следующий символ '" << ch << "' есть в дереве (Выводим: ";
			}
			std::string stack;
			while(num != 0) {
				cur_parent = my_tree.get(num).parent;
				if(my_tree.get(cur_parent).left == num) stack += '0';
				else stack += '1';
				num = cur_parent;
			}
			for(auto i = stack.rbegin(); i != stack.rend(); ++i) {
				out << *i;
				dem << *i;
			}
			if(my_tree.find(ch) + 1 == my_tree.size()) {
				my_tree.add(ch);
				out << ch;
				dem << ch << ")" << std::endl << "Состояние дерева после добавления:" << std::endl;
				my_tree.print(0, 0, dem);
			}
			else {
				dem << ")" << std::endl;
			}
			my_tree.rebuild(ch);
			dem << "Состояние дерева после перестройки:" << std::endl;
			my_tree.print(0, 0, dem);
		}
	}

bool decode(std::ifstream& in, std::ofstream& out, std::ofstream& dem) {
		bin_tree my_tree;
		dem << "Начальное состояние дерева" << std::endl;
		my_tree.print(0, 0, dem);
		std::string cur_text;
		readFile(cur_text, in);
		int num;

		for(size_t i = 0; i < cur_text.size(); ++i) {
			num = 0;
			while(my_tree.get(num).symbol == '\0') {
				if(my_tree.get(num).count == 0) break;
				if(cur_text[i] == '1') {
					num = my_tree.get(num).right;
				}
				else {
					if(cur_text[i] == '0') {
						num = my_tree.get(num).left;
					}
					else {
						dem << std::endl << "Файл не является закодированным текстом, выход из программы...";
						return false;
					}
				}
				++i;
			}

			if(my_tree.get(num).count == 0) {
				dem << std::endl << "Идя по пути из закодированного файла встретили пустой лист => добавляем в дерево (Выводим: '" << cur_text[i] << "')" << std::endl;
				my_tree.add(cur_text[i]);
				out << cur_text[i];
				dem << "Состояние дерева после добавления:" << std::endl;
				my_tree.print(0, 0, dem);
				my_tree.rebuild(cur_text[i]);
				dem << "Состояние дерева после перестройки:" << std::endl;
				my_tree.print(0, 0, dem);
			}
			else {
				dem << std::endl << "Идя по пути из закодированного файла встретили символ (Выводим: '" << my_tree.get(num).symbol << "')" << std::endl;
				out << my_tree.get(num).symbol;
				--i;
				my_tree.rebuild(my_tree.get(num).symbol);
				dem << "Состояние дерева после перестройки" << std::endl;
				my_tree.print(0, 0, dem);
			}
		}
		return true;
	}
