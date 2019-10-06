//
// Created by Anton on 04.10.2019.
//

#ifndef UNTITLED4_QUEUE_H
#define UNTITLED4_QUEUE_H

class queue {
public:


    typedef struct Element{
        int value;
        struct Element* next;
        explicit Element(int v = 0){
            value = v;
            next = nullptr;
        }
    }el;

    el* tail;
    el* head;

    queue();

    void push(int v);

    el pop();

    int getSize();

private:
    int size = 0;

};


#endif //UNTITLED4_QUEUE_H
