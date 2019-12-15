#include <iostream>
#include <fstream>
#include <vector>
#include <variant>
#include <algorithm>

class bin_tree {
	struct kanoha {
		kanoha(): symbol('\0'), count(0), parent(-1), left(-1), right(-1) {}
		kanoha(char b, int par): symbol(b), count(0), parent(par), left(-1), right(-1) {}
		char symbol;
		size_t count;
		int parent;
		int left;
		int right;
	};

	std::vector<kanoha> arr;

	size_t find(const char a) {
		for(size_t i = 0; i < arr.size(); ++i) {
			if(arr[i].symbol == a) {
				return i;
			}
		}
		return arr.size() - 1;
	}

	void add(const char a) {
		arr[arr.size() - 1].left = arr.size() + 1;
		arr[arr.size() - 1].right = arr.size();
		arr.push_back(kanoha(a, arr.size() - 1));
		arr.push_back(kanoha());
		arr[arr.size() - 1].parent = arr.size() - 3;
	}

	void swap(int one, int second) {
		if(one == second) return;
		std::swap(arr[one].symbol, arr[second].symbol);
		std::swap(arr[one].count, arr[second].count);
		std::swap(arr[one].left, arr[second].left);
		std::swap(arr[one].right, arr[second].right);
		if(arr[one].right != -1)
			arr[arr[one].right].parent = one;
		if(arr[one].left != -1)
			arr[arr[one].left].parent = one;
		if(arr[second].right != -1)
			arr[arr[second].right].parent = second;
		if(arr[second].left != -1)
			arr[arr[second].left].parent = second;
	}

	void rebuild(const char a) {
		size_t num = find(a);
		if(num + 2 == arr.size() && arr[num].count == 0) {
			arr[num].count++;
			--num;
		}
		while(true) {
			arr[num].count++;
			if(num == 0) {
				return;
			}
			int i = 0;
			while(arr[num].count > arr[num - i - 1].count)
				++i;
			if((size_t)arr[num].parent + i == num) {
				num = num - i;
			}
			else {
				swap(num, num - i);
				num = arr[num - i].parent;
			}
		}
	}
public:

	bin_tree() {
		arr.push_back(kanoha());
	}


	void code(std::ifstream& in, std::ofstream& out) {
		std::string cur_text, cur_str;
		while (std::getline(in, cur_str)) {
			cur_text += cur_str;
			cur_text += '\n';
		}
		if(cur_text.size()) {
			cur_text.pop_back();
		}
		int cur_parent, num;

		for(char ch: cur_text) {
			num = find(ch);
			std::string stack;
			while(num != 0) {
				cur_parent = arr[num].parent;
				if(arr[cur_parent].left == num) stack += '0';
				else stack += '1';
				num = cur_parent;
			}
			for(auto i = stack.rbegin(); i != stack.rend(); ++i) {
				out << *i;
			}
			if(find(ch) + 1 == arr.size()) {
				add(ch);
				out << ch;
			}
			//out << " ";
			rebuild(ch);
		}
	}
};

int main(int argc, char* argv[])
{
	bin_tree my_tree;
	if(argc == 3) {
		std::ifstream in(argv[1]);
		std::ofstream out(argv[2]);
		if(!in.is_open() || !out.is_open()) {
			std::cout << "Не удалось открыть файл:(" << std::endl;
			return 0;
		}
		my_tree.code(in , out);
		std::cout << "Дело сделано!" << std::endl;
	}
	else {
		std::cout << "Введите имена файлов, откуда и куда кодировать!" << std::endl;
	}
	return 0;
}
