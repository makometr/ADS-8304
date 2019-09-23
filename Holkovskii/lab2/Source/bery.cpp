#include <iostream>
#include <variant>
#include <map>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <map>

struct Node{
	~Node()
	{
		if(std::holds_alternative<Node*>(argv))
			delete std::get<Node*>(argv);
		else
		{
			delete std::get<std::pair<Node*, Node*>>(argv).first;
			delete std::get<std::pair<Node*, Node*>>(argv).second;
		}
	}

	bool evaluate()
	{
		if (std::holds_alternative<std::string>(val))
		{
			if (std::get<std::string>(val) == "AND")
				return std::get<std::pair<Node*, Node*>>(argv).first->evaluate() && std::get<std::pair<Node*, Node*>>(argv).second->evaluate();
			if (std::get<std::string>(val) == "OR")
				return std::get<std::pair<Node*, Node*>>(argv).first->evaluate() || std::get<std::pair<Node*, Node*>>(argv).second->evaluate();
			if (std::get<std::string>(val) == "XOR")
				return (std::get<std::pair<Node*, Node*>>(argv).first->evaluate() || std::get<std::pair<Node*, Node*>>(argv).second->evaluate())
				&& !(std::get<std::pair<Node*, Node*>>(argv).first->evaluate() && std::get<std::pair<Node*, Node*>>(argv).second->evaluate());
			if (std::get<std::string>(val) == "NOT")
				return ! std::get<Node*>(argv)->evaluate();
		}
		return std::get<int>(val);
	}

	std::variant<std::pair<Node*, Node*>, Node*> argv;
	std::variant<int, std::string> val;               //std::variant<bool,std::string> val;
};

void mkNode(Node*&, std::string const&, std::map<std::string,bool> const&);

void mkAtom(std::string const& str,int& ind,Node*& arg, std::map<std::string,bool> const& dict){
	if (str[ind] == '(')
	{
		int new_ind = ind, error = 0;
		std::string new_str = "";
		while (1)                //нахождение соот-ей ')'
		{
			new_str += str[new_ind];
			new_ind++;
			if (str[new_ind] == '(')
				error++;
			if (str[new_ind] == ')')
				error--;
			if (error < 0)
				break;
		}
		new_str += str[new_ind];
		mkNode(arg, new_str, dict);
		ind = new_ind + 1;
	}
	else
	{
		std::string tmp = "";
		while (str[ind] != ' ' && str[ind] != '(' && str[ind] != ')')
			tmp += str[ind++];
		auto tr = dict.find(tmp);
		if(tr == dict.end())
		{
			std::cout<<tmp<<" - not declared"<<std::endl;
			exit(1);
		}
		arg->val = tr->second;
	}
}

void mkNode(Node* & point, std::string const& str, std::map<std::string,bool> const& dict)
{
        int ind = 0;
	Node* arg1 = new Node;
	Node* arg2 = new Node;
	while (str[ind] == '(' || str[ind] == ' ')//перейти к оператору
		ind++;
	std::string name_op = "";
	while(str[ind] != ' ' && str[ind] != '(')
		name_op += str[ind++];
	if (name_op != "AND" && name_op != "OR" && name_op != "NOT" && name_op != "XOR")
	{
		std::cout << "Invalid operator!\n";
		delete arg1;
		delete arg2;
		exit(1);
	}
	point->val = name_op;
	while(str[ind] == ' ')
		ind++;
	mkAtom(str, ind, arg1, dict);
	while (str[ind] == ' ')
		ind++;
	if (str[ind] == ')')
	{
		if (std::get<std::string>(point->val) == "NOT")
		{
			point->argv = arg1;
			delete arg2;
			return;
		}
		else
		{
			std::cout << "Operator does not match expression\n";
			exit(1);
		}
	}
	mkAtom(str, ind, arg2, dict);
	point->argv = std::make_pair(arg1, arg2);//сохранение дочерних узлов в родительском
}

int main(int argc, char* argv[]){
	if(argc == 1)
	{
		std::map<std::string,bool> dict;
		std::string s, key = "";
		int val;
		std::cout << "Введите список значений переменных" << std::endl;
		std::getline(std::cin, s);
		s.erase(s.begin());
		s.erase(s.end()-1);
		int tmp = 0;
		for(size_t i = 0; i < s.size(); ++i)
			if (s[i] == '(')
				tmp++;
		for(int i = 0; i < tmp; ++i)
		{
			int k = 1;
			std::string tmp_s = "";
			while(s[k] != ' ')
				tmp_s += s[k++];
			k++;
			key = tmp_s;
			tmp_s = "";
			while(s[k] != ')')
				tmp_s += s[k++];
			std::istringstream stream(tmp_s);
			stream >> val;
			dict.insert({key, val});
			s.erase(0, ++k);
		}
		std::cout << "Введите выражение" << std::endl;
		std::getline(std::cin, s);
		Node* point = new Node;
		mkNode(point, s, dict);
		std::cout << point->evaluate() << std::endl;
		delete point;
	}
	else
	{
		std::cout << "For filename:" << argv[1] << std::endl;
		std::ifstream in(argv[1]);
		if (!in.is_open()){
			std::cout << "Can't open file" << std::endl;
			return 0;
		}
		if (in.eof()){
			std::cout << argv[1] << "is empty File" << std::endl;
			return 0;
		}
		std::map<std::string,bool> dict;
		std::string s, key="";
                int val;
                std::getline(in, s);
                s.erase(s.begin());
                s.erase(s.end()-1);
                int tmp = 0;
                for(size_t i = 0; i < s.size(); ++i)
                        if (s[i] == '(')
                                tmp++;
                for(int i = 0; i < tmp; ++i)
                {
                        int k = 1;
                        std::string tmp_s = "";
                        while(s[k] != ' ')
                                tmp_s += s[k++];
                        k++;                                                                                                                                                                                                               key=tmp_s;
                        tmp_s = "";
                        while(s[k] != ')')
                                tmp_s += s[k++];
                        std::istringstream stream(tmp_s);
                        stream >> val;
                        dict.insert({key, val});
                        s.erase(0, ++k);
                }
		std::getline(in, s);
		Node* point = new Node;
		std::cout<<"Для значений: "<<std::endl;
		for(auto tr = dict.begin();tr != dict.end(); ++tr)
			std::cout << tr->first << " : " << tr->second << std::endl;
		std::cout << "И для выражения: " << s << std::endl;
		mkNode(point, s, dict);
		std::cout << "Ответ: " << point->evaluate() << std::endl;
		delete point;
	}
	return 0;
}
