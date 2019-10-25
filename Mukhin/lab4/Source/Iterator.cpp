#include <queue>
#include "Iterator.h"
#include "Tree.h"

TreeIteratorDFS::TreeIteratorDFS(std::shared_ptr<Node> root) {
    if (root != nullptr) {
        path_in_dip.push_back(root);
        go_in_dip(root->left);
        go_in_dip(root->right);
    }
}

void TreeIteratorDFS::go_in_dip(std::shared_ptr<Node> parent) {
    if (parent == nullptr) {
        return;
    } else {
        path_in_dip.push_back(parent);
        go_in_dip(parent->left);
        go_in_dip(parent->right);
    }
}

bool TreeIteratorDFS::has_next() {
    if (size + 1 <= path_in_dip.size()){
        size++;
        return true;
    }
    return false;
}

std::shared_ptr<Node> TreeIteratorDFS::next() {
    if (path_in_dip.size() > size)
        return path_in_dip[size];
    return std::shared_ptr<Node>();
}

TreeIteratorBFS::TreeIteratorBFS(std::shared_ptr<Node> root) {
    if (root != nullptr) {
        std::queue<std::shared_ptr<Node>> queue;
        queue.push(root);
        is_visit[root] = true;
        while(!queue.empty()) {
            std::shared_ptr<Node> parent = queue.front();
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
    if (size + 1 <= path_in_breadth.size()){
        size++;
        return true;
    }
    return false;
}

std::shared_ptr<Node> TreeIteratorBFS::next() {
    if (path_in_breadth.size() > size)
        return path_in_breadth[size];
    return std::shared_ptr<Node>();
}
