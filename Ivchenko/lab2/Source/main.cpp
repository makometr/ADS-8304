#include <iostream>
#include <cstdlib>
#include <sstream>
#include <vector>


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

void read_hlist (hlist& y, std::stringstream& s, int *, std::vector<char> *l);			
void read_s_expr (base prev, hlist& y, std::stringstream& s, int *, std::vector<char> *); 
void read_seq (hlist& y, std::stringstream& s, int *, std::vector<char> *); 

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

hlist tail (const hlist s){
	if (s != nullptr) {
			if (!isAtom(s))	return s->ptrs.next;
			else { std::cerr << "Error: Tail(atom) \n"; exit(1); }
	}else { std::cerr << "Error: Tail(nil) \n";
			exit(1);
	}
}

hlist cons (const hlist h, const hlist t){
	hlist p;
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

hlist make_atom (const base x){
		hlist s;
		s = new s_expr;
		s -> tag = true;
		s->atom = x;
		return s;

}


void destroy (hlist s) {
	if ( s != nullptr) {
		if (!isAtom(s)) {
			destroy (head (s));
			destroy (tail (s));
		}
		delete s;

	}


}

void read_hlist ( hlist& y,  std::stringstream& ss, int *ctr, std::vector<char> *llist){
		base input;
		do ss >> input;
   		while (input == ' ');
		if (input != '(') 	{
			std::cerr << " ! List.Error 1 " << std::endl;
			exit(1);
		} 
		read_s_expr ( input, y, ss, ctr, llist);



}
void read_s_expr (base prev, hlist& y,  std::stringstream& ss, int *ctr, std::vector<char> *llist){ 
		if ( prev == ')' ) {
			std::cerr << " ! List.Error 2 " << std::endl;
			exit(1); 
		} 
		else if ( prev != '(' ) {
			 y = make_atom (prev);
			 (*llist).push_back(prev);
			 (*ctr)++;
		}
		else read_seq (y, ss, ctr, llist);

}
void read_seq ( hlist& y,  std::stringstream& ss, int *ctr,std::vector<char> *llist) {	
		base input; 
		hlist p1, p2;

		if (!(ss >> input)) {
			std::cerr << " ! List.Error 3 " << std::endl;
			 exit(1);
		}
		else{

    			while (input == ' ')
				ss >> input;


			if ( input == ')' ) 
				y = nullptr;
			else {
				read_s_expr ( input, p1, ss, ctr, llist);
				read_seq ( p2, ss, ctr, llist);
				y = cons (p1, p2);
			} 
		}
}

int main(int argc, char* argv[]){


	hlist hl;	
	int ctr = 0;
	std::vector<char> llist;
	std::stringstream ss;
	if (argc == 2){
    		ss << argv[1];
	}else{
		std::string s;
		std::cout << "Введите данные:";
		std::cin >> s;
		ss << s; 
		
	}

	std::cout << "Иерархический список:" << ss.str() << std::endl;	
	read_hlist(hl, ss, &ctr, &llist);
	std::cout << "Линейный список атомов:";
	for(auto el: llist)
		std::cout << el; 
	std::cout <<"\nКоличество атомов в иерархическом списке:"<< ctr << std::endl;
	destroy(hl);

	return 0;

}







