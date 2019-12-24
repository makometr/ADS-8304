#pragma once

#include <fstream>
#include <iostream>
#include <ctime>
#include <vector>

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
void printAndDestroy(node* &b);

typedef node *BinTreeSearch;

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

node* simpleInsert(node* p, int k)
{
	
	if( !p ) return new node(k); 

	if( p->key>k ) 

		p->left = simpleInsert(p->left,k); 

	else

		p->right = simpleInsert(p->right,k); 

	fixsize(p); 
	return p; 
}

node* insertroot(node* p, int k) 
{
	if( !p ) 
		return new node(k); 
		
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

node* randInsert(node* p, int k)	
{
	if( !p ) return new node(k);
	if( rand()%(p->size+1) == 0 )
		
		return insertroot(p,k); 
	
	if( p->key>k ) 
		p->left = randInsert(p->left,k); 
	
	else
		p->right = randInsert(p->right,k); 

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

void display(node* b, int n, std::ofstream &file){

		if (b != NULL) {

			file << ' ' << b->key;
			if(b->right != NULL) {
				display(b->right, n + 1, file);
			}
			else file << std::endl;
			if(b->left != NULL){
				for (int i = 1; i <= n; i++)
					file << "  ";
				display(b->left, n + 1, file);
			}
		}
}

void destroy(node* &b)
{
	if (b != nullptr) {
		destroy(b->left);
		destroy(b->right);
		delete b;
		b = nullptr;
	}

}

void printKLP(std::ofstream &file, BinTreeSearch b)
{
 
        if (b != nullptr) {

                file << "(";
                file << b->key;
                printKLP(file, b->left);
                printKLP(file, b->right);
                file << ")";

        }

}
