#include "redblackdemotree.h"

#include <iostream>
#include <cassert>
#include <string>

RedBlackDemoTree::RedBlackDemoTree()
    : m_htmlDemonstrator(new RedBlackTreeHtmlDemonstrator)
{}

RedBlackDemoTree::~RedBlackDemoTree() {
    erase(m_root);
    delete m_htmlDemonstrator;
}

RedBlackTreeHtmlDemonstrator *RedBlackDemoTree::getHtmlDemonstrator() const {
    return m_htmlDemonstrator;
}

void RedBlackDemoTree::insert(const RedBlackDemoTree::ValueType &value) {
    auto insertedNode = insertStupidly(value);
    insertCase1(insertedNode);
    validateProperties();
}

void RedBlackDemoTree::remove(const RedBlackDemoTree::ValueType &value) {
    auto node = findNode(value);
    if (node == nullptr) {
        m_htmlDemonstrator->printTree(m_root);
        m_htmlDemonstrator->printLine("Nothing to remove. Do nothing.");
        return;
    }
    m_htmlDemonstrator->highlightNode(node);
    m_htmlDemonstrator->printTree(m_root);
    node = goToOneChildCase(node);
    replaceNodeByChild(node);
    validateProperties();
}

void RedBlackDemoTree::erase(RedBlackDemoTree::Node *node) {
    if (node == nullptr)
        return;
    erase(node->left);
    erase(node->right);
    delete node;
}

RedBlackDemoTree::Node *RedBlackDemoTree::findNode(const RedBlackDemoTree::ValueType &value) const {
    auto current = m_root;
    while (true) {
        if (current == nullptr)
            return nullptr;

        if (value > current->value)
            current = current->right;
        else if (value < current->value)
            current = current->left;
        else
            return current;
    }
}

RedBlackDemoTree::Node *RedBlackDemoTree::getParent(RedBlackDemoTree::Node *node) {
    return node == nullptr ? nullptr : node->parent;
}

RedBlackDemoTree::Node *RedBlackDemoTree::getGrandParent(RedBlackDemoTree::Node *node) {
    return getParent(getParent(node));
}

RedBlackDemoTree::Node *RedBlackDemoTree::getSibling(RedBlackDemoTree::Node *node) {
    auto p = getParent(node);
    if (p == nullptr)
        return nullptr;
    if (node == p->left)
        return p->right;
    else
        return p->left;
}

RedBlackDemoTree::Node *RedBlackDemoTree::getUncle(RedBlackDemoTree::Node *node) {
    return getSibling(getParent(node));
}

RedBlackDemoTree::Node **RedBlackDemoTree::getNodeReferencePlace(RedBlackDemoTree::Node *node) {
    assert(node != nullptr);
    if (node->parent != nullptr) {
        if (node->parent->left == node)
            return &node->parent->left;
        else
            return &node->parent->right;
    }
    else {
        return &m_root;
    }
}

void RedBlackDemoTree::rotateLeft(RedBlackDemoTree::Node *node) {
    assert(node != nullptr);
    auto pivot = node->right;
    assert(pivot != nullptr);

    pivot->parent = node->parent;
    *getNodeReferencePlace(node) = pivot;

    node->right = pivot->left;
    if (pivot->left != nullptr)
        pivot->left->parent = node;

    node->parent = pivot;
    pivot->left = node;

    m_htmlDemonstrator->highlightNodes({node, pivot});
}

void RedBlackDemoTree::rotateRight(RedBlackDemoTree::Node *node) {
    assert(node != nullptr);
    auto pivot = node->left;
    assert(pivot != nullptr);

    pivot->parent = node->parent;
    *getNodeReferencePlace(node) = pivot;

    node->left = pivot->right;
    if (pivot->right != nullptr)
        pivot->right->parent = node;

    node->parent = pivot;
    pivot->right = node;

    m_htmlDemonstrator->highlightNodes({node, pivot});
}

RedBlackDemoTree::Node *RedBlackDemoTree::insertStupidly(const RedBlackDemoTree::ValueType &value) {
    auto node = new Node;
    node->value = value;

    Node *prevCurrent = nullptr;
    Node **current = &m_root;
    while (true) {
        if (*current == nullptr) {
            *current = node;
            node->parent = prevCurrent;
            break;
        }
        prevCurrent = *current;
        if (value > (*current)->value)
            current = &(*current)->right;
        else
            current = &(*current)->left;
    }

    m_htmlDemonstrator->highlightNode(node);
    m_htmlDemonstrator->printTree(m_root);

    return node;
}

void RedBlackDemoTree::insertCase1(RedBlackDemoTree::Node *node) {
    if (node->parent == nullptr) {
        // Node has no parent
        node->recolorToBlack();
        m_htmlDemonstrator->printLine("Inserting case 1: The node is root. The node got black color.");
        m_htmlDemonstrator->highlightNode(node);
        m_htmlDemonstrator->printTree(m_root);
    }
    else {
        // Node has parent
        insertCase2(node);
    }
}

void RedBlackDemoTree::insertCase2(RedBlackDemoTree::Node *node) {
    if (node->parent->isBlack()) {
        // Node has black parent
        // Do nothing.
        m_htmlDemonstrator->printLine("Inserting case 2: The node has black parent. Do nothing.");
        return;
    }
    else {
        // Node has red parent
        insertCase3(node);
    }
}

void RedBlackDemoTree::insertCase3(RedBlackDemoTree::Node *node) {
    auto u = getUncle(node);

    if (u != nullptr && u->isRed()) {
        // Node has red parent and red uncle
        node->parent->recolorToBlack();
        u->recolorToBlack();
        auto g = getGrandParent(node);
        g->recolorToRed();

        m_htmlDemonstrator->printLine("Inserting case 3: The node has red parent and red uncle. "
                                      "The uncle and the parent is recolored to black, the grandparent is recolored to red. "
                                      "Start working with the grandparent.");
        m_htmlDemonstrator->highlightNodes({node->parent, u, g});
        m_htmlDemonstrator->printTree(m_root);

        insertCase1(g);
    }
    else {
        // Node has red parent and black or no uncle
        insertCase4Step1(node);
    }
}

void RedBlackDemoTree::insertCase4Step1(RedBlackDemoTree::Node *node) {
    auto g = getGrandParent(node);

    std::string message = "Inserting case 4 step 1: The node has red parent and black or no uncle. "
                          "Preparation to step 2: ";

    if (node == node->parent->right && node->parent == g->left) {
        rotateLeft(node->parent);
        node = node->left;
        message += "Rotation to left around the parent.";
        m_htmlDemonstrator->printLine(message);
        m_htmlDemonstrator->printTree(m_root);
    }
    else if (node == node->parent->left && node->parent == g->right) {
        rotateRight(node->parent);
        node = node->right;
        message += "Rotation to right around the parent.";
        m_htmlDemonstrator->printLine(message);
        m_htmlDemonstrator->printTree(m_root);
    }
    else {
        message += "Do nothing.";
        m_htmlDemonstrator->printLine(message);
    }

    insertCase4Step2(node);
}

void RedBlackDemoTree::insertCase4Step2(RedBlackDemoTree::Node *node) {
    auto g = getGrandParent(node);

    node->parent->recolorToBlack();
    g->recolorToRed();

    std::string message = "Inserting case 4 step 2: The parent recolored to black, "
                          "the grandparent is recolored to red, ";

    if (node == node->parent->left) {
        rotateRight(g);
        message += "rotation to right around the grandparent.";
    }
    else {
        rotateLeft(g);
        message += "rotation to left around the grandparent.";
    }

    m_htmlDemonstrator->printLine(message);
    m_htmlDemonstrator->printTree(m_root);
}

RedBlackDemoTree::Node *RedBlackDemoTree::findMaxInSubtree(RedBlackDemoTree::Node *node) {
    if (node == nullptr)
        return nullptr;
    while (true) {
        if (node->right == nullptr)
            return node;
        node = node->right;
    }
}

RedBlackDemoTree::Node *RedBlackDemoTree::findMinInSubtree(RedBlackDemoTree::Node *node) {
    if (node == nullptr)
        return nullptr;
    while (true) {
        if (node->left == nullptr)
            return node;
        node = node->left;
    }
}

RedBlackDemoTree::Node *RedBlackDemoTree::goToOneChildCase(RedBlackDemoTree::Node *node) {
    std::string message = "Going to one-child case: ";

    if (node->left == nullptr || node->right == nullptr) {
        message += "The node already doesn't have more than one child. Do nothing.";
        m_htmlDemonstrator->printLine(message);
        return node;
    }
    // Here node->left != nullptr and node->right != nullptr

    message += "The node's value was replaced by its ";

    Node *descendant = findMaxInSubtree(node->left);
    message += "left max";

    node->value = descendant->value;

    message += " descendant's value. Start working with the descendant.";
    m_htmlDemonstrator->printLine(message);
    m_htmlDemonstrator->highlightNodes({node, descendant});
    m_htmlDemonstrator->printTree(m_root);

    return descendant;
}

void RedBlackDemoTree::replaceNode(RedBlackDemoTree::Node *node, RedBlackDemoTree::Node *replacement) {
    assert(node != nullptr);
    if (replacement != nullptr) {
        replacement->parent = node->parent;
    }
    *getNodeReferencePlace(node) = replacement;
    // Caller should delete "node"
}

void RedBlackDemoTree::replaceNodeByChild(RedBlackDemoTree::Node *node) {
    std::string message = "Replacing the node by its child: ";

    auto child = (node->right == nullptr ? node->left : node->right);
    if (node->isBlack()) {
        message += "The node is black, ";
        if (isRed(child)) {
            child->recolorToBlack();
            message += "child is red. Recoloring the child to black and replacing the node by the child.";
        }
        else { // child is black
            // Using "node" instead "child" (cause they both have black color but child may be null.
            message += "child is black. Replacing was deferred.";
            m_htmlDemonstrator->printLine(message);
            removeCase1(node);
            message = "Replacing the node by its child (continuation): Just replacing the node by the child.";
        }
    }
    else { // node is red
        message += "Node is red (=> the child is null). Just replacing the node by the child.";
    }
    replaceNode(node, child);
    delete node;
    m_htmlDemonstrator->printLine(message);
    m_htmlDemonstrator->highlightNode(child);
    m_htmlDemonstrator->printTree(m_root);
}

void RedBlackDemoTree::removeCase1(RedBlackDemoTree::Node *node) {
    if (node->parent == nullptr) {
        // Node is root
        m_htmlDemonstrator->printLine("Delete case 1: The node is root. Do nothing.");
    }
    else {
        // Node is no root
        removeCase2(node);
    }
}

void RedBlackDemoTree::removeCase2(RedBlackDemoTree::Node *node) {
    Node *s = getSibling(node);
    if (isRed(s)) {
        std::string message = "Delete case 2: The sibling is red. ";

        node->parent->recolorToRed();
        s->recolorToBlack();
        message += "Recoloring the parent to red and the sibling to black, ";

        if (node == node->parent->left) {
            rotateLeft(node->parent);
            message += "rotation to left around the parent.";
        }
        else {
            rotateRight(node->parent);
            message += "rotation to right around the parent.";
        }

        m_htmlDemonstrator->printLine(message);
        m_htmlDemonstrator->highlightNodes({node->parent, s});
        m_htmlDemonstrator->printTree(m_root);
    }
    removeCase3(node);
}

void RedBlackDemoTree::removeCase3(RedBlackDemoTree::Node *node) {
    Node *s = getSibling(node);
    if (isBlack(node->parent) && isBlack(s) && isBlack(s->left) && isBlack(s->right)) {
        std::string message;
        message += "Remove case 3: The node's parent, the sibling, the sibling' left child, "
                   "the sibling's right child is black. ";

        s->recolorToRed();
        message += "Recoloring the sibling to red. Start working with the node's parent.";

        m_htmlDemonstrator->printLine(message);
        m_htmlDemonstrator->highlightNode(s);
        m_htmlDemonstrator->printTree(m_root);
        removeCase1(node->parent);
    }
    else {
        removeCase4(node);
    }
}

void RedBlackDemoTree::removeCase4(RedBlackDemoTree::Node *node) {
    Node *s = getSibling(node);
    if (isRed(node->parent) && isBlack(s) && isBlack(s->left) && isBlack(s->right)) {
        std::string message;
        message += "Remove case 4: The node's parent is red but "
                   "the sibling, the sibling' left child, the sibling's right child is black. ";

        s->recolorToRed();
        node->parent->recolorToBlack();
        message += "Recoloring the sibling to red and the node's parent to black.";

        m_htmlDemonstrator->printLine(message);
        m_htmlDemonstrator->highlightNodes({s, node->parent});
        m_htmlDemonstrator->printTree(m_root);
    }
    else {
        removeCase5(node);
    }
}

void RedBlackDemoTree::removeCase5(RedBlackDemoTree::Node *node) {
    Node *s = getSibling(node);
    if (isBlack(s)) {
        std::string message;
        message += "Remove case 5: The sibling is black, ";

        if ((node == node->parent->left) && isBlack(s->right) && isRed(s->left)) {
            message += "the node is the left child of its parent, the sibling's right child is black "
                       "and the sibling's left child is red. ";

            s->recolorToRed();
            s->left->recolorToBlack();
            rotateRight(s);
            message += "Recoloring the sibling to red, the sibling's left child to black, "
                       "rotation right around the sibling.";
        }
        else if ((node == node->parent->right) && isBlack(s->left) && isRed(s->right)) {
            message += "the node is the right child of its parent, the sibling's left child is black "
                       "and the sibling's right child is red. ";

            s->recolorToRed();
            s->right->recolorToBlack();
            rotateLeft(s);
            message += "Recoloring the sibling to red, the sibling's right child to black, "
                       "rotation left around the sibling.";
        }
    }
    removeCase6(node);
}

void RedBlackDemoTree::removeCase6(RedBlackDemoTree::Node *node) {
    Node *s = getSibling(node);

    std::string message = "Remove case 6: ";

    s->color = node->parent->color;
    node->parent->recolorToBlack();
    message += "Recoloring sibling's color to the color of the node's parent,"
               "recoloring the node's parent to black. ";

    if (node == node->parent->left) {
        s->right->recolorToBlack();
        rotateLeft(node->parent);
        message += "Recoloring the sibling's right child to black, rotation to left around the node's parent.";
    }
    else {
        s->left->recolorToBlack();
        rotateRight(node->parent);
        message += "Recoloring the sibling's left child to black, rotation to right around the node's parent.";
    }
}

void RedBlackDemoTree::validateProperties() {
#ifndef NDEBUG
    if (m_root != nullptr) {
        assert(m_root->isBlack());
        validateColors(m_root);
        validatePathLengths(m_root);
    }

    std::cout << "Red-black tree properties validation: ok" << std::endl;
#endif
}

size_t RedBlackDemoTree::validatePathLengths(RedBlackDemoTree::Node *node) {
    if (node == nullptr)
        return 1;
    auto len = validatePathLengths(node->left);
    assert(len == validatePathLengths(node->right));
    if (node->isBlack())
        return len + 1;
    else
        return len;
}

void RedBlackDemoTree::validateColors(RedBlackDemoTree::Node *node) {
    if (node == nullptr)
        return;
    if (node->isRed()) {
        assert(node->left == nullptr || node->left->isBlack());
        assert(node->right == nullptr || node->right->isBlack());
    }
    validateColors(node->left);
    validateColors(node->right);
}
