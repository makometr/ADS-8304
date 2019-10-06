#include <iostream>
#include <fstream>
#include <vector>

template <typename Elem>
struct bin_tree {
	bin_tree(const Elem& val = ""): cur_deep(1), deep(1), cur_ind(0) {
		bt.resize(1);
		bt[0] = val;
	}

	void set(const Elem val) {
		bt[cur_ind] = val;
	}

	bin_tree& left() {
		cur_ind = (cur_ind << 1) + 1;
		if(++cur_deep > deep) {
			deep = cur_deep;
			bt.resize((1 << deep) - 1,"");
		}
		return *this;
	}

	bin_tree& right() {
		cur_ind = (cur_ind << 1) + 2;
		if(++cur_deep > deep) {
			deep = cur_deep;
			bt.resize((1 << deep) - 1,"");
		}
		return *this;
	}

	bin_tree& back() {
		if(cur_ind != 0) {
			cur_ind = (cur_ind - 1) >> 1;
		}
		return *this;
	}

	const Elem get() {
		return bt[cur_ind];
	}

	bin_tree& cl_root() {
		cur_ind = 0;
		deep = 1;
		cur_deep = 1;
		bt.resize(1);
		return *this;
	}

	bool check() {
		for(int i = 0; i < (1 << deep) - 1 ; ++i)
			for(int j = 0; j < (1 << deep) - 1; ++j)
				if((i != j) && (bt[i] != "") && (bt[i] == bt[j]))
					return true;
		return false;
	}
private:
	int cur_deep;
	int deep;
	int cur_ind;
	std::vector<Elem> bt;
};

bool mkBinTree(bin_tree<std::string>& abc, std::string& str, size_t& ind) {
	if(str[ind] != '(') {
		std::cout << "Некорректный формат ввода" << std::endl;
		return false;
	}
	std::string a = "";
	while((str[++ind] != '(') && (str[ind] != ')') && (ind != str.size()))
		a += str[ind];
	if((a == "") && (str[ind] == '(')) {
		std::cout << "Некорректный формат ввода" << std::endl;
		return false;
	}
	abc.set(a);
	if(str[ind] == ')') {
		abc.back();
		ind++;
		return true;
	}
	if(mkBinTree(abc.left(), str, ind) == false) {
		return false;
	}
	if(str[ind] == ')') {
		abc.back();
		ind++;
		return true;
	}
	if(mkBinTree(abc.right(), str, ind) == false) {
		return false;
	}
	ind++;
	abc.back();
	return true;
}

int main(int argc, char* argv[]) {
	bin_tree<std::string> abc;
	std::string str;
	size_t pos, ind = 0, k = 0;
	if(argc == 1) {
		std::getline(std::cin, str);
	}
	else {
		std::cout << std::endl << "Для файла: " << argv[1] << std::endl;
		std::ifstream in(argv[1]);
		if (!in.is_open()) {
			std::cout << "Не могу открыть файл((" << std::endl;
			return 0;
		}
		if (in.eof()) {
			std::cout << argv[1] << "Как-то пусто" << std::endl;
			return 0;
		}
		while (std::getline(in, str)) {
			std::cout << std::endl << "Тест " << ++k << std::endl << "Для выражения: " << str << std::endl;
			while((pos = str.find(' ')) != std::string::npos) {
				str.erase(pos,1);
			}
			if(mkBinTree(abc, str, ind)) {
				abc.check() ? std::cout << "Есть одинаковые" << std::endl: std::cout << "Нет одинаковых" << std::endl;
			}
			ind = 0;
			abc.cl_root();
		}
		return 0;
	}
	while((pos = str.find(' ')) != std::string::npos) {
		str.erase(pos,1);
	}
	if(mkBinTree(abc, str, ind)) {
		abc.check() ? std::cout << "Есть одинаковые" << std::endl: std::cout << "Нет одинаковых" << std::endl;
	}
	return 0;
}
