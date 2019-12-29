#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include<ctime>
#include<string.h>//delay
#include<stdlib.h>

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
//void printKLP(binTree b, std::ofstream& out);

void print_cons_write_file(std::string bin_tree, int i, std::ofstream& out);
bool check(std::istream& inp);

int factorial(int i){

	if(i==0)
		return 1;
	else
		return i*factorial(i - 1);
}

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
void printKLP(binTree b, std::ofstream& out)
{
	

	if (!isNull(b)) {

		out<<"( ";
		out << RootBT(b);
		printKLP(Left(b), out);
		printKLP(Right(b), out);
		out<<")";
		

	}

}





void insert_key(binTree &bt, int key) {

	

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

void printAns( int **digits, int quant_d,int quant_s,char *answer ) {

	int  i ,j;

	std::ofstream out;
        out.open(answer, std::ios::app);

	for(i =0; i < quant_s; i++){

		binTree bt = nullptr;

		for(j = 0; j < quant_d; j++)
			insert_key(bt , digits[i][j]);

		printKLP(bt,out);
		out<<"\n";
		destroy(bt);

	}
	out.close();


}


void gen_tasks_answers(int quant_d, int quant_s,char *answers,char* tasks ){

	int i,j;
	int **digits = new int*[quant_s];

	for(i = 0; i < quant_s; i++)
		digits[i] = new int[quant_d];

	srand(time(0));

	for(j = 0; j < quant_s; j++){

		for(i = 0; i < quant_d ; i++)
			digits[j][i] = rand() % 100;


	}


	

	
	printAns(digits, quant_d,quant_s,answers);

	std::ofstream out2(tasks);

	out2<<"Запишите скобочные представления случайных бинарных деревьев поиска заданных следующими последовательностями\n";
	
	for(j = 0; j < quant_s; j++){

                for(i = 0; i < quant_d ; i++)
                        out2<<digits[j][i]<<" ";

		out2<<"\n";

        }
	out2.close();

	


}




int main(int argc, char *argv[]) {

	setlocale(LC_ALL, "Russian");

	int quant_digits,quant_strings;
	std::cout<<"Введите количество чисел для каждого случайного бд\n";
	std::cin>>quant_digits;
	std::cout<<"Введите количество бд\n";
	std::cin>>quant_strings;

	gen_tasks_answers(quant_digits , quant_strings, argv[1], argv[2]);//1 ответы 2 задание 3 ответ ученика4 результаты

	std::ofstream ans_inp(argv[3]);
	ans_inp.close();

	std::cout<<"Сгенерировано новое задание. Перейдите в файл "<<argv[2]<<" чтобы узнать его\n";
 	std::cout<<"Ответы запишите построчно в "<<argv[3]<<" и введите ok\n";
	std::string arg;
	std::cin>>arg;
	if(arg =="ok"){
	int i;


	std::ofstream res(argv[4]);
	std::ifstream ans_r(argv[1]);
	std::ifstream ans_inp(argv[3]);
	std::string str1;
	std::string str2;
	
	for(i = 0; i < quant_strings;i++){
		
		std::getline(ans_r,str1);
		std::getline(ans_inp,str2);

		if(str1 == str2){
			res<<str2<<" Верно"<<"\n";
		}
		else{
			res<<str2<<" Не верно"<<"\n";
		}
	}

	ans_r.close();
	ans_inp.close();

	}
	else
		std::cout<<"Аргумент введен неверно\n";
		
	return 0;
}


