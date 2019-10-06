//
// Created by Anton on 04.10.2019.
//

#include "queue.h"
#include <iostream>


    queue::queue(){
    tail = nullptr;
    head = nullptr;
}


void queue::push(int v){

    el* n = new el(v);

    if(tail == nullptr){
        tail = n;
        head = tail;
    }

    else {
        head->next = n;
        head = head->next;
        tail->next = head;
    }

    size++;
}

queue::el queue::pop(){
    if (head == tail){
        el tmp = *tail;

        delete(tail);

        tail = nullptr;
        head = tail;


        size--;

        return tmp;
    }
    else{
        el tmp = *head;
        el* tmp_tail = head;
        head = tail;
        while (head->next != tmp_tail) {
            head = head->next;
        }
        delete(tmp_tail);
        head->next = nullptr;
        size--;
        return tmp;
    }
}

int queue::getSize() {
    return size;
}