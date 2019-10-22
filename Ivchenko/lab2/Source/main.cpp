#include <iostream>
#include <cstdlib>
#include <sstream>

typedef char base;	

	struct s_expr {
		bool tag; 
		union{
			base atom;
			s_expr *next;
			s_expr *list;
		} node;		
	};			
	
	typedef s_expr *hlist;

	void print_s_expr( hlist s );

	hlist head (const hlist s);
	hlist tail (const hlist s);
	hlist cons (const hlist h, const hlist t);
	hlist make_atom (const base x);
	bool isAtom (const hlist s);
	bool isNull (const hlist s);
	void destroy (hlist s);
	
	base getAtom (const hlist s);


	void read_hlist ( hlist& y, std::stringstream& s, int *);			
	void read_s_expr (base prev, hlist& y, std::stringstream& s, int *); 
	void read_seq ( hlist& y, std::stringstream& s, int *); 
	

	void write_hlist (const hlist x, int *a);		
	void write_seq (const hlist x, int *b); 
	

hlist head (const hlist s){
		if (s != NULL) {
			if (!isAtom(s))	return s->node.next;
			else { std::cerr << "Error: Head(atom) \n"; exit(1); }
		}else { 
			std::cerr << "Error: Head(nil) \n";
			exit(1);
		}
}

bool isAtom (const hlist s){	
	if(s == NULL) return false;
	else return (s -> tag);
}

bool isNull (const hlist s){
	return s == NULL;
	
}

hlist tail (const hlist s)
{
		if (s != NULL) {
			if (!isAtom(s))	return s->node.list;
			else { std::cerr << "Error: Tail(atom) \n"; exit(1); }
		}else { std::cerr << "Error: Tail(nil) \n";
			exit(1);
		}
}

hlist cons (const hlist h, const hlist t)

	{hlist p;
	if (isAtom(t)) { 
		std::cerr << "Error: Cons(*, atom)\n"; 
		exit(1);
	}
	else {	
		p = new s_expr; 
		if ( p == NULL)	{
			std::cerr << "Memory not enough\n";
			exit(1);
		} 	
		else {
			p->tag = false;
			p->node.next = h;
			p->node.list = t;
			return p;	
		}
	}
}

hlist make_atom (const base x)
	{	hlist s;
		s = new s_expr;
		s -> tag = true;
		s->node.atom = x;
		return s;
	}


void destroy (hlist s) 
{
	if ( s != NULL) {
		if (!isAtom(s)) {
			destroy ( head (s));
			destroy ( tail (s));
		}
		delete s;
	
	};
	}

base getAtom (const hlist s)
	{
		if (!isAtom(s)) {
			 std::cerr << "Error: getAtom(s) for !isAtom(s) \n";
			 exit(1);
		}
		else return (s->node.atom);
	}


void read_hlist ( hlist& y,  std::stringstream& s, int *c)
	{	base x;
		do s >> x;
   		while (x == ' ');
		if (x != '(') 	{
			std::cerr << " ! List.Error 1 " << std::endl;
			exit(1);
		} 
		read_s_expr ( x, y, s, c);
		
	}
void read_s_expr (base prev, hlist& y,  std::stringstream& s, int *c)
	{ 
		if ( prev == ')' ) {
			std::cerr << " ! List.Error 2 " << std::endl;
			exit(1); 
		} 
		else if ( prev != '(' ) {
			 y = make_atom (prev);
			 std::cout<<prev;
			 (*c)++;
		}
		else read_seq (y, s, c);
	}
void read_seq ( hlist& y,  std::stringstream& s, int *c) {	
		base x; 
		hlist p1, p2;

		if (!(s >> x)) {
			std::cerr << " ! List.Error 3 " << std::endl;
			 exit(1);
		}
		else{

    			while (x == ' ')
				s >> x;


			if ( x == ')' ) y = nullptr;
			else {
				read_s_expr ( x, p1, s, c);
				read_seq ( p2, s, c);
				y = cons (p1, p2);
			} 
		}
}
	
int main(int argc, char* argv[]){
	if (argc == 2){
		std::stringstream str;
    		str << argv[1];
		std::cout << "Иерархический список:" << argv[1] << std::endl;
		int c = 0;	
		s_expr* hl;
		std::cout << "Линейный список атомов:";
		read_hlist(hl, str, &c);
		std::cout << std::endl;
		std::cout <<"Количество атомов в иерархическом списке:"<< c << std::endl;
		destroy(hl);		
		
	}
	return 0;
	
}
	




