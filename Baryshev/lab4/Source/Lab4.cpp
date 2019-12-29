#include <iostream>
#include <fstream>
#include <fstream>
#include <cstdlib>

std::ifstream infile("Tests/Tests.txt");
std::ofstream fOut;
typedef char base;

struct node {
	base info;
	node *lt;
	node *rt;
	node() {
		lt = NULL;
		rt = NULL;
	}
};
	
typedef node *binTree;

bool isNull(binTree);
base RootBT(binTree);
binTree Create(void);
binTree Left(binTree);
binTree Right(binTree);
binTree ConsBT(const base &x, binTree &lst,  binTree &rst);
unsigned int sizeBT(binTree b);
void destroy(binTree&);
void outBT(binTree b);
void displayBT(binTree b, int n);
void printKLP(binTree b);
void printLKP(binTree b);
void printLPK(binTree b);

binTree EnterBinTreeFormula(std::string strBinTree, int position){
	binTree left, right;
	int buf = 0; 
	int counter = 0;
	while(	!((strBinTree[position] == '*' || strBinTree[position] == '-' || strBinTree[position] == '+') && counter == 0) ){
		position++;
		if(strBinTree[position] == '(')
			counter++;
		else if((strBinTree[position] == '*' || strBinTree[position] == '+' || strBinTree[position] == '-') && counter > 0){
			counter--;
			position++;
			if(strBinTree[position] == '('){
				counter++;
			}
		}
	}
	buf = position;
	int buf1 = buf;
	counter = 0;
	if(strBinTree[buf1 - 1] == ')'){
		buf1--;
		while(	!((strBinTree[buf1] == '(') && counter == 0) ){
			buf1--;
			if(strBinTree[buf1] == ')'){
				counter++;
			}
			else if((strBinTree[buf1] == '(') && counter > 0){
				counter--;
				buf1--;
				if(strBinTree[buf1] == ')'){
					counter++;
				}
			}
		}
		left = EnterBinTreeFormula(strBinTree, buf1);
	}
	else {
		binTree p1;
		p1 = new node;
		p1->info = strBinTree[buf - 1];
		p1->lt = NULL;
		p1->rt = NULL;
		left = p1;
	}
	if(strBinTree[buf + 1] == '('){
		right = EnterBinTreeFormula(strBinTree, buf + 1);
	}
	else {
		binTree p2;
		p2 = new node;
		p2->info = strBinTree[buf + 1];
		p2->lt = NULL;
		p2->rt = NULL;
		right = p2;
	}
	return ConsBT(strBinTree[position], left, right);
}

binTree ConsBT(const base &x, binTree &lst, binTree &rst) {
	binTree p;
	p = new node;
	if (p != NULL) { 	
		p->info = x;
		p->lt = lst;
		p->rt = rst;
		return p;
	}
	else {
		std::cerr << "Memory not enough\n";
		exit(1);
	}
}

void outBT(binTree b) {	
	if (b!=NULL) {
		fOut << RootBT(b);
		outBT(Left(b));
		outBT(Right(b));
	}
	else
		fOut << '/';
}

void displayBT (binTree b, int n) {
	if (b!=NULL) {
		fOut << ' ' << RootBT(b);
		if(!isNull(Right(b))) {
			displayBT (Right(b),n+1);
		}
		else
			fOut << std::endl;
		if(!isNull(Left(b))) {
			for(int i = 1; i <= n; i++)
				fOut << "  ";
			displayBT (Left(b),n+1);
		}
	}
}

unsigned int sizeBT (binTree b)
{
	if (isNull(b)) return 0;
	else return sizeBT (Left(b))+ sizeBT(Right(b)) + 1;
}

void printKLP (binTree b)
{	if (!isNull(b)) {
		fOut << RootBT(b);
		printKLP (Left(b));
		printKLP (Right(b));
	}
}

void printLKP (binTree b)
{	if (!isNull(b)) {
		printLKP (Left(b));
		fOut << RootBT(b);
		printLKP (Right(b));
	}
}

void printLPK (binTree b)
{	if (!isNull(b)) {
		printLPK (Left(b));
		printLPK (Right(b));
		fOut << RootBT(b);
	}
}
	
binTree Create() {
	return NULL;
}

bool isNull(binTree b) {	
	return (b == NULL);
}

base RootBT (binTree b)
{	if (b == NULL) { std::cerr << "Error: RootBT(null) \n"; exit(1); }
	else return b->info;
}

binTree Left (binTree b)
{	if (b == NULL) { std::cerr << "Error: Left(null) \n"; exit(1); }
	else return b ->lt;
}

binTree Right (binTree b)
{	if (b == NULL) { std::cerr << "Error: Right(null) \n"; exit(1); }
	else return b->rt;
}
		
void destroy (binTree &b) {
	if (b != NULL)	{
		destroy (b->lt);
		destroy (b->rt);
		delete b;
		b = NULL;
	}
}

void replaceElemBinTree(binTree b)
{	if (!isNull(b)) {
		if(RootBT(b) == '+' || RootBT(b) == '-'){
			if(RootBT(Left(b)) == '*' && RootBT(Right(b)) == '*'){
				if(RootBT(b->lt->rt) == RootBT(b->rt->rt)){
					b->lt->info = b->info;
					b->info = '*';
					b->rt->info = RootBT(b->lt->rt);
					b->lt->rt->info = RootBT(b->rt->lt);
					destroy(b->rt->lt); 
					destroy(b->rt->rt);
				}
				else if(RootBT(b->lt->rt) == RootBT(b->rt->lt)){
					b->lt->info = b->info;
					b->info = '*';
					b->rt->info = RootBT(b->rt->lt);
					b->lt->rt->info = RootBT(b->rt->rt);
					destroy(b->rt->lt); 
					destroy(b->rt->rt);
				}
				else if(RootBT(b->lt->lt) == RootBT(b->rt->lt)){
					b->rt->info = b->info;
					b->info = '*';
					b->lt->info = RootBT(b->lt->lt);
					b->rt->lt->info = RootBT(b->lt->rt);
					destroy(b->rt->lt); 
					destroy(b->rt->rt);
				}
				else if(RootBT(b->lt->lt) == RootBT(b->rt->rt)){
					b->rt->info = b->info;
					b->info = '*';
					b->lt->info = RootBT(b->lt->lt);
					b->rt->rt->info = RootBT(b->lt->rt);
					destroy(b->rt->lt); 
					destroy(b->rt->rt);
				}
			}
		}
		replaceElemBinTree (Left(b));
		replaceElemBinTree (Right(b));
	}
}

int main () {
	setlocale(LC_CTYPE, "rus");
	
	binTree binaryTree;
	std::string binTreeString;
	fOut.open("Result.txt");
	
	infile >> binTreeString;
	while(binTreeString != "END"){
		if(binTreeString.size() > 1){
			fOut << "Преобразование дерева для формулы: " << binTreeString << std::endl;
			binaryTree = EnterBinTreeFormula(binTreeString, 0);
			fOut << "Бинарное дерево (повернутое): " << std::endl;
			displayBT (binaryTree, 1);
			fOut << std::endl;
			replaceElemBinTree(binaryTree);
			fOut << "Бинарное дерево (повернутое): " << std::endl;
			displayBT (binaryTree, 1);
			fOut << std::endl << "Постфиксная форма: ";
			printLPK(binaryTree);
			fOut << std::endl << "**********************************" << std::endl;
			infile >> binTreeString;
			destroy(binaryTree);
		}
		else{
			fOut << "Простейший случай условия: " << binTreeString << std::endl;
			infile >> binTreeString;
		}
	}
	
	fOut.close();
	infile.close();
	
	return 0;
}
