#include "Tree.h"
#include "Iterator.h"
Tree::Tree(int root_data) {
    root = std::make_shared<Node>();
    root->data = root_data;
}

std::shared_ptr<TreeIterator> Tree::make_iterator_DFS() {
    return std::make_shared<TreeIteratorDFS>(root);
}

std::shared_ptr<TreeIterator> Tree::make_iterator_BFS() {
    return std::make_shared<TreeIteratorBFS>(root);
}

void Tree::insert(int element) {
    if (root == nullptr) {
        root = std::make_shared<Node>();
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

void Tree::insert(std::shared_ptr<Node>& parent, int element) {
    if (parent == nullptr) {
        parent = std::make_shared<Node>();
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
    std::map<std::shared_ptr<Node>, int> nodes_and_levels = get_nodes_and_levels();
    std::shared_ptr<TreeIterator> bfs = this->make_iterator_BFS();
    int level_of_dip = 0;

    for (std::shared_ptr<Node> el = bfs->next(); bfs->has_next(); el = bfs->next()) {
        level_of_dip = nodes_and_levels[el];
        std::cout << std::string(level_of_dip * 5, ' ') << el->data << std::endl;
    }
}

int Tree::dip() {
    if (root == nullptr) {
        return 0;
    } else {
        std::map<std::shared_ptr<Node>, int> nodes_and_levels = get_nodes_and_levels();
        if (nodes_and_levels.size() == 1)
            return 1;
        std::shared_ptr<TreeIterator> bfs = this->make_iterator_BFS();
        int max_level_of_dip = 0;

        for (std::shared_ptr<Node> el = bfs->next(); bfs->has_next(); el = bfs->next()) {
            if (max_level_of_dip < nodes_and_levels[el]) {
                max_level_of_dip = nodes_and_levels[el];
            }
        }

        return max_level_of_dip;
    }
}

void Tree::print_leaves() {
    std::map<std::shared_ptr<Node>, int> nodes_and_levels = get_nodes_and_levels();
    if (nodes_and_levels.size() == 1) {
        std::cout << "Leaf: " << root->data << std::endl;
        return;
    }
    std::shared_ptr<TreeIterator> dfs = this->make_iterator_DFS();
    for (std::shared_ptr<Node> el = dfs->next(); dfs->has_next(); el = dfs->next()) {
        if (el->left == nullptr && el->right == nullptr) {
            std::cout << "Leaf: " << el->data << std::endl;
        }
    }
}

int Tree::tree_length() {
    std::map<std::shared_ptr<Node>, int> nodes_and_levels = get_nodes_and_levels();
    if (nodes_and_levels.size() == 1)
        return 1;
    std::shared_ptr<TreeIterator> bfs = this->make_iterator_BFS();
    int max_level = 1;
    int level_of_dip;

    for (std::shared_ptr<Node> el = bfs->next(); bfs->has_next(); el = bfs->next()) {
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
        std::map<std::shared_ptr<Node>, int> nodes_and_levels = get_nodes_and_levels();
        if (nodes_and_levels.size() == 1) {
            return 1;
        }
        std::shared_ptr<TreeIterator> bfs = this->make_iterator_BFS();
        int level_of_dip;
        int count = 0;

        for (std::shared_ptr<Node> el = bfs->next(); bfs->has_next(); el = bfs->next()) {
            level_of_dip = nodes_and_levels[el];
            if (level_of_dip == data) {
                count++;
            }
        }

        return count;
    }
}

std::map<std::shared_ptr<Node>, int> Tree::get_nodes_and_levels() {
    std::map<std::shared_ptr<Node>, int> nodes_and_levels;
    if (root == nullptr) {
        std::cout << "Tree is empty" << std::endl;
        return std::map<std::shared_ptr<Node>, int>();
    } else {
        std::map<std::shared_ptr<Node>, bool> is_visit;
        std::queue<std::pair<std::shared_ptr<Node>, int>> queue;
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
