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

typedef s_expr* lisp;
void read_lisp (lisp& y);
void read_s_expr(base prev, lisp& y);
void read_seq(lisp& y);
void write_seq(const lisp x);
bool compareS_expr(const lisp lispFirst, const lisp lispSecond, bool &flag);
bool helpCompare(const lisp x, const lisp y, bool &flag);

bool isAtom (const lisp s) {
	if(s == NULL)
		return false;
	else return
		(s -> tag);
}

bool isNull (const lisp s) {
	return s == NULL;
}

lisp head(const lisp s) {
    if (s != NULL)
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
    if (s != NULL)
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
    if (s != NULL) {
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
		y = NULL;
	}
	else{
		read_s_expr(x, p1);
		read_seq(p2);
		y = cons(p1, p2);
	}
}
	
	
void write_lisp (const lisp x) {
	if(isNull(x))
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
	if (!isNull(x)){
		write_lisp(head (x)); 
		write_seq(tail (x));
	}
}
	
bool compareS_expr(const lisp lispFirst, const lisp lispSecond, bool &flag) {
	if(flag == false)
		return false;
	if(isAtom(lispFirst) || isAtom(lispSecond)) {
		if(isAtom(lispSecond) && isAtom(lispSecond)) {
			if(!(lispSecond->node.atom == lispFirst->node.atom)) {
				flag = false;
			}
		}
		else{
			flag = false;
		}
	}
	else if(!(isAtom(lispFirst)) && !(isAtom(lispSecond))) {
		if(helpCompare(lispFirst, lispSecond, flag) == false)
			flag = false;
	}
	else{
		flag = false;
	}
	return flag;
}

bool helpCompare(const lisp x, const lisp y, bool &flag) {
	if(!isNull(x)) {
		if(isNull(x) || isNull(y))
			return false;
		compareS_expr(head(x), head(y), flag);
		if(isNull(x) || isNull(y))
			return false;
		helpCompare(tail(x), tail(y), flag);
	}
	return true;
}

int main() {
    lisp lst1 = new s_expr;
    lisp lst2 = new s_expr;
    bool compareHierarchicalResult = true;
	bool *compareHierarchicalResultPointer = &compareHierarchicalResult;
    
	read_lisp(lst1);
    read_lisp(lst2);
	std::cout << "1-st lisp is: ";
	write_lisp(lst1);
	std::cout << std::endl << "2-nd lisp is: ";
	write_lisp(lst2);
	
	if(compareS_expr(lst1, lst2, *compareHierarchicalResultPointer))
		std::cout << std::endl << "Result: They are equal" << std::endl;
	else
		std::cout << std::endl << "Result: They are not equal" << std::endl;

	destroy(lst1);
    destroy(lst2);
    
    return 0;
}