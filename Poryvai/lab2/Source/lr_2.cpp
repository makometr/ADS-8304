
#include<iostream>
#include<cstdlib>
#include<string>//getline()
#include<fstream>//ifstream()
//VAR 3 Считаю сумму длин всех плеч бк
//using namespace std;
typedef int base;	// базовый тип элементов (атомов)

struct s_expr;
struct  two_ptr
{
	s_expr* hd;//не могу инициализировать
	s_expr* tl;//не могу инициализировать
};	//end two_ptr;

struct s_expr {
	bool tag; // true: atom, false: pair
	union
	{
		base atom;//не могу инициализировать
		two_ptr pair{ nullptr, nullptr };
	} node;		//end union node
};			//end s_expr 

typedef s_expr* lisp;

lisp head(const lisp s);
lisp tail(const lisp s);
lisp cons(const lisp h, const lisp t);
lisp make_atom(int x);
bool isAtom(const lisp s);
bool isNull(const lisp s);
void read_lisp(lisp& y);			// основная
void read_s_expr(char prev, lisp& y);
void read_seq(lisp& y);
void read_lisp(lisp& y, std::ifstream &data);
void read_s_expr(char prev, lisp& y, std::ifstream &data);
void read_seq(lisp& y, std::ifstream &data);

// функции вывода:
void write_lisp(const lisp x);		// основная
void write_seq(const lisp x);
void write_lisp(const lisp x, std::ofstream& out);
void write_seq(const lisp x, std::ofstream& out);

lisp head(const lisp s)
{// PreCondition: not null (s)
	if (s != nullptr)
		if (!isAtom(s))
			return s->node.pair.hd;
		else {

			std::cerr << "Error: Head(atom) \n"; exit(1); 
		}
	else {

		std::cerr << "Error: Head(nil) \n";
		exit(1);
	}
}

lisp tail(const lisp s)
{// PreCondition: not null (s)
	if (s != nullptr)
		if (!isAtom(s))
			return s->node.pair.tl;
	else {
			std::cerr << "Error: Tail(atom) \n"; exit(1);
	}
	else {
		std::cerr << "Error: Tail(nil) \n";
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
	return s == nullptr;
}

bool isAtom(const lisp s)
{
	if (s == nullptr)
		return false;
	else
		return (s->tag);
}


lisp cons(const lisp h, const lisp t)
// PreCondition: not isAtom (t)
{
	lisp p;
	if (isAtom(t)) { 
		std::cerr << "Error: Tail(nil) \n"; exit(1);
	}
	else {
			p = new s_expr;
			p->tag = false;
			p->node.pair.hd = h;
			p->node.pair.tl = t;
			return p;
		
	}
}
void read_lisp(lisp& y)
{
	char x;
	do 
		std::cin >> x;
	while (x == ' ');
	read_s_expr(x, y);
} //end read_lisp
//...........................
void read_s_expr(char prev, lisp& y)
{ //prev - ранее прочитанный символ}
	if (prev == ')') {

		std::cerr << " ! List.Error 1\n"; exit(1);

	}
	else if (prev != '(') {

		std::cin.putback(prev);
		int digit;
		std::cin >> digit;
		y = make_atom(digit);
	}
	else read_seq(y);
} 

void read_seq(lisp& y)
{
	char x;
	lisp p1, p2;

	if (!(std::cin >> x)) {

		std::cerr << " ! List.Error 2 \n"; exit(1); 
	}
	else {
		while (x == ' ')
			std::cin >> x;
		if (x == ')')
			y = nullptr;
		else {

			read_s_expr(x, p1);
			read_seq(p2);
			y = cons(p1, p2);

		}
	}
} //end read_seq

void read_lisp(lisp& y,std::ifstream &data)
{
	char x;
	do 
		data >> x;
	while (x == ' ');
	//cout << "1";
	read_s_expr(x, y,data);
	
} //end read_lisp
//...........................
void read_s_expr(char prev, lisp& y, std::ifstream &data)
{ //prev - ранее прочитанный символ}
	//cout << "2";
	if (prev == ')') { 

		std::cerr << " ! List.Error 1 \n"; exit(1);
	}
	else if (prev != '(') {
		data.putback(prev);
		int digit;
		data >> digit;
		y = make_atom(digit);

	}
	else read_seq(y , data);
} //end read_s_expr

void read_seq(lisp& y, std::ifstream &data)
{
	//cout << "3";
	char x;
	lisp p1, p2;

	if (!(data >> x)) { 
		std::cerr << " ! List.Error 2 \n"; exit(1);
	}
	else {
		while (x == ' ')
			data >> x;
		if (x == ')')
			y = nullptr;
		else {
			//cout << x << endl;
			read_s_expr(x, p1,data);
			read_seq(p2,data);
			y = cons(p1, p2);
		}
	}
} //end read_seq
//...........................
// Процедура вывода списка с обрамляющими его скобками - write_lisp,
//  а без обрамляющих скобок - write_seq
void write_lisp(const lisp x)
{//пустой список выводится как () 
	if (isNull(x))
		std::cout << " ()";
	else if (isAtom(x))
		std::cout << ' ' << x->node.atom;
	else { //непустой список} 
		std::cout << " (";
		write_seq(x);
		std::cout << " )";
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

void write_lisp(const lisp x,std::ofstream &out)
{//пустой список выводится как () 
	if (isNull(x))
		out << " ()";
	else if (isAtom(x))
		out << ' ' << x->node.atom;
	else { //непустой список} 
		out << " (";
		write_seq(x , out);
		out << " )";
	}
} // end write_lisp
//...........................
void write_seq(const lisp x, std::ofstream &out)
{//выводит последовательность элементов списка без обрамляющих его скобок
	if (!isNull(x)) {
		write_lisp(head(x) , out);
		write_seq(tail(x) , out);
	}
}

void sum(lisp p, int* s) {

	if (isAtom(p))
		* s += p->node.atom;
	else if (p->node.pair.hd != nullptr) {

		sum(p->node.pair.hd, s);

		if (p->node.pair.tl != nullptr && !isAtom(p->node.pair.tl->node.pair.hd))
			sum(p->node.pair.tl, s);
	}
	
}

int main(int argc, char* argv[]) {

	setlocale(LC_ALL, "Russian");
	std::cout << "Ввод из файла или из консоли? (f , c)\nОба пункта?(fc)\n";
	std::string arg;
	std::getline(std::cin , arg);

	if (arg == "f") {
		
		std::ifstream data(argv[1]);
		std::ofstream fout("out.txt");//Через linux не пашет
		
		if (data) {
			
			lisp bin_k;
			read_lisp(bin_k, data);

			while (bin_k->tag == false) {
				int total = 0;

				write_lisp(bin_k, fout);
				write_lisp(bin_k);
				sum(bin_k, &total);
				std::cout << " sum = " << total << "\n";
				fout << " sum = ";
				fout << total;
				fout << "\n";
				read_lisp(bin_k, data);

			}
		}
		else
			std::cout << "Неверное имя файла\n";
		
		data.close();
		fout.close();
	}
	else if (arg == "c") {

		lisp bin_k;
		read_lisp(bin_k);
		
		std::ofstream fout("out.txt");
		while (bin_k->tag == false) {

			int total = 0;

			write_lisp(bin_k, fout);
			write_lisp(bin_k);

			sum(bin_k, &total);

			std::cout << " sum = " << total<<"\n";
			fout << " sum = ";
			fout << total;
			fout << "\n";
			read_lisp(bin_k);
		

		}

		fout.close();
	}
	else if (arg == "fc") {

		lisp bin_k;

		std::ifstream data(argv[1]);
		std::ofstream fout1("out1.txt");
		if (data) {

			lisp bin_k;
			read_lisp(bin_k, data);

			std::cout << "File:\n";
			while (bin_k->tag == false) {
				int total = 0;
				
				write_lisp(bin_k, fout1);
				write_lisp(bin_k);

				sum(bin_k, &total);

				std::cout << " sum = " << total <<"\n";
				fout1 << " sum = ";
				fout1 << total;
				fout1 << "\n";
				read_lisp(bin_k, data);


			}
		}
		else
			std::cout << "Неверное имя файла\n";

		std::cout << "Consol:\n";

		read_lisp(bin_k);

		std::ofstream fout2("out2.txt");

		
		while (bin_k->tag == false) {

			int total = 0;
			
			write_lisp(bin_k, fout2);
			write_lisp(bin_k);

			sum(bin_k, &total);

			std::cout << " sum = " << total << "\n";
			fout2 << " sum = ";
			fout2 << total;
			fout2 << "\n";
			read_lisp(bin_k);


		}
		
		data.close();
		fout1.close();
		fout2.close();
	}
	return 0;
}
