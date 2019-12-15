#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <ctime>

struct Node {
    Node() = default;

    int cnt = 0;
    std::string s;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
};

struct char_count{
    char_count(int count, std::string &s){
        cnt = count;
        str = s;
    };

    int cnt;
    std::string str;
};

void read_file(std::vector<std::string>& file_data, std::ifstream& input)
{
    std::string current_file_string;
    while (std::getline(input, current_file_string))
    {
        if (current_file_string.back() == '\r')
            current_file_string.erase(current_file_string.end() - 1);
        file_data.push_back(current_file_string);
    }
}

bool decode(std::string const& code, std::shared_ptr<Node>& head, std::string& result){

    std::string current_checked_code;
    std::shared_ptr<Node> processing_node(head);

    for(char c : code) {

        if(c == '0') {
            if(processing_node->right == nullptr) {
                return false;
            }
            if(processing_node->right->s.length() == 1) {
                result += processing_node->right->s;
                processing_node = head;
            }
            else
                processing_node = processing_node->right;
        }

        else{
            if(processing_node->left == nullptr) {
                return false;
            }
            if(processing_node->left->s.length() == 1) {
                result += processing_node->left->s;
                processing_node = head;
            }
            else
                processing_node = processing_node->left;
        }
    }
    return true;
}


bool comparator (char_count i, char_count j) {
    return (i.cnt > j.cnt);
}

void count_chars(std::string &input_str, std::vector<char_count> &cnt_vector) {
    for(auto &i : input_str){
        bool flag = false;
        for( auto &j : cnt_vector) {
            if(j.str[0] == i) {
                j.cnt += 1;
                flag = true;
                break;
            }
        }

        if(flag)
            continue;

        std::string tmp;
        tmp.push_back(i);
        char_count elem(1, tmp);
        cnt_vector.push_back(elem);
    }
    std::sort(cnt_vector.begin(), cnt_vector.end(), comparator);
}


void HF_tree(std::string &input_str, std::vector<char_count> &cnt_vector, std::shared_ptr<Node> &head){

    //Crete leaf_vector(vector of pointers of type Node);
    std::vector<std::shared_ptr<Node>> leaf_vector;
    for( auto &i : cnt_vector){

        std::shared_ptr<Node> leaf_ptr(new(Node));
        leaf_ptr->cnt = i.cnt;
        leaf_ptr->s = i.str;

        leaf_vector.push_back(leaf_ptr);
    }

    //Create tree
    while(leaf_vector.size() > 1){
        size_t i = leaf_vector.size() - 1;

        //creating of new Node out of two leaves; creating of connection
        std::shared_ptr<Node> leaf_ptr(new(Node));
        leaf_ptr->s = leaf_vector[i-1]->s + leaf_vector[i]->s;
        leaf_ptr->cnt = leaf_vector[i-1]->cnt + leaf_vector[i]->cnt;

        if(leaf_vector[i]->cnt <= leaf_vector[i-1]->cnt) {
            leaf_ptr->right = leaf_vector[i];
            leaf_ptr->left = leaf_vector[i - 1];
        }
        else {
            leaf_ptr->left = leaf_vector[i];
            leaf_ptr->right = leaf_vector[i - 1];
        }

        //insert new Node at the right place in the vector
        for(int j = 0; j < leaf_vector.size(); ++j){
            if(leaf_ptr->cnt >= leaf_vector[j]->cnt) {
                leaf_vector.insert(leaf_vector.begin() + j, leaf_ptr);
                break;
            }
        }

        leaf_vector.pop_back();
        leaf_vector.pop_back();
    }
    head = leaf_vector[0];
}


void make_dict(std::shared_ptr<Node> &elem, std::map<char, std::string> &dict, std::string &current_code){

    if(!elem->left && !elem->right){
        if(current_code.empty()) {
            current_code += '1';
        }
        dict[elem->s[0]] = current_code;
        return;
    }

    std::string left_code = current_code + '1';
    make_dict(elem->left, dict, left_code);

    std::string right_code = current_code + '0';
    make_dict(elem->right, dict, right_code);
}


void encode(std::string input_str, std::map<char, std::string> &dict, std::string &encode_str){
    for(auto &i : input_str){
        encode_str += dict[i];
    }
}


void make_FS_tree(std::shared_ptr<Node> &elem, std::vector<char_count> cnt_vector) {

    //Condition of end of recursion
    if(cnt_vector.size() <= 1) {
        return;
    }

    //Create child Nodes and vectors for them
    std::shared_ptr<Node> right_branch(new Node);
    std::shared_ptr<Node> left_branch(new Node);
    std::vector<char_count> right_cnt_vector;
    std::vector<char_count> left_cnt_vector;

    //Set connection
    elem->right = right_branch;
    elem->left = left_branch;

    //Creating of right branch and vector
    for(size_t i = cnt_vector.size() - 1; i >= 1; --i) {

        right_branch->cnt += cnt_vector[i].cnt;
        right_branch->s.insert(0, cnt_vector[i].str);
        right_cnt_vector.insert(right_cnt_vector.begin(), cnt_vector.back());
        cnt_vector.pop_back();

        if(right_branch->cnt + cnt_vector[i-1].cnt >= elem->cnt / 2) {
            break;
        }
    }

    //Creating of left branch and vector
    left_cnt_vector = cnt_vector;
    left_branch->s = elem->s;
    left_branch->s.erase(left_branch->s.end() - right_branch->s.length(), left_branch->s.end());
    left_branch->cnt = elem->cnt - right_branch->cnt;

    //Recursive call
    make_FS_tree(left_branch, left_cnt_vector);
    make_FS_tree(right_branch, right_cnt_vector);

}


void FS_tree(std::string &input_str, std::vector<char_count> &cnt_vector, std::shared_ptr<Node> &head) {

    int sum = 0;
    std::string all_chars;
    for(auto &i : cnt_vector) {
        sum += i.cnt;
        all_chars += i.str;
    }

    head->cnt = sum;
    head->s = all_chars;

    make_FS_tree(head, cnt_vector);
}


int main(int argc, char* argv[]) {

     if (argc >= 2)
     {
         std::ifstream input(argv[1]);
         if (!input.is_open())
         {
             std::cout << "Incorrect input file\n";
             return 1;
         }

         std::vector<std::string> file_data;
         read_file(file_data, input);

         for (int i = 0; i != file_data.size(); ++i)
         {

             std::string input_str = file_data[i];
             if(input_str.empty()) {
                 std::cout << "Nothing have been written into the string" << std::endl;
                 return 1;
             }

             std::cout << "Test #" << i + 1 <<
              "\nInput message: " << input_str << std::endl;


             //Count number of repetition of every character in the input string
             std::vector<char_count> cnt_vector;

             count_chars(input_str, cnt_vector);

             double start_time =  clock();
             //Haffman algorithm
             //Make tree
             std::shared_ptr<Node> hf_head(new Node);
             HF_tree(input_str, cnt_vector, hf_head);
             //Make dict
             std::map<char, std::string> hf_dict;
             std::string hf_proc_str;
             make_dict(hf_head, hf_dict, hf_proc_str);
             //Encode input string
             std::string hf_encode_str;
             encode(input_str, hf_dict, hf_encode_str);
             //Decode coded string
             std::string hf_decode_res;
             decode(hf_encode_str, hf_head, hf_decode_res);
             //Find Haffman's algorithm run time
             double end_time = clock();
             double hf_search_time = end_time - start_time;


             start_time =  clock();
             //Fano-Shannon algorithm
             //Make tree
             std::shared_ptr<Node> fs_head(new Node);
             FS_tree(input_str, cnt_vector, fs_head);
             //Make dict
             std::map<char, std::string> fs_dict;
             std::string fs_proc_str;
             make_dict(fs_head, fs_dict, fs_proc_str);
             //Encode input string
             std::string fs_encode_str;
             encode(input_str, fs_dict, fs_encode_str);
             //Decode coded string
             std::string fs_decode_res;
             decode(fs_encode_str, fs_head, fs_decode_res);
             //Find Fano-Shannon's algorithm run time
             end_time = clock();
             double fs_search_time = end_time - start_time;



             std::cout << "Codes of characters for Haffman's algorithm" << std::endl;
             for(auto &j : hf_dict) {
                 std::cout << j.first << '=' << j.second << " | ";
             }
             std::cout << std::endl << "Codes of characters for Fano-Shannon's algorithm" << std::endl;
             for(auto &j : fs_dict) {
                 std::cout << j.first << '=' << j.second << " | ";
             }
             std::cout << std::endl;

             std::cout << "Haffman's algorithm run time: " << hf_search_time << "ms" << std::endl;
             std::cout << "Fano-Shannon's algorithm run time: " << fs_search_time << "ms" << std::endl;

             std::cout << "Haffman's string has " <<
                       static_cast<double>(fs_encode_str.length() - hf_encode_str.length()) / fs_encode_str.length() * 100
                       << "%(" << fs_encode_str.length() - hf_encode_str.length()
                       <<" characters) better compression" << std::endl;

             std::cout << "Haffman's algorithm: " << hf_encode_str << std::endl;
             std::cout << "Fano-Shannon's algorithm: " << fs_encode_str << std::endl;

             std::cout << "Result of decoding for two algorithms: " << fs_decode_res <<
                       std::endl << "__________________________________________" << std::endl;

         }
     }
    return 0;
}