#pragma once

#include <string>
#include <array>
#include <queue>

template <typename T>
class BinTree{
public:

    struct elem{
        T value;
        int left_child_index;
        int right_child_index;
    };

    explicit BinTree(int n){
        MAX_SIZE = n;
        array = new elem*[n];
        for(int i = 0; i < n; i++){
            array[i] = new elem;
        }
    }

    void set_elem_value(T value, int index) {
        array[index]->value = value;
    }

    void set_left_child_index(int current_index, int child_index = -1) {
        array[current_index]->left_child_index = child_index;
    }

    void set_right_child_index(int current_index, int child_index = -1) {
        array[current_index]->right_child_index = child_index;
    }

    elem* get_root() {
        return array[0];
    }

    bool make_bin_tree(int& counter, std::string& str){

        int local_index = size;

        if(str[counter] != '(') {
            std::cout << "Unexpected input format" << std::endl;
            return false;
        }
        std::string current_substring;
        while((str[++counter] != '(') && (str[counter] != ')') && (str[counter] != '#') && (counter != str.size()))
            current_substring += str[counter];
        if((current_substring.empty()) && (str[counter] == '(')) {
            std::cout << "Unexpected input format" << std::endl;
            return false;
        }

        set_elem_value(current_substring, local_index);

        if(str[counter] == ')') {
            set_left_child_index(local_index);
            set_right_child_index(local_index);
            ++counter;
            return true;
        }
        if(str[counter] == '#' && str[counter+1] != '(') {
            std::cout << "Unexpected symbol in the input stream(something after '#' symbol)" << std::endl;
            return false;
        }
        else if(str[counter] == '#') {
            set_left_child_index(local_index);
            ++counter;
        }
        else if(str[counter] == '('){
            if(size + 1 == MAX_SIZE){
                resize_array();
            }
            set_left_child_index(local_index, ++size);
            if(!make_bin_tree(counter, str))
                return false;
        }

        if(str[counter] == ')') {
            set_right_child_index(local_index);
            ++counter;
            return true;
        }
        else if(str[counter] == '('){
            if(size + 1 == MAX_SIZE){
                resize_array();
            }
            set_right_child_index(local_index, ++size);

            if(!make_bin_tree(counter, str))
                return false;
        }
        else {
            std::cout << "Unexpected input format" << std::endl;
            return false;
        }
        ++counter;
        if(str[counter] == ' ') {
            std::cout << "Unexpected input format" << std::endl;
            return false;
        }
        return true;
    }

    int left(BinTree::elem* current_elem){
        return current_elem->left_child_index;
    }


    int right(BinTree::elem* current_elem){
        return current_elem->right_child_index;
    }

    void queue_output(elem* root, std::queue<elem*>& queue){

        std::cout << root->value << ' ';

        if(root->left_child_index != -1)
            queue.push(array[left(root)]);
        if(root->right_child_index != -1)
            queue.push(array[right(root)]);

        if(!queue.empty()) {
            elem* tmp = queue.front();
            queue.pop();
            queue_output(tmp, queue);
        }

    }

    void resize_array(){

        elem** extra_array = new elem*[MAX_SIZE*2];
        for(int i = 0; i <= size; i++){
            extra_array[i] = array[i];
        }

        MAX_SIZE = MAX_SIZE*2;
        for(int i = size + 1; i < MAX_SIZE; i++)
            extra_array[i] = new elem;
        delete[] array;
        array = extra_array;
    }

	 ~BinTree(){
        for(int i = 0; i < MAX_SIZE; i++) {
            delete(array[i]);
        }
        delete[] array;
    }
private:
    int size = 0;
    int MAX_SIZE = 0;
    elem** array;
};