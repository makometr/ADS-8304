#include <iostream>
#include <cstdlib>
#include <fstream>
#include<string>

typedef char base;
typedef unsigned int unInt;

struct node {
	base info = -1;
	node* lt;
	node* rt;
	// constructor
	node() { lt = nullptr; rt = nullptr; }
};

typedef node* binTree; // "представитель" бинарного дерева

binTree Create(void);
bool isNull(binTree);
base RootBT(binTree); // для непустого бин.дерева
binTree Left(binTree);// для непустого бин.дерева
binTree Right(binTree);// для непустого бин.дерева
binTree ConsBT(const base& x, binTree& lst, binTree& rst);
void destroy(binTree&);

binTree enterBT(std::string str, int& i);
void outBT(binTree b);
void displayBT(binTree b, int n, std::ofstream& out);
unInt sizeBT(binTree b);
void printKLP(binTree b, std::ofstream& out);

void print_cons_write_file(std::string bin_tree, int i, std::ofstream& out);
void print_tree(binTree b, std::ofstream& out);
void print_forest(binTree b, std::ofstream& out);

bool is_bt(std::string bin_tree,int i);

//void is_btree(binTree b, bool &flag){
//	if( b != nullptr)
//		return true;
//	else
//		return false;
//}
binTree Create()
{
	return nullptr;
}
//-------------------------------------
bool isNull(binTree b)
{
	return (b == nullptr);
}
//-------------------------------------
base RootBT(binTree b)			// для непустого бин.дерева
{
	if (b == nullptr) { 

		std::cerr << "Error: RootBT(null) \n"; exit(1); 
	}
	else 	
		return b->info;
}
//-------------------------------------	
binTree Left(binTree b)		// для непустого бин.дерева
{
	if (b == nullptr) { 

		std::cerr << "Error: Left(null) \n"; exit(1);
	}
	else 	
		return b->lt;
}
//-------------------------------------	
binTree Right(binTree b)		// для непустого бин.дерева
{
	if (b == nullptr) { 
		std::cerr << "Error: Right(null) \n"; exit(1); 
	}
	else
		 return b->rt;
}
//-------------------------------------		
binTree ConsBT(const base& x, binTree& lst, binTree& rst)
{
	binTree p;
	p = new node;
	if (p != nullptr) {
		p->info = x;
		p->lt = lst;
		p->rt = rst;
		return p;
	}
	else {
		std::cerr << "Memory not enough\n"; exit(1); 
	}
}
//-------------------------------------			
void destroy(binTree& b)
{
	if (b != nullptr) {

		destroy(b->lt);
		destroy(b->rt);
		delete b;
		b = nullptr;

	}
}
binTree enterBT(std::string str,int &i)
{
 	char ch;//сюда добавить условие для неверного задания бинарного дерева
	binTree p, q;
	ch = str[i];
	i++;
	if(i <= str.length()){

		if (ch == '/') 
			return nullptr;
		else {

			p = enterBT(str,i);
			q = enterBT(str, i );
			return ConsBT(ch, p, q);
		}
	}
	else{
		return nullptr;//если не хватает '/'
	}
		
}
//---------------------------------------
void outBT(binTree b)
{
	if (b != nullptr) {

		std::cout << RootBT(b);
		outBT(Left(b));
		outBT(Right(b));

	}
	else 
		std::cout << '/';
}

//---------------------------------------
void displayBT(binTree b, int n,std::ofstream& out)
{	// n - уровень узла
	if (b != nullptr) {
		std::cout << ' ' << RootBT(b);
		out << ' ' << RootBT(b);

		if (!isNull(Right(b))) { 

			displayBT(Right(b), n + 1, out);
		}
		else {
			std::cout << "\n";
			out << "\n";
		}// вниз
		if (!isNull(Left(b))) {
			for (int i = 1; i <= n; i++) {
				std::cout << "  "; // вправо
				out << "  ";
			}
			displayBT(Left(b), n + 1 , out);
		}
	}
	else {};
}
//---------------------------------------

//---------------------------------------
unInt sizeBT(binTree b)
{
	if (isNull(b)) 
		return 0;
	else
		return sizeBT(Left(b)) + sizeBT(Right(b)) + 1;
}
//---------------------------------------
void printKLP(binTree b, std::ofstream & out)
{
	if (!isNull(b)) {

		std::cout << RootBT(b);
		out << RootBT(b);
		printKLP(Left(b) , out);
		printKLP(Right(b) , out);

	}
}


void print_tree(binTree b, std::ofstream &out) {

	binTree p;

	if (b != nullptr) {
		std::cout << "( ";
		std::cout << b->info;
		out << "( ";
		out << b->info;
		p = b->lt;

		while (p != nullptr) {

			print_tree(p , out);
			p = p->rt;
		}
		
		std::cout << " )";
		out << " )";
	}
}


void print_forest(binTree b, std::ofstream &out) {

	binTree p = b;
	while (p != nullptr) {

		print_tree(p , out);
		std::cout << " ";
		p = p->rt;
	}
}

void print_cons_write_file(std::string bin_tree, int i,std::ofstream& out) {

		binTree b = enterBT(bin_tree, i);

		if(is_bt(bin_tree,i) == true){

			std::cout << "Бинарное дерево (повернутое): " << "\n";
			out<< "Бинарное дерево (повернутое): " << "\n";
			displayBT(b, 1, out);

			std::cout << "Размер (число узлов) дерева = " << sizeBT(b) << "\n";
			out<< "Размер (число узлов) дерева = " << sizeBT(b) << "\n";

			std::cout << "Бинарное дерево в КЛП-порядке: " << "\n";
			out<< "Бинарное дерево в КЛП-порядке: " << "\n";
			printKLP(b, out);
			std::cout << "\n";
			out<< "\n";
			std::cout << "Лес соответствующий данному бинарному дереву\n";
			out<< "Лес соответствующий данному бинарному дереву\n";
			print_forest(b, out);

			destroy(b);
	
			std::cout << "\n";
			std::cout << "\n";
			out << "\n";
			out << "\n";
		}
		else{
			
			std::cout<<"Бинарное дерево задано неверно\n"<<bin_tree<<"\n";
			out<<"Бинарное дерево задано неверно\n"<<bin_tree<<"\n";
		}
}

bool is_bt(std::string bin_tree,int i){
	
	if(bin_tree[0] == '/' || bin_tree == " " || bin_tree == "" || bin_tree.length() != i )
		return false;
	else
		return true;

}

int main(int argc, char *argv[]) {
	 
	setlocale(LC_ALL, "Russian");
	std::cout << "Ввод бинарного дерева в клп представлении (/ = nullptr) из файла или консоли(f,c)?\n";
	std::string arg, bin_tree;
	int i = 0;
	std::cin >> arg;
	std::ofstream out("wrong_out.txt");
	if (arg == "f") {
		std::ifstream infile(argv[1]);
		while (getline(infile, bin_tree)) {
				print_cons_write_file(bin_tree, i, out);
		}
	}
	else if (arg == "c") {
		while (getline(std::cin, bin_tree)) {
				print_cons_write_file(bin_tree, i, out);
			
		}
	}
	else
		std::cout << "Аргумент задан неверно\n";
	return 0;
}
