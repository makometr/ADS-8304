#ifndef avl_hpp
#define avl_hpp

#include <stdio.h>
#include <iostream>

struct AVLnode
{
    int key;
    int balance;
    AVLnode *left;
    AVLnode *right;

    AVLnode(int k) {
        key = k;
        balance = 0;
        left = right = nullptr;
    }
};

class AVLtree {
    public:
        AVLtree() = default;
        AVLtree(const AVLtree &) = delete;
        ~AVLtree() {}
        AVLtree &operator=(const AVLtree &) = delete;
    
        AVLnode *root = nullptr;
        AVLnode *insert(AVLnode *p, int k);
        AVLnode *remove(AVLnode *p, int k)  ;
        
        void bracketNotation(AVLnode* root,std::string& str);
        void printBaracketNotation(std::ofstream &output);
        void deleteTree(AVLnode *p);

    private:
        int height(AVLnode *p);
        void setParentBalance(AVLnode *p);

        AVLnode *rotateLeft(AVLnode *p);
        AVLnode *rotateRight(AVLnode *q);
        AVLnode *balance(AVLnode *p);
        AVLnode *findMin(AVLnode *p);
        AVLnode *removeMin(AVLnode *p);
       
    
    
};

#endif /* avl_hpp */

/* AVL class definition */

void AVLtree::deleteTree(AVLnode *p) {
    if (p->left) {
        deleteTree(p->left);
    }
    if (p->right) {
        deleteTree(p->right);
    }
    delete p;
}

int AVLtree::height(AVLnode *p) {
     if (p == NULL)
           return -1;
       return 1 + std::max(height(p->left), height(p->right));
}

void AVLtree::setParentBalance(AVLnode *p) {
    p->balance = height(p->right) - height(p->left);

}

AVLnode *AVLtree::insert( AVLnode *p, int k)
{
    if (p == NULL){
        return new AVLnode(k);
    }
    if (k == p->key) return p;
    else if (k < p->key)
        p->left = insert(p->left, k);
    else
        p->right = insert(p->right, k);
    return balance(p);
}

AVLnode *AVLtree::remove(AVLnode *p, int k)
{
    if (!p) return 0;
    if (k < p->key)
        p->left = remove(p->left, k);
    else if (k > p->key)
        p->right = remove(p->right, k);
    else
    {
        AVLnode *q = p->left;
        AVLnode *r = p->right;
        delete p;
        if (!r) return q;
        AVLnode *min = findMin(r);
        min->right = removeMin(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);
}

AVLnode *AVLtree::findMin(AVLnode *p)
{
    return p->left ? findMin(p->left) : p;
}

AVLnode *AVLtree::removeMin(AVLnode *p)
{
    if (p->left == 0)
        return p->right;
    p->left = removeMin(p->left);
    return balance(p);
}


AVLnode *AVLtree::balance(AVLnode *p)
{
    setParentBalance(p);
    if (p->balance == 2) {
        if (p->right->balance < 0)
            p->right = rotateRight(p->right);
        return rotateLeft(p);
    }
    if (p->balance == -2) {
        if (p->left->balance > 0)
            p->left = rotateLeft(p->left);
        return rotateRight(p);
    }
    return p;
}

AVLnode *AVLtree::rotateRight(AVLnode *p)
{
    AVLnode *q = p->left;
    p->left = q->right;
    q->right = p;
    setParentBalance(p);
    setParentBalance(q);
    return q;
}


AVLnode *AVLtree::rotateLeft(AVLnode *q)
{
    AVLnode *p = q->right;
    q->right = p->left;
    p->left = q;
    setParentBalance(q);
    setParentBalance(p);
    return p;
}


void AVLtree::bracketNotation(AVLnode *root,std::string& str) {
            if (root == NULL)
                return;
                  
            std::string s = "(";
            s += std::to_string(root->key);
            for(char i : s){
                str.push_back(i);
             }
            
            if (!root->left && !root->right){
                str.push_back(')');
                return;

            }
          
            // for left subtree
            str.push_back('(');
            bracketNotation(root->left, str);
            str.push_back(')');
          
            // only if right child is present to
            // avoid extra parenthesis
            if (root->right) {
                str.push_back('(');
                bracketNotation(root->right, str);
                str.push_back(')');
            }

}


void AVLtree::printBaracketNotation(std::ofstream &output){
     std::string brack;
     int h = height(root);
     bracketNotation(root,brack);
     std::cout << "\nAVL Bracket view: " << brack<< std::endl;
     std::cout << "Height of Tree: " << h << std::endl;
     output << "\nAVL Bracket view: " << brack <<"\n";
     output << "Height of Tree: " << h << "\n";

 }
 
 
