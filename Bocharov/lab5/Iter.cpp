#include <queue>
#include "Iter.h"
#include "Tree.h"

TreeIterDFS::TreeIterDFS(const std::shared_ptr<Node_of_tree>& root) {
    if (root != nullptr) {
        dip_path.push_back(root);
        go_in_dip(root->left_Node);
        go_in_dip(root->right_Node);
    }
}

void TreeIterDFS::go_in_dip(const std::shared_ptr<Node_of_tree>& parent) {
    if (parent == nullptr) {
        return;
    } else {
        dip_path.push_back(parent);
        go_in_dip(parent->left_Node);
        go_in_dip(parent->right_Node);
    }
}

bool TreeIterDFS::has_next() {
    if (size + 1 <= dip_path.size()){
        size++;
        return true;
    }
    return false;
}

std::shared_ptr<Node_of_tree> TreeIterDFS::next() {
    if (dip_path.size() > size)
        return dip_path[size];
    return std::shared_ptr<Node_of_tree>();
}

TreeIterBFS::TreeIterBFS(const std::shared_ptr<Node_of_tree>& root) {
    if (root != nullptr) {
        std::queue<std::shared_ptr<Node_of_tree>> queue;
        queue.push(root);
        visiting[root] = true;
        while(!queue.empty()) {
            std::shared_ptr<Node_of_tree> parent = queue.front();
            queue.pop();
            breadth_path.push_back(parent);
            if (parent->left_Node != nullptr && !visiting[parent->left_Node]) {
                queue.push(parent->left_Node);
                visiting[parent->left_Node] = true;
            }
            if (parent->right_Node != nullptr && !visiting[parent->right_Node]) {
                queue.push(parent->right_Node);
                visiting[parent->right_Node] = true;
            }
        }
    }
}

bool TreeIterBFS::has_next() {
    if (size + 1 <= breadth_path.size()){
        size++;
        return true;
    }
    return false;
}

std::shared_ptr<Node_of_tree> TreeIterBFS::next() {
    if (breadth_path.size() > size)
        return breadth_path[size];
    return std::shared_ptr<Node_of_tree>();
}
