#include "bin_tree.h"

bin_tree::kanoha::kanoha(): symbol('\0'), count(0), parent(-1), left(-1), right(-1) {}
bin_tree::kanoha::kanoha(char b, int par): symbol(b), count(0), parent(par), left(-1), right(-1) {}

void bin_tree::swap(int one, int second) {
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

	bin_tree::bin_tree() {
		arr.push_back(kanoha());
	}

	bin_tree::kanoha bin_tree::get(size_t i) {
		return arr[i];
	}

	size_t bin_tree::size() {
		return arr.size();
	}

	size_t bin_tree::find(const char a) {
		for(size_t i = 0; i < arr.size(); ++i) {
			if(arr[i].symbol == a) {
				return i;
			}
		}
		return arr.size() - 1;
	}

	void bin_tree::add(const char a) {
		arr[arr.size() - 1].left = arr.size() + 1;
		arr[arr.size() - 1].right = arr.size();
		arr.push_back(kanoha(a, arr.size() - 1));
		arr.push_back(kanoha());
		arr[arr.size() - 1].parent = arr.size() - 3;
	}

	void bin_tree::print(int index, int deep, std::ofstream& dem) {
		if(index == -1) return;
		print(arr[index].right, deep + 1, dem);
		for(int i = 0; i < deep; ++i) dem << "\t";
		if(arr[index].symbol == '\n')
			dem << "\\n : " << arr[index].count << std::endl;
		else
			if(arr[index].symbol == '\0')
				dem << arr[index].count << std::endl;
			else
				dem << "'"<< arr[index].symbol << "':" << arr[index].count << std::endl;
		print(arr[index].left, deep + 1, dem);
	}

	void bin_tree::rebuild(const char a) {
		size_t num = find(a);
		if(num + 2 == size() && arr[num].count == 0) {
			arr[num--].count++;
		}
		while(true) {
			arr[num].count++;
			if(num == 0) {
				return;
			}
			int i = 0;
			while(arr[num].count > arr[num - i - 1].count) {
				++i;
			}
			if((size_t)arr[num].parent + i == num) {
				num = num - i;
			}
			else {
				swap(num, num - i);
				num = arr[num - i].parent;
			}
		}
	}
