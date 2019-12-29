#include "Tree.h"
#include "Iter.h"

Tree::Tree(int root_data) {
    Tree_root = std::make_shared<Node_of_tree>();
    Tree_root->value = root_data;
}

std::shared_ptr<TreeIter> Tree::make_DFS_iter() {
    return std::make_shared<TreeIterDFS>(Tree_root);
}

std::shared_ptr<TreeIter> Tree::make_BFS_iter() {
    return std::make_shared<TreeIterBFS>(Tree_root);
}

void Tree::insert_elem(int element) {
    if (Tree_root == nullptr) {
        Tree_root = std::make_shared<Node_of_tree>();
        Tree_root->value = element;
    } else {
        if (Tree_root->value > element) {
            insert_elem(Tree_root->left_Node, element);
        }

        if (Tree_root->value < element) {
            insert_elem(Tree_root->right_Node, element);
        }

        if (Tree_root->value == element) {
            Tree_root->value = element;
        }
    }
}

void Tree::insert_elem(std::shared_ptr<Node_of_tree>& parent, int element) {
    if (parent == nullptr) {
        parent = std::make_shared<Node_of_tree>();
        parent->value = element;
    } else {
        if (parent->value > element) {
            insert_elem(parent->left_Node, element);
        }

        if (parent->value < element) {
            insert_elem(parent->right_Node, element);
        }

        if (parent->value == element) {
            parent->value = element;
        }
    }
}

void Tree::cout_tree() {
    std::map<std::shared_ptr<Node_of_tree>, int> nodes_and_levels = nodes_at_levels();
    std::shared_ptr<TreeIter> bfs = this->make_BFS_iter();
    int level_of_dip = 0;

    for (std::shared_ptr<Node_of_tree> el = bfs->next(); bfs->has_next(); el = bfs->next()) {
        level_of_dip = nodes_and_levels[el];
        std::cout << std::string(level_of_dip * 5, ' ') << el->value << std::endl;
    }
}

int Tree::dip_tree() {
    if (Tree_root == nullptr) {
        return 0;
    } else {
        std::map<std::shared_ptr<Node_of_tree>, int> nodes_and_levels = nodes_at_levels();
        if (nodes_and_levels.size() == 1)
            return 1;
        std::shared_ptr<TreeIter> bfs = this->make_BFS_iter();
        int max_level_of_dip = 0;

        for (std::shared_ptr<Node_of_tree> el = bfs->next(); bfs->has_next(); el = bfs->next()) {
            if (max_level_of_dip < nodes_and_levels[el]) {
                max_level_of_dip = nodes_and_levels[el];
            }
        }

        return max_level_of_dip;
    }
}

void Tree::cout_leaves() {
    std::map<std::shared_ptr<Node_of_tree>, int> nodes_and_levels = nodes_at_levels();
    if (nodes_and_levels.size() == 1) {
        std::cout << "Leaf: " << Tree_root->value << std::endl;
        return;
    }
    std::shared_ptr<TreeIter> dfs = this->make_DFS_iter();
    for (std::shared_ptr<Node_of_tree> el = dfs->next(); dfs->has_next(); el = dfs->next()) {
        if (el->left_Node == nullptr && el->right_Node == nullptr) {
            std::cout << "Leaf: " << el->value << std::endl;
        }
    }
}

int Tree::dip_of_tree() {
    std::map<std::shared_ptr<Node_of_tree>, int> nodes_and_levels = nodes_at_levels();
    if (nodes_and_levels.size() == 1)
        return 1;
    std::shared_ptr<TreeIter> bfs = this->make_BFS_iter();
    int max_level = 1;
    int level_of_dip;

    for (std::shared_ptr<Node_of_tree> el = bfs->next(); bfs->has_next(); el = bfs->next()) {
        level_of_dip = nodes_and_levels[el];
        if (max_level < level_of_dip) {
            max_level = level_of_dip;
        }
    }

    int length = 0;
    for (int i = 1; i <= max_level; i++) {
        length += nodes_at_level(i) * (i - 1);
    }

    return length;
}

int Tree::nodes_at_level(int data) {
    if (Tree_root == nullptr) {
        return 0;
    } else {
        std::map<std::shared_ptr<Node_of_tree>, int> nodes_and_levels = nodes_at_levels();
        if (nodes_and_levels.size() == 1) {
            return 1;
        }
        std::shared_ptr<TreeIter> bfs = this->make_BFS_iter();
        int level_of_dip;
        int count = 0;

        for (std::shared_ptr<Node_of_tree> el = bfs->next(); bfs->has_next(); el = bfs->next()) {
            level_of_dip = nodes_and_levels[el];
            if (level_of_dip == data) {
                count++;
            }
        }

        return count;
    }
}

std::map<std::shared_ptr<Node_of_tree>, int> Tree::nodes_at_levels() {
    std::map<std::shared_ptr<Node_of_tree>, int> nodes_and_levels;
    if (Tree_root == nullptr) {
        std::cout << "Empty" << std::endl;
        return std::map<std::shared_ptr<Node_of_tree>, int>();
    } else {
        std::map<std::shared_ptr<Node_of_tree>, bool> is_visit;
        std::queue<std::pair<std::shared_ptr<Node_of_tree>, int>> queue;
        queue.push({Tree_root, 1});
        is_visit[Tree_root] = true;

        while (!queue.empty()) {
            auto [parent, level] = queue.front();
            nodes_and_levels[parent] = level;
            queue.pop();

            if (parent->left_Node != nullptr && !is_visit[parent->left_Node]) {
                queue.push({parent->left_Node, level + 1});
                is_visit[parent->left_Node] = true;
            }

            if (parent->right_Node != nullptr && !is_visit[parent->right_Node]) {
                queue.push({parent->right_Node, level + 1});
                is_visit[parent->right_Node] = true;
            }
        }

        return nodes_and_levels;
    }
}
