#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "qtfiles.h"

constexpr size_t DEFAULT_LEN = 103;//стартовая длина
constexpr size_t COEFF = 31; //стартовый множитель для хэша
constexpr size_t COEFFS_COUNT = 100; //количество степеней множителя, высчитываемых заранее
constexpr size_t PRIMES_COUNT = 24;//количество простых чисел для расширения хэш-таблицы
constexpr size_t PRIMES[] = { 103 , 211, 331 , 449 , 587 , 709 , 853 , 991 , 1117 , 1279 , 1433 , 1567 , 1709 , 	1873 , 2027 , 2179 , 2341 , 2477 , 2671 , 2797 , 2963 , 	3163, 3319, 3469 };

template <class Elem>
class HashTable {
private:
    std::list<Elem>* arr; //массив с информацией
    size_t len; //количество выделенной памяти
    size_t realLen; //количество элементов в массиве
    unsigned long long* coeffs;//массив коэффициентов
    unsigned long long hash(Elem elem);
    std::string getListString(unsigned long long hash);//формирует строку, представляющую все значения в ячейке
    QWidget* tableWidget;//главный виджет
    QGridLayout* table;//главный слой
    QLabel** numberLabels;//порядковые номера
    QLabel** textLabels;
    QLabel* hashTableText;//заголовок "хэш-таблица"
    QLabel* outputText;//заголовок "вывод"
    QTextEdit* outputBox;//окно вывода

    void expandTable();

    void out(QString output);
public:
    HashTable();
    ~HashTable();

    bool insert(Elem elem, bool withoutOutput = false);
    bool remove(Elem elem);
    bool find(Elem elem, unsigned long long myHash);
    void checkCollisions() const;
    size_t getLen() const;

    //void setStepByStepMode(bool state);
    void drawHashTable(QWidget*& tableWidget, Elem elem = "");
    void clearDrawnHashTable(QWidget*& tableWidget);
    void highlight(unsigned long long i);
    void clearHighlights();

};

template <class Elem>
HashTable<Elem>::HashTable() :arr(new std::list<std::string>[DEFAULT_LEN]),
    len(DEFAULT_LEN),
    realLen(0),
    coeffs(new unsigned long long[COEFFS_COUNT]),
    table(nullptr),
    numberLabels(new QLabel*[DEFAULT_LEN]),
    textLabels(new QLabel*[DEFAULT_LEN]),
    outputBox(nullptr)

{ //высчитываем коэффициенты для хэша
    for (int i = 0; i < static_cast<int>(COEFFS_COUNT); i++) {
        coeffs[i] = (i > 0) ? coeffs[i - 1] * COEFF : COEFF;
    }
    for (int i=0; i<DEFAULT_LEN; i++){
        numberLabels[i] = nullptr;
        textLabels[i] = nullptr;
    }
}

template <class Elem>
HashTable<Elem>::~HashTable() {

    delete[] numberLabels;//delete содержимого не нужен, виджет удаляет всех детей сам
    delete[] textLabels;
    delete[] coeffs;
    delete[] arr;
}
template <class Elem>
unsigned long long HashTable<Elem>::hash(Elem elem) {//полиномиальная функция хэширования (s1*a^1 + s2*a^2 + ... + sn*a^n) mod len

    unsigned long long myHash = 0;
    for (int i = 0; i < static_cast<int>(elem.length()); i++) {
        myHash += elem[i] * coeffs[i % COEFFS_COUNT];//если нужно больше коэффициентов, то и так сойдет
    }
    myHash %= len;
    return myHash;

}

template <class Elem>
bool HashTable<Elem>::find(Elem elem, unsigned long long myHash) {
    if (myHash == len)//если хеш еще не посчитан то передается несуществующий
        myHash = hash(elem);
    if (!arr[myHash].empty()) {
        auto current = arr[myHash].begin();
        auto end = arr[myHash].end();
        while (current != end) {
            if (*current == elem)
                return true;
            current++;
        }
        return false;
    }
    else return false;
}

template <class Elem>
bool HashTable<Elem>::insert(Elem elem, bool withoutOutput) {

    if (elem.length()==0){
        if (!withoutOutput)
            out("Введен пустой элемент.");
        return false;
    }
    if (realLen > (0.8 * len))
        expandTable();

    unsigned long long myHash = hash(elem);
    if (find(elem, myHash)) { //а вот тут уже высчитан хэш, передадим его чтобы не пересчитывать
        if (!withoutOutput)
            out(QString::fromStdString("Элемент " + elem + " уже находится в таблице."));
        return false;
    }

    //std::cout << elem << "\n";
    arr[myHash].push_back(elem);
    realLen++;
    if (!withoutOutput)
        out(QString::fromStdString("Элемент " + elem + " записан в ячейку " + std::to_string(myHash) + ". Элементов в таблице: " + std::to_string(realLen)));
    highlight(myHash);
    return true;
}

template <class Elem>
bool HashTable<Elem>::remove(Elem elem) {
    unsigned long long myHash = hash(elem);
    if (!arr[myHash].empty()) {
        auto current = arr[myHash].begin();
        auto end = arr[myHash].end();
        while (current != end) {
            if (*current == elem) {
                arr[myHash].erase(current);
                realLen--;
                out(QString::fromStdString("Элемент " + elem + " удален из ячейки " + std::to_string(myHash) + ". Элементов в таблице: " + std::to_string(realLen)));
                highlight(myHash);
                return true;
            }
            current++;
        }
    }
    else {
        out(QString::fromStdString("Элемент " + elem + " не найден."));
        //std::cout << "Элемент " << elem << " не найден!\n";
        return false;
    }
}

template <class Elem>
void HashTable<Elem>::checkCollisions() const {

    std::cout << "Проверка коллизий...\n";
    for (int i = 0; i < static_cast<int>(len); i++) {
        if (!arr[i].empty()) {
            std::cout << "Занятая ячейка " << i << "\n";
            auto current = arr[i].begin();
            auto end = arr[i].end();
            size_t counter = 0;
            std::string collisions;//содержимое ячейки
            while (current != end) {
                if (!counter) {
                    collisions.clear();
                }
                collisions += *current + "\n";
                counter++;
                current++;
            }
            if (counter > 1) {
                std::cout << "Коллизия!\n" << collisions; //<< "\n";
            }
        }
    }
}

template <class Elem>
void HashTable<Elem>::expandTable() {

    //std::cout << "Расширение таблицы!\n";
    out("Таблица переполнена. Расширение таблицы.");
    clearHighlights();
    size_t oldLen = len;

    for (int i=0; i< len; i++){
        delete numberLabels[i];
        delete textLabels[i];
        numberLabels[i] = nullptr;
        textLabels[i] = nullptr;
    }
    delete[] numberLabels;
    delete[] textLabels;


    for (int i = 0; i < static_cast<int>(PRIMES_COUNT); i++) {
        if ((PRIMES[i] == oldLen) && (i + 1) < static_cast<int>(PRIMES_COUNT)) {
            len = PRIMES[i + 1]; //за новую длину берем следующее простое число из заданных
            break;
        }
        else if ((i + 1) >= static_cast<int>(PRIMES_COUNT))
            len += DEFAULT_LEN; //если кончились, что поделать
    }

    numberLabels = new QLabel*[len];
    textLabels = new QLabel*[len];
    for (int i=0; i<len; i++){
        numberLabels[i] = nullptr;
        textLabels[i] = nullptr;
    }

    realLen = 0; //само пересчитается в insert
    auto oldArr = arr;
    arr = new std::list<std::string>[len];

    for (int i = 0; i < static_cast<int>(oldLen); i++) {
        if (!oldArr[i].empty()) {
            auto current = oldArr[i].begin();
            auto end = oldArr[i].end();
            while (current != end) {
                insert(*current, true);
                current++;
            }
        }
    }

    delete[] oldArr;

    drawHashTable(tableWidget);
    out(QString::fromStdString("Расширение таблицы завершено. Количество ячеек: " + std::to_string(len)));
}

template <class Elem>
void HashTable<Elem>::out(QString output){
    if (outputBox){
        outputBox->setText(outputBox->toPlainText()+output+"\n");
        outputBox->moveCursor(QTextCursor::End);
    }
}

template <class Elem>
void HashTable<Elem>::highlight(unsigned long long i){

    if (numberLabels[i])
        numberLabels[i]->setStyleSheet("font-size: 12px; background: rgb(255,255,153)");
    if (textLabels[i])
        textLabels[i]->setStyleSheet("font-size: 12px; background: rgb(255,255,153)");
}

template <class Elem>
void HashTable<Elem>::clearHighlights(){
    for (int i=0; i<len; i++){
        if (numberLabels[i])
            numberLabels[i]->setStyleSheet("font-size: 12px; background: white");
        if (textLabels[i])
            textLabels[i]->setStyleSheet("font-size: 12px; background: white");
    }
}

template <class Elem>
size_t HashTable<Elem>::getLen() const {
    return len;
}


template <class Elem>
std::string HashTable<Elem>::getListString(unsigned long long hash){

    unsigned long long i = hash;
    if (!arr[i].empty()) {
        std::string str = "";
        auto current = arr[i].begin();
        auto end = arr[i].end();
        while (current != end) {
            str += *current;
            current++;
            if (current != end)
                str += " --> ";
        }
        return str;
    }
    else {
        return "";
    }

}

template <class Elem>
void HashTable<Elem>::drawHashTable( QWidget*& tableWidget, Elem elem){

    bool fullRedraw = false;
    if (!table || (elem==""))
        fullRedraw = true;

    this->tableWidget = tableWidget;
    if (!table){ //инициализация содержимого
        table = new QGridLayout(tableWidget);
        table->setColumnStretch(1, 1);

        hashTableText = new QLabel("Хэш-таблица:", tableWidget);
        hashTableText->setStyleSheet("font-size: 16px");
        table->addWidget(hashTableText, 0, 0, 1, 2, Qt::AlignHCenter | Qt::AlignVCenter);

        outputText = new QLabel("Вывод:", tableWidget);
        outputText->setStyleSheet("font-size: 16px");
        table->addWidget(outputText, 0, 2, 1, 2, Qt::AlignHCenter | Qt::AlignVCenter);

    }
    if (!outputBox){ //инициализация текстбокса
        outputBox = new QTextEdit(tableWidget);
        table->addWidget(outputBox, 1, 2, 10, 2);
        outputBox->setText("Таблица успешно отрисована.\n");
        outputBox->setReadOnly(true);
        QSizePolicy policy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        outputBox->setSizePolicy(policy);
    }

    if (fullRedraw){ //перебираем все ячейки и все рисуем
        for (unsigned i=0; i<len; i++){
            //if (!arr[i].empty()) {
                if (!numberLabels[i]){
                    numberLabels[i] = new QLabel(QString::fromStdString(std::to_string(i)+ ": "), tableWidget);
                    numberLabels[i]->setStyleSheet("font-size: 12px; background: white");
                    table->addWidget(numberLabels[i], i+1, 0, 1, 1);
                }

                if (!textLabels[i]){

                    textLabels[i] = new QLabel(QString::fromStdString(getListString(i)), tableWidget);
                    if (getListString(i)!=""){
                        numberLabels[i]->setStyleSheet("font-size: 12px; background: rgb(255,255,153)");
                        textLabels[i]->setStyleSheet("font-size: 12px; background: rgb(255,255,153)");
                    }
                    else
                        textLabels[i]->setStyleSheet("font-size: 12px; background: white");
                    table->addWidget(textLabels[i], i+1, 1, 1, 1);

                }
                else {
                    textLabels[i]->setText(QString::fromStdString(getListString(i)));
                }
            //}
        }
    }

    if (elem.length() > 0){ //если передан конкретный элемент то перерисовываем только его ячейку
        unsigned long long myHash = hash(elem);
        if (!textLabels[myHash]){

            textLabels[myHash] = new QLabel(QString::fromStdString(getListString(myHash)), tableWidget);
            textLabels[myHash]->setStyleSheet("font-size: 12px");
            table->addWidget(textLabels[myHash], myHash+1, 1, 1, 1);

        }
        else {
            textLabels[myHash]->setText(QString::fromStdString(getListString(myHash)));

        }
    }
    else{

    }
}


template <class Elem>
void HashTable<Elem>::clearDrawnHashTable(QWidget*& tableWidget){
    if (!table)
        return;
    for (int i=0; i< len; i++){
        delete numberLabels[i];
        delete textLabels[i];
        numberLabels[i] = nullptr;
        textLabels[i] = nullptr;
    }
    delete hashTableText;
    delete outputText;
    delete outputBox;
    outputBox = nullptr;
    delete table;
    table = nullptr;

}

