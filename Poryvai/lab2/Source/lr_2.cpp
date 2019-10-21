#include<iostream>
#include<cstdlib>
//VAR 3 Считаю сумму длин всех плеч бк
using namespace std;
typedef int base;	// базовый тип элементов (атомов)

struct s_expr;
struct  two_ptr
{
	s_expr* hd;
	s_expr* tl;
};	//end two_ptr;

struct s_expr {
	bool tag; // true: atom, false: pair
	union
	{
		base atom;
		two_ptr pair;
	} node;		//end union node
};			//end s_expr 

typedef s_expr* lisp;

lisp head(const lisp s);
lisp tail(const lisp s);
lisp cons(const lisp h, const lisp t);
lisp make_atom(char* x);
bool isAtom(const lisp s);
bool isNull(const lisp s);
void read_lisp(lisp& y);			// основная
void read_s_expr(char prev, lisp& y);
void read_seq(lisp& y);

// функции вывода:
void write_lisp(const lisp x);		// основная
void write_seq(const lisp x);
lisp head(const lisp s)
{// PreCondition: not null (s)
	if (s != NULL) if (!isAtom(s))	return s->node.pair.hd;
	else { cerr << "Error: Head(atom) \n"; exit(1); }
	else {
		cerr << "Error: Head(nil) \n";
		exit(1);
	}
}

lisp tail(const lisp s)
{// PreCondition: not null (s)
	if (s != NULL) if (!isAtom(s))	return s->node.pair.tl;
	else { cerr << "Error: Tail(atom) \n"; exit(1); }
	else {
		cerr << "Error: Tail(nil) \n";
		exit(1);
	}
}


lisp make_atom(int x)
{
	lisp s;
	s = new s_expr;
	s->tag = true;
	s->node.atom = x;
	return s;
}

bool isNull(const lisp s)
{
	return s == NULL;
}

bool isAtom(const lisp s)
{
	if (s == NULL) return false;
	else return (s->tag);
}


lisp cons(const lisp h, const lisp t)
// PreCondition: not isAtom (t)
{
	lisp p;
	if (isAtom(t)) { cerr << "Error: Tail(nil) \n"; exit(1); }
	else {
		p = new s_expr;
		if (p == NULL) { cerr << "Memory not enough\n"; exit(1); }
		else {
			p->tag = false;
			p->node.pair.hd = h;
			p->node.pair.tl = t;
			return p;
		}
	}
}
void read_lisp(lisp& y)
{
	char x;
	do cin >> x; while (x == ' ');
	read_s_expr(x, y);
} //end read_lisp
//...........................
void read_s_expr(char prev, lisp& y)
{ //prev - ранее прочитанный символ}
	if (prev == ')') { cerr << " ! List.Error 1 " << endl; exit(1); }
	else if (prev != '(') {
		cin.putback(prev);
		int digit;
		cin >> digit;
		//cin.putback(prev);//возвращаю символ в поток ввода
		//digit[i] = '\0';
		//cout << x << endl;
		y = make_atom(digit);
	}
	else read_seq(y);
} //end read_s_expr
void read_seq(lisp& y)
{
	char x;
	lisp p1, p2;

	if (!(cin >> x)) { cerr << " ! List.Error 2 " << endl; exit(1); }
	else {
		while (x == ' ') cin >> x;
		if (x == ')') y = NULL;
		else {
			read_s_expr(x, p1);
			read_seq(p2);
			y = cons(p1, p2);
		}
	}
} //end read_seq
//...........................
// Процедура вывода списка с обрамляющими его скобками - write_lisp,
//  а без обрамляющих скобок - write_seq
void write_lisp(const lisp x)
{//пустой список выводится как () 
	if (isNull(x)) cout << " ()";
	else if (isAtom(x)) cout << ' ' << x->node.atom;
	else { //непустой список} 
		cout << " (";
		write_seq(x);
		cout << " )";
	}
} // end write_lisp
//...........................
void write_seq(const lisp x)
{//выводит последовательность элементов списка без обрамляющих его скобок
	if (!isNull(x)) {
		write_lisp(head(x));
		write_seq(tail(x));
	}
}

void sum(lisp p, int* s)
{//Функция задания лабы

	if (isAtom(p))
		* s += p->node.atom;
	else if (p->node.pair.hd != NULL) {

		sum(p->node.pair.hd, s);

		if (p->node.pair.tl != NULL && !isAtom(p->node.pair.tl->node.pair.hd))
			sum(p->node.pair.tl, s);
	}
	
}

int main() {

	lisp a;
	read_lisp(a);
	write_lisp(a);
	int s = 0;
	sum(a, &s);
	cout << "\n"<<s;
	return 0;
}
