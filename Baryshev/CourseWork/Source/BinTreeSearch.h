#pragma once

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

node* Find(node*, int);
node* Insert(node*, int);
int GetSize(node* );
void FixSize(node* );
node* RotateRight(node* );
node* RotateLeft(node* );
node* InsertRoot(node*, int);
node* Join(node*, node*);
node* Remove(node*, int);

typedef node *BinSearchTree;

node* Find(node* p, int k)
{
    if( !p ) return 0;
    if( k == p->key )
        return p; 
    if( k < p->key )
        return Find(p->left,k); 
    else
        return Find(p->right,k); 
}

int GetSize(node* p)
{
	if( !p ) return 0; 
	return p->size; 
}

void FixSize(node* p)
{
	p->size = GetSize(p->left)+GetSize(p->right)+1; 
}

int hBT(node* b)
{
if (b == NULL) return 0;
else return std::max(hBT (b->left), hBT(b->right)) + 1;
}

node* RotateRight(node* p)
{
	node* q = p->left; 
	if( !q ) return p; 
	p->left = q->right; 
	q->right = p; 
	q->size = p->size; 
	FixSize(p); 
	return q; 
}

node* RotateLeft(node* q)
{
	node* p = q->right;
	if( !p ) return q;
	q->right = p->left;
	p->left = q;
	p->size = q->size;
	FixSize(q);
	return p;
}

node* InsertRoot(node* p, int k) 
{
	if( !p ) return new node(k); 
	if( k < p->key ) 
	{
		p->left = InsertRoot(p->left, k); 
		return RotateRight(p); 
	}
	else 
	{
		p->right = InsertRoot(p->right, k);
		return RotateLeft(p);
	}
}

node* Insert(node* p, int k)
{
	if( !p ) return new node(k); 
	if( rand()%(p->size+1) == 0 ) 
		return InsertRoot(p,k); 
	if( p->key>k ) 
		p->left = Insert(p->left,k); 
	else
		p->right = Insert(p->right,k); 
    FixSize(p); 
	return p; 
}

node* Join(node* p, node* q)
{
	if( !p ) return q;
	if( !q ) return p;
	if( rand()%(p->size+q->size) < p->size ) 
	{
		p->right = Join(p->right, q); 
		FixSize(p); 
		return p; 
	}
	else 
	{
		q->left = Join(p, q->left); 
		FixSize(q); 
		return q; 
	}
}

node* Remove(node* p, int Key)
{
	if(!p) return p; 
	if(p->key == Key) 
	{
		node* q = Join(p->left, p->right); 
		delete p; 
		return q; 
	}
	else if(Key < p->key) 
		p->left = Remove(p->left, Key); 
	else 
		p->right = Remove(p->right, Key); 
	return p; 
}

void displayBT(node* b, int n, std::ofstream& fout){
		if (b != NULL) {
			fout << ' ' << b->key;
			if(b->right != NULL) {
				displayBT(b->right, n + 1, fout);
			}
			else fout << std::endl;
			if(b->left != NULL){
				for (int i = 1; i <= n; i++)
					fout << "  ";
				displayBT(b->left, n + 1, fout);
			}
		}
}

void display(node* b, int n){
		if (b != NULL) {
			std::cout << ' ' << b->key;
			if(b->right != NULL) {
				display(b->right, n + 1);
			}
			else std::cout << std::endl;
			if(b->left != NULL){
				for (int i = 1; i <= n; i++)
					std::cout << "  ";
				display(b->left, n + 1);
			}
		}
}

void destroy (node* &b)
	{	if (b != NULL)	{
			destroy (b->left);
			destroy (b->right);
			delete b;
			b = NULL;
		}
	}
