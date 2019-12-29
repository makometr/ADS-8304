#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <string>
#include <sstream>
using namespace std;
struct node // структура для представления узлов дерева
{
    int key;
    unsigned char height;
    node* left;
    node* right;
    explicit node(int k) { key = k; left = right = nullptr; height = 1; }
};

unsigned char height(node* p); // определение высоты дерева
int bfactor(node* p); // баланс фактор
void fixheight(node* p); // подсчет высоты
node* rotateright(node* p); // правый поворот вокруг p
node* rotateleft(node* q); // левый поворот вокруг q
node* insert(node* p, int k); // вставка ключа k в дерево с корнем p
node* findmin(node* p); // поиск узла с минимальным ключом в дереве p
node* removemin(node* p); // удаление узла с минимальным ключом из дерева p
node* remove(node* p, int k); // удаление ключа k из дерева p
node* delete_tree(node* tree);// удаление дерева
void txt_tree(node* tree, string& str); // скобочная запись дерева

#endif // AVL_TREE_H
