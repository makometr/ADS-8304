#include <iostream>

typedef char base;
struct s_expr;

struct ptr{
    s_expr* hd;
    s_expr* tl;
};

struct s_expr{
    bool tag;
	union{
  	  base atom;
    	  ptr pair;
	} node;
};

bool compareHierarchicalResult = true;
typedef s_expr* lisp;
void read_lisp (lisp& y);
void read_s_expr(base prev, lisp& y);
void read_seq(lisp& y);
void write_seq(const lisp x);
bool compareS_expr(const lisp lispFirst, const lisp lispSecond);
bool helpCompare(const lisp x, const lisp y);

bool isAtom (const lisp s) {
	if(s == nullptr)
		return false;
	else return
		(s -> tag);
}

bool isnullptr (const lisp s) {
	return s == nullptr;
}

lisp head(const lisp s) {
    if (s != nullptr)
        if (!isAtom(s))
            return s->node.pair.hd;
        else {
            std::cerr << "Error: Head(atom)" << std::endl << std::endl;
            exit(1);
        }
    else {
        std::cerr << "Error: Head(nil)" << std::endl << std::endl;
        exit(1);
    }
}

lisp tail(const lisp s) {
    if (s != nullptr)
        if (!isAtom(s))
            return s->node.pair.tl;
        else{
            std::cerr << "Error: Tail(atom)" << std::endl << std::endl;
            exit(1);
        }
    else{
        std::cerr << "Error: Tail(nil)" << std::endl << std::endl;
        exit(1);
    }
}

void destroy(lisp s) {
    if (s != nullptr) {
        if (!isAtom(s)) {
            destroy(head(s));
            destroy(tail(s));
        }
        delete s;
    }
}

lisp cons(lisp const h, lisp const t) {
    lisp p;
    if (isAtom(t)) {
        std::cerr << "Error: cons(*, atom) \n";
        exit(1);
    }
    else {
        p = new s_expr;
        p->tag = false;
        p->node.pair.hd = h;
        p->node.pair.tl = t;
        return p;
    }
}

lisp make_atom(char const x) {
    lisp s;
    s = new s_expr;
    s->tag = true;
    s->node.atom = x;
    return s;
}

void read_lisp(lisp& y) {	
	base x;
	do{
		std::cin >> x;
	} 
	while(x==' ');
	read_s_expr (x, y);
}

void read_s_expr(base prev, lisp& y) { 
	if(prev != '(') {
		y = make_atom(prev);
	}
	else{ 
		read_seq(y);
	}
}
	
void read_seq(lisp& y) {	
	base x; 
	lisp p1, p2;
	std::cin >> x;
	if(x == ')') {
		y = nullptr;
	}
	else{
		read_s_expr(x, p1);
		read_seq(p2);
		y = cons(p1, p2);
	}
}
	
	
void write_lisp (const lisp x) {
	if(isnullptr(x))
		std::cout << "()";
	else if(isAtom(x))
		std::cout << x->node.atom;
	else{
		std::cout << "(";
		write_seq(x);
		std::cout << ")";
	}
}

void write_seq (const lisp x) {
	if (!isnullptr(x)){
		write_lisp(head (x)); 
		write_seq(tail (x));
	}
}
	
bool compareS_expr(const lisp lispFirst, const lisp lispSecond) {
	if(compareHierarchicalResult == false)
		return false;
	if(isAtom(lispFirst) || isAtom(lispSecond)) {
		if(isAtom(lispSecond) && isAtom(lispSecond)) {
			if(!(lispSecond->node.atom == lispFirst->node.atom)) {
				compareHierarchicalResult = false;
			}
		}
		else{
			compareHierarchicalResult = false;
		}
	}
	else if(!(isAtom(lispFirst)) && !(isAtom(lispSecond))) {
		if(helpCompare(lispFirst, lispSecond) == false)
			compareHierarchicalResult = false;
	}
	else{
		compareHierarchicalResult = false;
	}
	return compareHierarchicalResult;
}

bool helpCompare(const lisp x, const lisp y) {
	if(!isnullptr(x)) {
		if(isnullptr(x) || isnullptr(y))
			return false;
		compareS_expr(head(x), head(y));
		if(isnullptr(x) || isnullptr(y))
			return false;
		helpCompare(tail(x), tail(y));
	}
	return true;
}

int main() {
    	lisp lst1;
    	lisp lst2;
    
	read_lisp(lst1);
  	read_lisp(lst2);
	std::cout << "1-st lisp is: ";
	write_lisp(lst1);
	std::cout << std::endl << "2-nd lisp is: ";
	write_lisp(lst2);
	
	if(compareS_expr(lst1, lst2))
		std::cout << std::endl << "Result: They are equal" << std::endl;
	else
		std::cout << std::endl << "Result: They are not equal" << std::endl;

	destroy(lst1);
	destroy(lst2);
    
    return 0;
}

