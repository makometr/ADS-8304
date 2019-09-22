#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct Node {
    int N;
    int R;
    int L;
    int H;
    int M;
    bool balance;
    bool b_check;
    Node *prev;
    Node *left;
    Node *right;
};


void init(int n, int l, int r, Node *&bin) {
    bin->left = nullptr;
    bin->right = nullptr;
    bin->prev = nullptr;
    bin->N = n;
    bin->L = l;
    bin->R = r;
    bin->M = 0;
    bin->H = 0;
    bin->b_check = false;
    std::cout << n << std::endl;
}

void *back(Node *&bin) {
    if (bin->N == 0) return bin;
    else (back(bin->prev));
}

int add(int n, int l, int r, int m, int h, Node *&bin) {
    Node *tmp = new Node;
    tmp->N = n;
    tmp->R = r;
    tmp->L = l;
    tmp->M = m;
    tmp->H = h;
    tmp->right = nullptr;
    tmp->left = nullptr;
    tmp->balance = true;

    std::cout << "TMP->N = " << tmp->N << std::endl;
    std::cout << "BIN->L = " << bin->L << std::endl;
    std::cout << "BIN->R = " << bin->R << std::endl;

    if (bin->L == tmp->N) {
        tmp->prev = bin;
        std::cout << "left move" << std::endl;
        std::cout << std::endl;
        bin->left = tmp;
        bin = bin->left;
        return 0;
    } else if (bin->R == tmp->N) {
        tmp->prev = bin;
        std::cout << "right move" << std::endl;
        std::cout << std::endl;
        bin->right = tmp;
        bin = bin->right;
        return 0;
    } else {
        bin = bin->prev;
        std::cout << "need to back" << std::endl;
        std::cout << std::endl;
        add(n, l, r, m, h, bin);
        return 0;
    }
}

bool balance(Node *&bin) {
    if (bin->left->left != nullptr && !bin->left->b_check) {
        std::cout << "from: " << bin->N << " to:" << bin->left->N << std::endl;
        bin = bin->left;
        balance(bin);
    } else if (bin->right->right != nullptr && !bin->right->b_check) {
        std::cout << "from: " << bin->N << " to:" << bin->right->N << std::endl;
        bin = bin->right;
        balance(bin);
    } else {
        bin->left->b_check = true;
        bin->right->b_check = true;
        int IL = bin->left->H * bin->left->M;
        std::cout << "NL: " << bin->left->N << " IL = " << IL << " ML = " << bin->left->M << std::endl;
        int IR = bin->right->H * bin->right->M;
        std::cout << "NR: " << bin->right->N << " IR = " << IR << " MR = " << bin->right->M << std::endl;
        bin->M = bin->left->M + bin->right->M;
        std::cout << "M = " << bin->M << std::endl;
        if (IL == IR && bin->right->balance && bin->left->balance) {
            bin->balance = true;
            std::cout << IL << "=" << IR << std::endl;
        } else {
            bin->balance = false;
            std::cout << IL << "!=" << IR << std::endl;
        }
        bin->b_check = true;
        if (bin->N == 0 && bin->left->b_check && bin->right->b_check) return bin->balance;
        bin = bin->prev;
        balance(bin);
    }
}

int fromFile(std::string path) {
    std::string file_name = path, log_file;
    if (path.size() == 1) {
        std::cout << " Enter test-file location: " << std::endl;
        std::cin >> file_name;
    }
    std::ifstream file;
    file.open(file_name);

    if (!file.is_open()) {
        std::cout << "ERROR: File is not open" << std::endl;
        return 0;
    }
    std::cout << " Enter where to save results (location with <name>.txt): " << std::endl;
    std::cin >> log_file;
    std::ofstream log(log_file);
    if (!log.is_open()) {
        std::cout << "ERROR: File is not open" << std::endl;
        return 0;
    }
    std::string str, word;
    Node *bin = new Node;
    int counter = 0;
    while (!file.eof()) {
        getline(file, str);
        std::cout << str << std::endl;
        std::istringstream iss(str);
        std::vector<int> array;
        while (iss >> word) array.push_back(std::stoi(word));
        for (int i : array) std::cout << i;
        std::cout << std::endl;
        counter++;
        if (array[0] == 0) {
            init(array[0], array[1], array[2], bin);
        }
        else if (array.size() == 5) {
            add(array[0], array[1], array[2], array[3], array[4], bin);
        }
        else {
            std::cout << "ERROR: Wrong data!" << std::endl;
            return 0;
        }
        log << str << std::endl;
    }
    if ((counter - 1) % 2 != 0) {
        std::cout << "ERROR: Wrong hierarchical list!" << std::endl;
        return 0;
    }
    bin = (Node *) back(bin);
    if (balance(bin))  log << "BALANCED" << std::endl;
    else  log << "NOT BALANCED" << std::endl;
    log.close();
    return 0;
}

int main(int argc, char *argv[]) {
    std::ifstream input;
    if (argc > 1) {
        std::string path = "Tests/";
        path += argv[1];
        std::cout << path << std::endl;
        fromFile(path);
    } else if (argc == 1) {
        fromFile(" ");
    }
    return 0;
}
