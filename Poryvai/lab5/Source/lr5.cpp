#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

typedef int base;
typedef unsigned int unInt;

struct node {
	base info;
	int count;
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
bool check(std::istream& inp);

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
	else return b->info;
}
//-------------------------------------	
binTree Left(binTree b)		// для непустого бин.дерева
{
	if (b == nullptr) { 

		std::cerr << "Error: Left(null) \n"; exit(1);
	}
	else return b->lt;
}
//-------------------------------------	
binTree Right(binTree b)		// для непустого бин.дерева
{
	if (b == nullptr) { 
		std::cerr << "Error: Right(null) \n"; exit(1); 
	}
	else return b->rt;
}
//-------------------------------------		
binTree ConsBT(const base& info, binTree& lst, binTree& rst)
{
	binTree p;
	p = new node;
	if (p != nullptr) {
		p->info = info;
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

		std::cout << RootBT(b)<<" ";
		out << RootBT(b);
		printKLP(Left(b), out);
		printKLP(Right(b), out);

	}

}

void print(binTree b, std::ofstream& out) {

	if (!isNull(b)) {


		print(Left(b), out);

		std::cout << RootBT(b) << " ";
		out << RootBT(b);
		out << " ";
		print(Right(b), out);

	}
}



void insert_key(binTree &bt, int key) {
//	std::cout<<"insert key";
	if (bt == nullptr) {

		bt = new node;
		(bt)->info = key;
		bt->lt = nullptr;
		bt->rt = nullptr;
		bt->count = 0;

	}
	else if ((bt)->info > key) {

		insert_key( bt->lt, key);
	
	}
	else if ((bt)->info < key) {
		
		insert_key(bt->rt, key);
	
	}
	else if( bt->info == key )
		bt->count++;
}
void inp_bts( binTree& bt,std::ifstream& inp) {
	int key;
	
	while (inp.peek() != '\n' && !inp.eof()) {
		inp >> key;
		insert_key(bt, key);
	}
	
}

void inp_bts(binTree& bt, std::istream& inp) {
	int key;
	
	while (inp.peek() != '\n' && !inp.eof()) {
		inp >> key;
		insert_key(bt, key);
	}
		
}

bool check(std::string str){


	int i = 0;
	if(str == "" || str ==" ")
		return false;
	while( i < str.length() ){


		if( str[i] != '1' && str[i] !='0' && str[i] !='2' && str[i] !='3' && str[i] !='4' && str[i] !='5' && str[i] !='6' && str[i] !='7' && str[i] !='8' && str[i] !='9'  )
			if(str[i] != ' ')
				return false;

		i++;
	}


	return true;

}




int main(int argc, char *argv[]) {
 
	setlocale(LC_ALL, "Russian");
	std::cout << "Ввод бинарного дерева из файла или консоли(f,c)?\n";
	std::string arg, bin_tree;
	int i = 0;
	char ch = '0';
	getline(std::cin ,  arg);
	std::string str;
	
	std::ofstream out("wrong_out.txt");

	if (arg == "f") {

		std::ifstream inp(argv[1]);


		while (!inp.eof()) {
			getline(inp,str);

			if( check(str) == true){

                        	inp.putback('\n');

                       		for(i = str.length() -1; i >= 0; i--)
                         		inp.putback(str[i]);

				binTree bt = nullptr;
				inp_bts(bt, inp);
				print(bt, out);
				destroy(bt);
				getline(inp , str);
				std::cout << "\n";
				out << "\n";
			}
			else{	
				if(!inp.eof()){

					std::cout<<str<<"\n";
                			std::cout<<"Неверно введено дерево\n\n";
					out<<str<<"\n";
                        		out<<"Неверно введено дерево\n\n";}
                	}

		}



	}
	else if (arg == "c") {
		while (!std::cin.eof()) {
			getline(std::cin , str);

			if(check(str) == true){

				std::cin.putback('\n');
				for(i = str.length() -1; i >= 0; i--)
					std::cin.putback(str[i]);
				
				binTree bt = nullptr;
				inp_bts(bt, std::cin);
				print(bt, out);
				destroy(bt);
				std::cin.get(ch);
				std::cout << "\n";
				out << "\n";
			}
			else{
				if(!std::cin.eof()){
					std::cout<<"Неверно введено дерево\n";
					out << "Неверно введено дерево\n";
				}
			}
		}


	}
	else
		std::cout << "Аргумент задан неверно\n";

	return 0;
}
