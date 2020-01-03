#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <stack>
#include <cmath>

struct Node;
using NodePtr = std::shared_ptr<Node>;


struct Node
{
	Node() = default;

	char name = 0;
	NodePtr left;
	NodePtr right;
};

void readInputData(std::ifstream& in, std::vector<std::string>& data)
{
	std::string tmp;
	while (std::getline(in, tmp))
	{
		if (tmp.back() == '\r')
			tmp.erase(tmp.end() - 1);
		data.push_back(tmp);
	}
}

bool isSameTree(std::string s1, std::string s2)
{
	std::sort(s1.begin(), s1.end());
	std::sort(s2.begin(), s2.end());

	return s1 == s2;
}

bool formTree(std::string const& LNR, std::string const& LRN, NodePtr& head)
{
	if (LRN.empty())
	{
		head = nullptr;
		return true;
	}

	head->name = *(LRN.end() - 1);

	size_t root_ind = LNR.find(head->name);
	if (root_ind == std::string::npos)
		return false;

	std::string newLeftLNR(LNR.begin(), LNR.begin() + root_ind);
	std::string newRightLNR(LNR.begin() + root_ind + 1, LNR.end());

	std::string newLeftLRN(LRN.begin(), LRN.begin() + newLeftLNR.size());
	std::string newRightLRN(LRN.begin() + newLeftLNR.size(), LRN.end() - 1);

	NodePtr left = std::make_shared<Node>();
	bool leftFormResult = formTree(newLeftLNR, newLeftLRN, left);
	if (leftFormResult == false)
		return false;

	NodePtr right = std::make_shared<Node>();
	bool rightFormResult = formTree(newRightLNR, newRightLRN, right);
	if (rightFormResult == false)
		return false;

	head->left = left;
	head->right = right;

	return true;
}

void printNLR(NodePtr& head, std::ofstream& out)
{
	if (!head)
		return;

	out << head->name << " ";
	printNLR(head->left, out);
	printNLR(head->right, out);
}

void printTree(NodePtr& head, size_t h, std::vector<std::string>& image, std::ofstream& out)
{
	std::string line(std::pow(2, h + 1) - 1, ' ');

	std::stack<NodePtr> st;
	st.push(head);
	size_t cur_h = 0;

	while (cur_h != h)
	{
		std::vector<NodePtr> nodes;
		size_t step = std::pow(2, h - cur_h + 1);
		size_t ind = std::pow(2, h - cur_h);

		while (!st.empty())
		{
			NodePtr insertElem = st.top();
			st.pop();
			line[ind] = (insertElem) ? insertElem->name : '#';
			ind += step;

			nodes.push_back(insertElem);
		}
		for (int i = nodes.size() - 1; i >= 0; --i)
		{
			if (nodes[i] == nullptr)
			{
				st.push(nullptr);
				st.push(nullptr);
				continue;
			}
			st.push(nodes[i]->right);
			st.push(nodes[i]->left);
		}
		image.push_back(line);

		std::fill(line.begin(), line.end(), ' ');

		++cur_h;
	}

}

size_t treeHeight(NodePtr& head, size_t h = 0)
{
	if (!head)
		return h;
	++h;

	return std::max(treeHeight(head->left, h), treeHeight(head->right, h));
}


int main(int argc, char** argv)
{
	if (argc > 2)
	{
		std::ifstream in(argv[1]);
		if (!in)
		{
			std::cout << "Uncorrect input file\n";
			return 0;
		}
		std::ofstream out(argv[2]);
		if (!out)
		{
			std::cout << "Uncorrect output file\n";
			return 0;
		}

		std::vector<std::string> inputData;
		readInputData(in, inputData);
		if (inputData.size() % 2 != 0)
		{
			std::cout << "Input data must consist of pairs (expression and variable list), entered data is uncorrect\n";
			return 0;
		}
		size_t ind = 1;
		for (auto it = inputData.begin(); it != inputData.end(); it += 2, ++ind)
		{
			out << "№" << ind << "\n";
			// Left (корень) Right
			auto& LNR = *it;
			// Left Right (корень)
			auto& LRN = *(it + 1);

			LNR.erase(std::remove_if(LNR.begin(), LNR.end(), [](char c) {return c == ' '; }), LNR.end());
			LRN.erase(std::remove_if(LRN.begin(), LRN.end(), [](char c) {return c == ' '; }), LRN.end());

			bool checkIsSameRes = isSameTree(LNR, LRN);
			if (checkIsSameRes == false)
			{
				out << "Not same trees\n";
				continue;
			}

			NodePtr head = std::make_shared<Node>();
			bool formResult = formTree(LNR, LRN, head);
			if (formResult == false)
			{
				out << "Uncorrect data\n";
				continue;
			}

			std::vector<std::string> image;
			printTree(head, treeHeight(head), image, out);
			for (auto line : image)
				out << line << "\n";

			out << "\nNLR: ";
			printNLR(head, out);
			out << "\n\n";
		}
	}
}
