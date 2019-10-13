#include "Tree.h"
#include <iostream>

Tree::Tree(int root_data) {
    root = new Node;
    root->data = root_data;
}

TreeIterator* Tree::make_iterator_DFS() {
    return new TreeIteratorDFS(root);
}

TreeIterator* Tree::make_iterator_BFS() {
    return new TreeIteratorBFS(root);
}

void Tree::insert(int element) {
    if (root == nullptr) {
        root = new Node;
        root->data = element;
    } else {
        if (root->data > element) {
            insert(root->left, element);
        }

        if (root->data < element) {
            insert(root->right, element);
        }

        if (root->data == element) {
            root->data = element;
        }
    }
}

void Tree::insert(Node*& parent, int element) {
    if (parent == nullptr) {
        parent = new Node;
        parent->data = element;
    } else {
        if (parent->data > element) {
            insert(parent->left, element);
        }

        if (parent->data < element) {
            insert(parent->right, element);
        }

        if (parent->data == element) {
            parent->data = element;
        }
    }
}

void Tree::print_tree() {
    std::map<Node*, int> nodes_and_levels = get_nodes_and_levels();
    TreeIterator* bfs = this->make_iterator_BFS();
    int level_of_dip;

    for (Node* el = bfs->next(); bfs->has_next(); el = bfs->next()) {
        level_of_dip = nodes_and_levels[el];
        std::cout << std::string(level_of_dip * 5, ' ') << el->data << std::endl;
    }
}

int Tree::dip() {
    if (root == nullptr) {
        return 0;
    } else {
        std::map<Node*, int> nodes_and_levels = get_nodes_and_levels();
        TreeIterator* bfs = this->make_iterator_BFS();
        int max_level_of_dip = 0;

        for (Node *el = bfs->next(); bfs->has_next(); el = bfs->next()) {
            if (max_level_of_dip < nodes_and_levels[el]) {
                max_level_of_dip = nodes_and_levels[el];
            }
        }

        return max_level_of_dip;
    }
}

void Tree::print_leaves() {
    TreeIterator* dfs = this->make_iterator_DFS();
    for (Node* el = dfs->next(); dfs->has_next(); el = dfs->next()) {
        if (el->left == nullptr && el->right == nullptr) {
            std::cout << "Leaf: " << el->data << std::endl;
        }
    }
}

int Tree::tree_length() {
    std::map<Node*, int> nodes_and_levels = get_nodes_and_levels();
    TreeIterator* bfs = this->make_iterator_BFS();
    int max_level = 1;
    int level_of_dip;

    for (Node* el = bfs->next(); bfs->has_next(); el = bfs->next()) {
        level_of_dip = nodes_and_levels[el];
        if (max_level < level_of_dip) {
            max_level = level_of_dip;
        }
    }

    int length = 0;
    for (int i = 1; i <= max_level; i++) {
        length += count_nodes_in_level(i) * (i - 1);
    }

    return length;
}

int Tree::count_nodes_in_level(int data) {
    if (root == nullptr) {
        return 0;
    } else {
        std::map<Node*, int> nodes_and_levels = get_nodes_and_levels();
        TreeIterator* bfs = this->make_iterator_BFS();
        int level_of_dip;
        int count = 0;

        for (Node* el = bfs->next(); bfs->has_next(); el = bfs->next()) {
            level_of_dip = nodes_and_levels[el];
            if (level_of_dip == data) {
                count++;
            }
        }

        return count;
    }
}

std::map<Node*, int> Tree::get_nodes_and_levels() {
    std::map<Node*, int> nodes_and_levels;
    if (root == nullptr) {
        std::cout << "Tree is empty" << std::endl;
        nodes_and_levels[nullptr] = 0;
        return nodes_and_levels;
    } else {
        std::map<Node *, bool> is_visit;
        std::queue<std::pair<Node *, int>> queue;
        queue.push({root, 1});
        is_visit[root] = true;

        while (!queue.empty()) {
            auto [parent, level] = queue.front();
            nodes_and_levels[parent] = level;
            queue.pop();

            if (parent->left != nullptr && !is_visit[parent->left]) {
                queue.push({parent->left, level + 1});
                is_visit[parent->left] = true;
            }

            if (parent->right != nullptr && !is_visit[parent->right]) {
                queue.push({parent->right, level + 1});
                is_visit[parent->right] = true;
            }
        }

        return nodes_and_levels;
    }
}

void Tree::clear(Node* current_elem) {
    if (current_elem != nullptr) {
        clear(current_elem->left);
        clear(current_elem->right);
        delete current_elem;
    }
}

Tree::~Tree() {
    clear(root);
}
