#include <iostream>
#include <cstdlib>
#include <sstream>

typedef char base;

	struct s_expr;	
	struct pair{
		s_expr *next = nullptr;
		s_expr *list = nullptr;
	};
	
	struct s_expr {
		bool tag; 
		base atom;
		pair ptrs;		
	};			
			
	typedef s_expr *hlist;

	hlist head (const hlist s);
	hlist tail (const hlist s);
	hlist cons (const hlist h, const hlist t);
	hlist make_atom (const base x);
	bool isAtom (const hlist s);
	bool isNull (const hlist s);
	void destroy (hlist s);

	void read_hlist ( hlist& y, std::stringstream& s, int *);			
	void read_s_expr (base prev, hlist& y, std::stringstream& s, int *); 
	void read_seq ( hlist& y, std::stringstream& s, int *); 

hlist head (const hlist s){
		if (s != nullptr) {
			if (!isAtom(s))	return s->ptrs.list;
			else { std::cerr << "Error: Head(atom) \n"; exit(1); }
		}else { 
			std::cerr << "Error: Head(nil) \n";
			exit(1);
		}
}

bool isAtom (const hlist s){	
	if(s == nullptr) return false;
	else return (s -> tag);
}

bool isNull (const hlist s){
	return s == nullptr;
	
}

hlist tail (const hlist s)
{
		if (s != nullptr) {
			if (!isAtom(s))	return s->ptrs.next;
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
		{
			p->tag = false;
			p->ptrs.list = h;
			p->ptrs.next = t;
			return p;	
		}
	}
}

hlist make_atom (const base x)
	{	hlist s;
		s = new s_expr;
		s -> tag = true;
		s->atom = x;
		return s;
	}


void destroy (hlist s) 
{
	if ( s != nullptr) {
		if (!isAtom(s)) {
			destroy ( head (s));
			destroy ( tail (s));
		}
		delete s;
	
	};


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


			if ( x == ')' ) 
				y = nullptr;
			else {
				read_s_expr ( x, p1, s, c);
				read_seq ( p2, s, c);
				y = cons (p1, p2);
			} 
		}
}
	
int main(int argc, char* argv[]){

	hlist hl = new s_expr;	
	int c = 0;
	std::stringstream ss;
	if (argc == 2){
    		ss << argv[1];
	}else{
		std::string s;
		std::cin >> s;
		ss << s; 
	}

	std::cout << "Иерархический список:" << ss.str() << std::endl;	
	std::cout << "Линейный список атомов:";
	read_hlist(hl, ss, &c);
	std::cout <<"\nКоличество атомов в иерархическом списке:"<< c << std::endl;
	destroy(hl);
		
	return 0;
	
}
	




