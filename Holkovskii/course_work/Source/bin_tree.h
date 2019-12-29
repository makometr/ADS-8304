#include <iostream>
#include <fstream>
#include <vector>
#include <variant>
#include <algorithm>


class bin_tree {
	struct kanoha {
		kanoha();
	    kanoha(char b, int par);
		char symbol;
		size_t count;
		int parent;
		int left;
		int right;
	};
	
	std::vector<kanoha> arr;
	void swap(int one, int second);

public:

	bin_tree();
	kanoha get(size_t i);
	size_t size();
	size_t find(const char a);
	void add(const char a);
	void print(int index, int deep, std::ofstream& dem);
	void rebuild(const char a);

};