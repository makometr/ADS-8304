//
// Created by Anton on 23.09.2019.
//

#ifndef ADS_LAB2_KRM_H
#define ADS_LAB2_KRM_H

#include <variant>
#include <string>


class krm {
public:

    struct atom;

    typedef struct Element{
        int depth;
        struct krm* parent = nullptr;
        atom* left;
        atom* right;
        ~Element(){
            delete(left);
            delete(right);
        }
    }elem;

    struct atom {
        int len;
        std::variant<int,krm*>value;
        ~atom(){
            if(std::holds_alternative<krm*>(value))
                delete(std::get<krm*>(value));
        }
    };			//end atom



    elem* e;

    krm(int n){
        e = new elem;
        e->depth = n;
        e->left = new atom;
        e->right = new atom;
    }

    ~krm(){
        delete(e);
    }

    bool make_atom(std::istream& input, krm* y, int mode);
    bool read_k (std::istream& input); // основная
    void print_k();
    void find_k(krm& p, std::string s, int& n);
};



#endif //ADS_LAB2_KRM_H
