#include <iostream>
#include <variant>
#include <map>
#include <algorithm>
#include <fstream>
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
		else
			return std::get<int>(val);
	}

	std::variant<std::pair<Node*, Node*>, Node*> argv;
	std::variant<int, std::string> val;               //std::variant<bool,std::string> val;
};

typedef struct Node Node;

void func(Node*&, std::string const&, std::map<std::string,bool> const&);

void mkAtom(std::string const& str,int& ind,Node*& arg, std::map<std::string,bool> const& dict){
	if (str[ind] == '(')
	{
		int tmp = ind, error = 0;
		std::string tmp_s = "";
		while (1)                //нахождение соот-ей ')'
		{
			tmp_s += str[tmp];
			tmp++;
			if (str[tmp] == '(')
				error++;
			if (str[tmp] == ')')
				error--;
			if (error < 0)
				break;
		}
		tmp_s += str[tmp];
		func(arg, tmp_s, dict);
		ind = tmp + 1;
	}
	else
	{
		std::string tmp = "";
		while (str[ind] != ' ' && str[ind] != '(' && str[ind] != ')')
			tmp += str[ind++];
		auto tr=dict.find(tmp);
		if(tr==dict.end())
		{
			std::cout<<tmp<<" - not declared"<<std::endl;
			exit(1);
		}
		arg->val = tr->second;
	}
}

void func(Node* & point, std::string const& str, std::map<std::string,bool> const& dict)
{
        int ind = 0;
	Node* arg1 = new Node;
	Node* arg2 = new Node;
	while (str[ind] == '(' || str[ind] == ' ')//перейти к оператору
		ind++;
	std::string oper="";                      //
	while(str[ind] != ' ' && str[ind] != '(') //}считывание оператора
		oper+=str[ind++];                 //
	if (oper != "AND" && oper != "OR" && oper != "NOT" && oper != "XOR")//проверка оператора
	{
		std::cout << "Invalid operator!\n";
		delete arg1;
		delete arg2;
		exit(1);
	}
	point->val = oper;             //запись оператора
	while(str[ind] == ' '){ind++;} //переход к первому аргументу или скобочке
	mkAtom(str, ind, arg1, dict);
	while (str[ind] == ' '){ind++;}//переход к следующему аргументу или скобочке
	if (str[ind] == ')')           //проверка унарности
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
	if(argc==1)
	{
		std::map<std::string,bool> dict;
		char* key=new char[20];
		int val;
		std::cout<<"Введите список значений переменных"<<std::endl;
		scanf("(");
		while(scanf("(%s %d)",key,&val)==2)
			dict.insert({key,val});
		delete[] key;
		std::string s;
		std::getline(std::cin,s);
		std::cout<<"Введите выражение"<<std::endl;
		std::getline(std::cin,s);
		Node* point = new Node;
		func(point, s, dict);
		std::cout << point->evaluate() << std::endl;
		delete point;
	}
	else
	{
		std::cout<<"For filename:"<<argv[1]<<std::endl;
		std::ifstream in(argv[1]);
		if (!in.is_open()){
			std::cout<<"Can't open file"<<std::endl;
			return 0;
		}
		if (in.eof()){
			std::cout<<argv[1]<<"is empty File"<<std::endl;
			return 0;
		}
		FILE* file = fopen(argv[1], "r");
		std::map<std::string,bool> dict;
		char* key=new char[20];
		int val;
		fscanf(file,"(");
		while(fscanf(file,"(%s %d)",key,&val)==2)
			dict.insert({key,val});
		delete[] key;
		fclose(file);
		std::string s;
		std::getline(in,s);
		std::getline(in,s);
		Node* point = new Node;
		std::cout<<"Для значений: "<<std::endl;
		for(auto tr = dict.begin();tr != dict.end(); ++tr)
			std::cout<<tr->first<<" : "<<tr->second<<std::endl;
		std::cout<<"И для выражения: "<<s<<std::endl;
		func(point, s, dict);
		std::cout <<"Ответ: "<< point->evaluate() << std::endl;
		delete point;
	}
	return 0;
}
