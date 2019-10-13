#include "Iterator.h"

TreeIteratorDFS::TreeIteratorDFS(Node* root) {
    if (root != nullptr) {
        path_in_dip.push_back(root);
        go_in_dip(root->left);
        go_in_dip(root->right);
    }
}

void TreeIteratorDFS::go_in_dip(Node* parent) {
    if (parent == nullptr) {
        return;
    } else {
        path_in_dip.push_back(parent);
        go_in_dip(parent->left);
        go_in_dip(parent->right);
    }
}

bool TreeIteratorDFS::has_next() {
    return size <= path_in_dip.size();
}

Node* TreeIteratorDFS::next() {
    return path_in_dip[size++];
}

TreeIteratorBFS::TreeIteratorBFS(Node* root) {
    if (root != nullptr) {
        std::queue<Node*> queue;
        queue.push(root);
        is_visit[root] = true;
        while(!queue.empty()) {
            Node* parent = queue.front();
            queue.pop();
            path_in_breadth.push_back(parent);
            if (parent->left != nullptr && !is_visit[parent->left]) {
                queue.push(parent->left);
                is_visit[parent->left] = true;
            }
            if (parent->right != nullptr && !is_visit[parent->right]) {
                queue.push(parent->right);
                is_visit[parent->right] = true;
            }
        }
    }
}

bool TreeIteratorBFS::has_next() {
    return size <= path_in_breadth.size();
}

Node* TreeIteratorBFS::next() {
    return path_in_breadth[size++];
}
