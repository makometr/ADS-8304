#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <cctype>

using namespace std;

struct node
{
	int key;  
	int size; 
	node* left; 
	node* right; 
	node(int k){
		key = k;
		left = right = 0;
		size = 1;
	} 
};

node* find(node*, int);
node* insert(node*, int);
int getsize(node* );
void fixsize(node* );
node* rotateright(node* );
node* rotateleft(node* );
node* insertroot(node*, int);
node* join(node*, node*);
node* remove(node*, int);
void printAndDestroy(node* &b, std::ofstream &fout);

typedef node *BinSearchTree;

node* find(node* p, int k)
{
    if( !p ) return 0;
    if( k == p->key )
        return p; 
    if( k < p->key )
        return find(p->left,k); 
    else
        return find(p->right,k); 
}

int getsize(node* p)
{
	if( !p ) return 0; 
	return p->size; 
}

void fixsize(node* p)
{
	p->size = getsize(p->left)+getsize(p->right)+1; 
}

node* rotateright(node* p)
{
	node* q = p->left; 
	if( !q ) return p; 
	p->left = q->right; 
	q->right = p; 
	q->size = p->size; 
	fixsize(p); 
	return q; 
}

node* rotateleft(node* q)
{
	node* p = q->right;
	if( !p ) return q;
	q->right = p->left;
	p->left = q;
	p->size = q->size;
	fixsize(q);
	return p;
}

node* insertroot(node* p, int k) 
{
	if( !p ) return new node(k); 
	if( k<p->key ) 
	{
		p->left = insertroot(p->left,k); 
		return rotateright(p); 
	}
	else 
	{
		p->right = insertroot(p->right,k);
		return rotateleft(p);
	}
}

node* insert(node* p, int k)
{
	if( !p ) return new node(k); 
	if( rand()%(p->size+1) == 0 ) 
		return insertroot(p,k); 
	if( p->key>k ) 
		p->left = insert(p->left,k); 
	else
		p->right = insert(p->right,k); 
    fixsize(p); 
	return p; 
}

node* join(node* p, node* q)
{
	if( !p ) return q;
	if( !q ) return p;
	if( rand()%(p->size+q->size) < p->size ) 
	{
		p->right = join(p->right,q); 
		fixsize(p); 
		return p; 
	}
	else 
	{
		q->left = join(p,q->left); 
		fixsize(q); 
		return q; 
	}
}

node* remove(node* p, int k)
{
	if( !p ) return p; 
	if( p->key==k ) 
	{
		node* q = join(p->left,p->right); 
		delete p; 
		return q; 
	}
	else if( k<p->key ) 
		p->left = remove(p->left,k); 
	else 
		p->right = remove(p->right,k); 
	return p; 
}

void displayBT(node* b, int n, std::ofstream &fout){
		if (b != nullptr) {
			fout << ' ' << b->key;
			if(b->right != nullptr) {
				displayBT(b->right, n + 1, fout);
			}
			else fout << endl;
			if(b->left != nullptr){
				for (int i = 1; i <= n; i++)
					fout << "  ";
				displayBT(b->left, n + 1, fout);
			}
		}
}

void printAndDestroy(node* &b, std::ofstream & fout)
{
	if (b != nullptr) {
		printAndDestroy(b->left , fout);
		fout << b->key << ' ';
		printAndDestroy(b->right, fout);
		delete b;
		b = nullptr;
	}

}
int check(std::stringstream &ss, std::string s, std::ofstream &fout){ 
	char check;
	while (ss >> check){
			if ((check != ' ') && (!isdigit(check))){
					fout << "Некорректные данные:" << s << endl;
					return 0;
			}
	}
	ss.clear();
	ss << s;
	return 1;
}

void readFromFile(std::ifstream &file){

		int cur;
		std::stringstream ss;
		vector<int> arr;	
		if(!file.is_open()){
  	  		std::cout<<"Неверный путь к файлу\n";
	    		return;
    		}	

		std::ofstream fout;
		fout.open ("Tests/output.txt", std::ios::app);
		if(!fout.is_open()){return;}

		std::string s;
		while (std::getline(file,s)){

				ss << s;
				if(!check(ss, s, fout)) {ss.clear(); continue;}


				while (ss >> cur)
					arr.push_back(cur);




				BinSearchTree MyBinTree = nullptr;
				for (auto i: arr) {
					MyBinTree = insert(MyBinTree, i);
				}	

				fout << "Изображение бинарного дерева поиска из набора элементов:" << s << endl;

				displayBT (MyBinTree,1, fout);

				fout << "\nПеречисление элементов в порядке возрастания:";


				ss.clear();
				arr.clear();
				s.clear();
				printAndDestroy(MyBinTree, fout);
				fout << "\n\n\n";
		}file.close();
		fout.close();


}

int main(int argc, char* argv[]){


	if (argc == 2) {
		std::ifstream file(argv[1]);
		readFromFile(file);
	}


	return 0;
}
