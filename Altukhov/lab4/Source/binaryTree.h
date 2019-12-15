#define SIZE 100
#include <iostream>
#include <fstream>
#include <string>

enum infoIndex {realArrSize, maxArrSize}; //сколько занято памяти и сколько выделено

template <typename T>
struct Elem{
    T value;
    int left;
    int right;
    Elem():left(-1), right(-1){}
    Elem(T value):value(value), left(-1), right(-1){}
};

template <typename T>

class BinaryTree{


    Elem<T>* arr;
    int curIndex;
    int* infoArr;
    bool isMainTree;

    void resize();

public:
    BinaryTree(): arr(nullptr), curIndex(-1), infoArr(new int[2]), isMainTree(true){
        infoArr[realArrSize] = 0;
        infoArr[maxArrSize] = 0;
    }
    BinaryTree(Elem<T>*& arr, int curIndex, int*& infoArr): arr(arr), curIndex(curIndex), infoArr(infoArr), isMainTree(false){}
    ~BinaryTree();
    bool isEmptyTree() const;
    bool isEmptyElem() const;
    Elem<T> getLeftElem() const;
    Elem<T> getRightElem() const;
    T getRoot() const;
    BinaryTree<T> getLeftTree();
    BinaryTree<T> getRightTree();
    void setLeft(); //инициализация без установки значения
    void setRight();
    void setLeft(T newValue);
    void setRight(T newValue);
    void setRoot(T newValue);
    void printTree();
    bool readTree(std::istringstream& inputStream);
    int calcHeight();
    int pathLength(int level=1);
    void printLeaves(std::ofstream& outputF);
    int countNodesOnLevel(int level);
};

template <typename T>
BinaryTree<T>::~BinaryTree(){
    if (isMainTree && arr){ //чтобы поддерево случайно не удалило все
        delete[] arr;
        delete[] infoArr;
        arr = nullptr;
        infoArr = nullptr;
    }

}

template <typename T>
void BinaryTree<T>::resize(){

    Elem<T>* tempArr = new Elem<T>[infoArr[maxArrSize]+SIZE];
    for (int i=0; i<infoArr[realArrSize]; i++)
        tempArr[i] = arr[i];
    delete[] arr;
    arr = tempArr;
}

template <typename T>
bool BinaryTree<T>::isEmptyTree() const {

    return !infoArr[realArrSize]; //инициализировано ли дерево
}

template <typename T>
bool BinaryTree<T>::isEmptyElem() const {

    return (curIndex == -1); //есть ли что-нибудь по этому индексу
}
template <typename T>
Elem<T> BinaryTree<T>::getLeftElem() const {

    if (!isEmptyElem()){
        return arr[arr[curIndex].left];
    }
    else {
        //пустой элем
        std::cout << "Пустой элемент был возвращен!\n";
        return Elem<T>();
    }
}

template <typename T>
Elem<T> BinaryTree<T>::getRightElem() const {

    if (!isEmptyElem()){
        return arr[arr[curIndex].right];
    }
    else {
        //пустой элем
        std::cout << "Пустой элемент был возвращен!\n";
        return Elem<T>();
    }
}

template <typename T>
T BinaryTree<T>::getRoot() const {

    if (!isEmptyElem()){
        return arr[curIndex].value;
    }
    else {
        //пустой элем
        std::cout << "Пустой элемент был возвращен!\n";
        return 0;
    }
}

template <typename T>
BinaryTree<T> BinaryTree<T>::getLeftTree() {

    if ((!isEmptyElem()) && (arr[curIndex].left != -1)){
        return BinaryTree<T>(arr, arr[curIndex].left, infoArr);
    }
    else {
        std::cout << "Левое поддерево не существует\n";
        return BinaryTree<T>();
    }
}

template <typename T>
BinaryTree<T> BinaryTree<T>::getRightTree() {

    if ((!isEmptyElem()) && (arr[curIndex].right != -1)){
        return BinaryTree<T>(arr, arr[curIndex].right, infoArr);
    }
    else {
        std::cout << "Правое поддерево не существует\n";
        return BinaryTree<T>();
    }
}


template <typename T>
void BinaryTree<T>::setLeft(){

    if (infoArr[realArrSize]==infoArr[maxArrSize]){
        this->resize();
    }
    if (!isEmptyElem()){
        arr[curIndex].left = infoArr[realArrSize];
        infoArr[realArrSize]++;
    }

}

template <typename T>
void BinaryTree<T>::setLeft(T newValue){

    if (infoArr[realArrSize]==infoArr[maxArrSize]){
        this->resize();
    }
    if (!isEmptyElem()){
        arr[curIndex].left = infoArr[realArrSize];
        arr[infoArr[realArrSize]] = Elem<T>(newValue);
        infoArr[realArrSize]++;
    }

}

template <typename T>
void BinaryTree<T>::setRight(){

    if (infoArr[realArrSize]==infoArr[maxArrSize]){
        this->resize();
    }
    if (!isEmptyElem()){
        arr[curIndex].right = infoArr[realArrSize];
        infoArr[realArrSize]++;
    }
}


template <typename T>
void BinaryTree<T>::setRight(T newValue){

    if (infoArr[realArrSize]==infoArr[maxArrSize]){
        this->resize();
    }
    if (!isEmptyElem()){
        arr[curIndex].right = infoArr[realArrSize];
        arr[infoArr[realArrSize]] = Elem<T>(newValue);
        infoArr[realArrSize]++;
    }
}

template <typename T>
void BinaryTree<T>::setRoot(T newValue){
    if (isEmptyTree()){
        arr = new Elem<T>[SIZE];
        infoArr[maxArrSize] = SIZE;
        infoArr[realArrSize] = 1;
        curIndex = 0;
    }
    if (!isEmptyElem()){
        arr[curIndex].value = newValue;
    }
}


void destroySpaces(std::istringstream& inputStream){
    char c ='\0';
    while ((inputStream >> c) && (c==' ')){}
    if (c!=' ')
        inputStream.unget();
}

template <typename T>
bool BinaryTree<T>::readTree(std::istringstream& inputStream){

    destroySpaces(inputStream);
    char c = '\0';
    if ((inputStream >> c) && (c=='(')){ //считывание узла

        destroySpaces(inputStream);
        T inputVal;

        if (inputStream>>inputVal){

            this->setRoot(inputVal);
            destroySpaces(inputStream);

            if ((inputStream >> c) && (c=='(')){ //считывание левого поддерева

                inputStream.unget();
                this->setLeft();

                if (this->getLeftTree().readTree(inputStream)){}
                else return false;

                if ((inputStream >> c) && (c=='(')){ //считывание правого поддерева (если есть)
                    inputStream.unget();
                    this->setRight();
                    if (this->getRightTree().readTree(inputStream)){}
                }
                else
                    inputStream.unget();
            }
            else if (c=='#') { //если нет скобки, то может левое поддерево отсутствует?
                destroySpaces(inputStream);
                if ((inputStream >> c) && (c=='(')){ //видимо да, считываем правое (если есть)
                    inputStream.unget();
                    this->setRight();
                    if (this->getRightTree().readTree(inputStream)){}
                    else return false;
                }
                else {
                    std::cout << "Лишний #\n";
                    return false;
                }
            }
            else {
                inputStream.unget();
            }

        }
        else {
            std::cout << "Нет значения узла\n";
            return false;
        }
    }
    else {
        std::cout << "Нет открывающей скобки\n";
        return false;
    }
    destroySpaces(inputStream);
    if ((inputStream >> c) && (c==')')){}
    else {
        std::cout << "Нет закрывающей скобки\n";
        return false;
    }

    return true;

}

template <typename T>
void BinaryTree<T>::printTree(){

    if (!isEmptyElem()){
        std::cout << this->getRoot() << " ";
        if (this->arr[curIndex].left != -1)
            this->getLeftTree().printTree();
        if (this->arr[curIndex].right != -1)
            this->getRightTree().printTree();
    }
}

template <typename T>
int BinaryTree<T>::calcHeight(){

    if (isEmptyElem()){
        return 0;
    }
    return std::max((this->arr[curIndex].left != -1) ? this->getLeftTree().calcHeight() : 0,  (this->arr[curIndex].right != -1) ? this->getRightTree().calcHeight():0) + 1;
}

template <typename T>
int BinaryTree<T>::pathLength(int level){

    int counter = 0;

    if (isEmptyElem())
        return 0;
    if (this->arr[curIndex].left != -1){
        counter += level;
        counter += this->getLeftTree().pathLength(level+1);
    }
    if (this->arr[curIndex].right != -1){
        counter += level;
        counter += this->getRightTree().pathLength(level+1);
    }
    return counter;
}

template <typename T>
void BinaryTree<T>::printLeaves(std::ofstream& outputF){

    if (isEmptyElem())
        return;
    if ((this->arr[curIndex].left == -1) && (this->arr[curIndex].right == -1)){
        std::cout << this->getRoot() << " ";
		outputF << this->getRoot() << " ";
	}
    else {
        if (this->arr[curIndex].left != -1)
            this->getLeftTree().printLeaves(outputF);
        if (this->arr[curIndex].right != -1)
            this->getRightTree().printLeaves(outputF);
    }
}

template <typename T>
int BinaryTree<T>::countNodesOnLevel(int level){

    level--;
    if (isEmptyElem()){
        return 0;
	}
	//std::cout << "Обработка уровня " << level+1 << ". Значение узла: " << this->getRoot() <<((level==0) ? ". +1 к счетчику.\n" : ".\n");
    if (level == 0){
        return 1;
    }
    return ((this->arr[curIndex].left != -1) ? this->getLeftTree().countNodesOnLevel(level) : 0) + ((this->arr[curIndex].right != -1) ? this->getRightTree().countNodesOnLevel(level) : 0);

}
