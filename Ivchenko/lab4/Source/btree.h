#pragma once

struct Node {
	char root;
	Node* lst;
	Node* rst;
	Node() {
		lst = NULL;
		rst = NULL; 
	}
};

typedef Node* bTree;

bTree Create(void);
bool isNull(bTree);
char RootBT(bTree);
bTree Left(bTree);
bTree Right(bTree);
bTree consBT(const char& x, bTree& lst, bTree& rst);
void destroy(bTree&);

bTree Create()
{
	return nullptr;
}
bool isNull(bTree b)
{
	return (b == nullptr);
}

char RootBT(bTree b)
{
	if (b == nullptr) {

		std::cerr << "Error: RootBT(null) \n"; exit(1);
	}
	else
		return b->root;
}

bTree Left(bTree b)
{
	if (b == nullptr) {

		std::cerr << "Error: Left(null) \n"; exit(1);
	}
	else
		return b->lst;
}

bTree Right(bTree b)
{
	if (b == nullptr) {
		std::cerr << "Error: Right(null) \n"; exit(1);
	}
	else
		return b->rst;
}

bTree consBT(const char& x, bTree& leftSubTree, bTree& rightSubTree)
{
	bTree p;
	p = new Node;
	if (p != nullptr) {
		p->root = x;
		p->lst = leftSubTree;
		p->rst = rightSubTree;
		return p;
	}
	else {
		std::cerr << "Memory not enough\n"; exit(1);
	}
}

void destroy(bTree& b)
{
	if (b != nullptr) {

		destroy(b->lst);
		destroy(b->rst);
		delete b;
		b = nullptr;

	}
}
void displayBT (bTree b, int n)
{	
		if (b!=NULL) {
			std::cout << ' ' << RootBT(b);
			if(!isNull(Right(b))) {displayBT (Right(b),n+1);}
			else std::cout << std::endl; 
			if(!isNull(Left(b))) {
				for (int i=1;i<=n;i++) std::cout << "  ";
				displayBT (Left(b),n+1);}
		}
		else {};
}
