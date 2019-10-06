#include <iostream>
#include <fstream>
#include <string>
#include <regex.h>
#include <string.h>

typedef char base;
struct s_expr;
struct two_ptr{
    s_expr *hd;
    s_expr *tl;
};
struct s_expr{
    bool tag;
    union{
        base value;
        two_ptr my_pair;
    }node;
};
typedef s_expr *lisp;

using namespace std;


void read_lisp( lisp& my_list, std::string &str);
void read_s_expr(base symb, lisp& my_list, std::string &str);
void read_seq(lisp& my_list, std::string &str);

bool in_lisp(base x, const lisp l);

lisp head(const lisp my_list);
lisp tail(const lisp my_list);
bool isAtom(const lisp my_list);
bool isNull(const lisp my_list);
lisp cons(const lisp h, const lisp t);
lisp make_atom(const base x);
void destroy(lisp my_list);

//ifstream file;

int main(int argc, char *argv[])
{
	lisp mainLisp;
	char symb = ' ';
	string str;
	int flag;
	if((argv[1]!=NULL)&&(argv[2]!=NULL)&&(argv[3]!=NULL)){
		regex_t regex;
		int reti1;
		int reti2;
		int reti3;
		reti1 = regcomp(&regex, ".\\.txt", 0);
		reti1 = regexec(&regex, argv[1], 0, NULL, 0);
		reti2 = regcomp(&regex, ".\\.txt", 0);
		reti2 = regexec(&regex, argv[2], 0, NULL, 0);
		reti3 = regcomp(&regex, ".\\.txt", 0);
		reti3 = regexec(&regex, argv[3], 0, NULL, 0);
		if ((!reti1)&&(!reti2)&&(!reti3)){
			ifstream fin(argv[1], ios::in);
			std::getline(fin, str);
			read_lisp(mainLisp, str);
			str=str.substr(1);
			if(!str.empty()){
				cerr<<"Неправильный ввод списка"<<endl;
				exit(1);
			}
			ifstream file(argv[2], ios::in);
			file>>symb;
			if (symb==' '){
				cerr<<"Неправильный ввод символа"<<endl;
				destroy(mainLisp);
				exit(1);
			}
    		ofstream fout(argv[3], ios::out);
    		fout<< symb;
    		if(in_lisp(symb, mainLisp)){
    			fout<<" был найден в иерархическом списке.";
			}else{
				fout<<" не был найден в иерархическом списке.";
			}
			destroy(mainLisp);
			return 0;
		}else{
			cout<<"Некорректные названия файлов (расширение txt)"<<endl;
			return 0;
		}
	}else{
		cout<<"\nВы не ввели или ввели неправильно аргументы командной строки.\nПервый аргумент командной строки - файл с расширением txt, из которого считывается список.\nВторой аргумент - файл с расширением txt, в котором записан символ.\nТретий аргумент - файл с расширением txt, куда будет записан результат.\nДля продолжения введите 1, иначе 0."<<endl;
		
		cin>>flag;
		if(flag==0) return 0; 
		cout<<"Введите в консоль элементы списка!"<<endl;
		cin>>str;
		read_lisp(mainLisp, str);
		str=str.substr(1);
		if(!str.empty()){
			cerr<<"Неправильный ввод списка"<<endl;
			exit(1);
		}
		cout<<"Введите атом!"<<endl;
		cin>>symb;
	}
    if (mainLisp==NULL) exit(1);

    if(in_lisp(symb, mainLisp)){
   		cout<<"Атом был найден в иерархическом списке."<<endl;
	}else{
		cout<<"Атом не был найден в иерархическом списке."<<endl;
	}
	destroy(mainLisp);
    return 0;
}

bool in_lisp(base x, const lisp l)
{
    if (l != NULL)
    {
        if (isAtom(l))
        {
            if (x == l->node.value) return true;
        }
        else
        {
            if (in_lisp(x, head(l))) return true;
            if (in_lisp(x, tail(l))) return true;
        }
    }
    return false;
}


void read_lisp(lisp &my_list, std::string &str){
    base x = str[0];
    while(x==' '){
    	str = str.substr(1);
    	x = str[0];
    }
    read_s_expr(x,my_list, str);
}

void read_s_expr(base symb, lisp &my_list, std::string &str){
    if((symb == ')') || (symb == '\0')){
    	cerr<<"Неправильный ввод списка"<<endl;
    	exit(1);
    }
    else
        if(symb != '(') my_list = make_atom(symb);
        else read_seq(my_list, str);
}

void read_seq(lisp& my_list, std::string &str){
    str = str.substr(1);
    base x = str[0];
    lisp p1,p2;
    if(x=='\0'){
    	cerr<<"Неправильный ввод списка"<< endl;
    	exit(1);
    }
    else{
        while(x==' '){
		    str = str.substr(1);
			x = str[0];
		}
        if(x==')') my_list = NULL;
        else{
            read_s_expr(x,p1, str);
            read_seq(p2, str);
            my_list = cons(p1, p2);
        }
    }
}

lisp head(const lisp my_list){
    if(my_list != NULL)
        if(!isAtom(my_list)) return my_list->node.my_pair.hd;
        else{cerr<<"Error: Head(atom)\n"; exit(1);}
    else{cerr<<"Error:Head(nil)\n"; exit(1);}
}

lisp tail(const lisp my_list){
    if(my_list != NULL)
        if(!isAtom(my_list)) return my_list->node.my_pair.tl;
        else{cerr<<"Error: Tail(atom)\n"; exit(1);}

    else{cerr<<"Error: Tail(nil)\n"; exit(1);}
}

bool isAtom(const lisp my_list){
    if(my_list==NULL) return false;
    else return(my_list->tag);
}

bool isNull(const lisp my_list){
    return my_list==NULL;
}

lisp cons(const lisp h, const lisp t){
    lisp p;
    if(isAtom(t)){
        cerr<<"Error: cons(*, atom)\n"; exit(1);
    }else{ p = new s_expr;
        if(p==NULL){cerr<< "Memory Error\n"; exit(1);}
            else{
                p->tag = false;
                p->node.my_pair.hd = h;
                p->node.my_pair.tl = t;
                return p;
            }
    }
}

lisp make_atom(const base x){
    lisp my_list;
    my_list = new s_expr;
    my_list->tag = true;
    my_list->node.value = x;
    return my_list;
}

void destroy(lisp my_list){
    if( my_list != NULL){
        if(!isAtom(my_list)){
            destroy(head(my_list));
            destroy(tail(my_list));
        }
    delete my_list;
    };
}
