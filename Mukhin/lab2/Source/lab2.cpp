#include <fstream>
#include "iostream"
#include <algorithm>
#include <sstream>

struct s_expr;

struct ptr {
    s_expr* hd = nullptr;
    s_expr* tl = nullptr;
};

struct s_expr {
    bool tag;
    char atom;
    ptr pair;
};

typedef s_expr* lisp;
void read_lisp(lisp& y, std::stringstream& s);
void read_s_expr(char prev, lisp& y, std::stringstream& s);
void read_seq(lisp& y, std::stringstream& s);

bool is_atom(lisp const s) {
    if (s == nullptr)
        return false;
    return s->tag;
}

lisp head(const lisp s) {
    if (s != nullptr)
        if (!is_atom(s))
            return s->pair.hd;
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
        if (!is_atom(s))
            return s->pair.tl;
        else {
            std::cerr << "Error: Tail(atom)" << std::endl << std::endl;
            exit(1);
        }
    else {
        std::cerr << "Error: Tail(nil)" << std::endl << std::endl;
        exit(1);
    }
}

void destroy(lisp s) {
    if (s != nullptr) {
        if (!is_atom(s)) {
            destroy(head(s));
            destroy(tail(s));
        }
        delete s;
    }
}

lisp cons(lisp const h, lisp const t) {
    lisp p;
    if (is_atom(t)) {
        std::cerr << "Error: cons(*, atom) \n";
        exit(1);
    }
    else {
        p = new s_expr;
        p->tag = false;
        p->pair.hd = h;
        p->pair.tl = t;
        return p;
    }
}

lisp make_atom(char const x) {
    lisp s;
    s = new s_expr;
    s->tag = true;
    s->atom = x;
    return s;
}

void read_seq(lisp& y, std::stringstream& s) {
    char x;
    lisp p1, p2;
    if (!(s >> x)) {
        std::cerr << " ! List.Error 2 " << std::endl << std::endl;
        exit(1);
    }
    else {
        while (x == ' ')
            s >> x;
        if (x == ')')
            y = nullptr;
        else {
            read_s_expr(x, p1, s);
            read_seq(p2, s);
            y = cons(p1, p2);
        }
    }
}

void read_s_expr(char prev, lisp& y, std::stringstream& s) {
    if (prev == ')') {
        std::cerr << " ! List.Error 1 " << std::endl << std::endl;
        exit(1);
    }
    else
    if (prev != '(' )
        y = make_atom(prev);
    else
        read_seq(y, s);
}

void read_lisp(lisp& y, std::stringstream& s) {
    char x;
    do s >> x;
    while (x == ' ');
    read_s_expr(x, y, s);
    if (s.peek() != EOF) {
        std::cerr << "Incorrect" << std::endl;
        exit(1);
    }
}

int dip(lisp const x) {
    int head = 0;
    int tail = 0;
    if (x != nullptr) {
        if (x->tag) {
            if (x->pair.tl != nullptr) {
                tail = dip(x->pair.tl);
            }
        }
        else {
            head = (x->pair.hd != nullptr) ? dip(x->pair.hd) + 1 : 0;
            tail = (x->pair.tl != nullptr) ? dip(x->pair.tl) : 0;
        }
        return std::max(head, tail);
    }
    return 0;
}


int main(int argc, char* argv[]) {
    if (argc != 2)
        return 1;
    std::stringstream str;
    str << argv[1];
    lisp lst = new s_expr;
    read_lisp(lst, str);
    std::cout << str.str();
    if (argv[1][0] == '(')
        std::cout << std::endl << "dip: " << dip(lst) << std::endl << std::endl;
    else
        std::cout << std::endl << "Неверный синтаксис, список должен начинаться с открывающей скобки!" << std::endl << std::endl;
    destroy(lst);
    return 0;
}
