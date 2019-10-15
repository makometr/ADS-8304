#include <iostream>
#include <fstream>
#include <vector>

template <typename Elem>
class bin_tree {
	int cur_deep;
	int deep;
	int cur_ind;
	Elem* vector;
public:
	bin_tree(const Elem& val = Elem()): cur_deep(1), deep(1), cur_ind(0) {
		vector = new Elem[1];
		vector[0] = val;
	}

	~bin_tree() {
		delete[] vector;
	}

	void set(const Elem val) {
		vector[cur_ind] = val;
	}

	bin_tree& left() {
		cur_ind = (cur_ind << 1) + 1;
		if(++cur_deep > deep) {
			Elem* tmp_vector = new Elem[(1<<cur_deep)-1];
			for(int i = 0; i < (1 << deep) - 1; ++i) {
				tmp_vector[i] = vector[i];
			}
			for(int i = (1 << deep) - 1; i < (1 << cur_deep) - 1; ++i) {
				tmp_vector[i] = Elem();
			}
			delete[] vector;
			deep = cur_deep;
			vector = tmp_vector;
		}
		return *this;
	}

	bin_tree& right() {
		cur_ind = (cur_ind << 1) + 2;
		if(++cur_deep > deep) {
			Elem* tmp_vector = new Elem[(1<<cur_deep)-1];
			for(int i = 0; i < (1 << deep) - 1; ++i) {
				tmp_vector[i] = vector[i];
			}
			for(int i = (1 << deep) - 1; i < (1 << cur_deep) - 1; ++i) {
				tmp_vector[i] = Elem();
			}
			delete[] vector;
			deep = cur_deep;
			vector = tmp_vector;
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
		return vector[cur_ind];
	}

	bin_tree& cl_root() {
		cur_ind = 0;
		deep = 1;
		cur_deep = 1;
		delete[] vector;
		vector = new Elem[1];
		vector[0] = Elem();
		return *this;
	}

	bool check() {
		for(int i = 0; i < (1 << deep) - 1 ; ++i)
			for(int j = 0; j < (1 << deep) - 1; ++j)
				if((i != j) && (vector[i] != Elem()) && (vector[i] == vector[j]))
					return true;
		return false;
	}
};

bool mkBinTree(bin_tree<std::string>& abc, std::string& str, size_t& ind) {
	if(str[ind] != '(') {
		std::cout << "Некорректный формат ввода" << std::endl;
		return false;
	}
	std::string a;
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
	size_t ind_space, ind = 0, count_test = 0;
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
			std::cout << std::endl << "Тест " << ++count_test << std::endl << "Для выражения: " << str << std::endl;
			while((ind_space = str.find(' ')) != std::string::npos) {
				str.erase(ind_space,1);
			}
			if(mkBinTree(abc, str, ind)) {
				abc.check() ? std::cout << "Есть одинаковые" << std::endl: std::cout << "Нет одинаковых" << std::endl;
			}
			ind = 0;
			abc.cl_root();
		}
		return 0;
	}
	while((ind_space = str.find(' ')) != std::string::npos) {
		str.erase(ind_space,1);
	}
	if(mkBinTree(abc, str, ind)) {
		abc.check() ? std::cout << "Есть одинаковые" << std::endl: std::cout << "Нет одинаковых" << std::endl;
	}
	return 0;
}
