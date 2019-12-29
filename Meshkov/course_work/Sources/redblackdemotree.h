#pragma once

#include "redblacktreehtmldemonstrator.h"

struct RedBlackDemoTreeNode {
    int value = 0;
    RedBlackDemoTreeNode *parent = nullptr, *left = nullptr, *right = nullptr;
    enum class Color : bool {
        BLACK,
        RED
    } color = Color::RED;

    inline bool isBlack() const { return color == Color::BLACK; };
    inline bool isRed() const { return color == Color::RED; };
    inline void recolorToBlack() { color = Color::BLACK; };
    inline void recolorToRed() { color = Color::RED; };
};

class RedBlackDemoTree {
public:
    RedBlackDemoTree();
    RedBlackDemoTree(const RedBlackDemoTree &) = delete;
    ~RedBlackDemoTree();
    RedBlackDemoTree &operator=(const RedBlackDemoTree &) = delete;

    RedBlackTreeHtmlDemonstrator *getHtmlDemonstrator() const;

    using ValueType = int;

    void insert(const ValueType &value);
    void remove(const ValueType &value);
    inline bool contains(const ValueType &value) const {
        return findNode(value) != nullptr;
    }

private:
    using Node = RedBlackDemoTreeNode;
    Node *m_root = nullptr;
    RedBlackTreeHtmlDemonstrator *m_htmlDemonstrator;

    static void erase(Node *node);
    Node *findNode(const ValueType &value) const;

    static Node *getParent(Node *node);
    static Node *getGrandParent(Node *node);
    static Node *getSibling(Node *node);
    static Node *getUncle(Node *node);
    Node **getNodeReferencePlace(Node *node);
    void rotateLeft(Node *node);
    void rotateRight(Node *node);

    [[nodiscard]] Node *insertStupidly(const ValueType &value);
    void insertCase1(Node *node);
    void insertCase2(Node *node);
    void insertCase3(Node *node);
    void insertCase4Step1(Node *node);
    void insertCase4Step2(Node *node);

    static Node *findMaxInSubtree(Node *node);
    static Node *findMinInSubtree(Node *node);
    Node *goToOneChildCase(Node *node);
    void replaceNode(Node *node, Node *replacement);
    static inline bool isBlack(Node *node) {
        return node == nullptr || node->isBlack();
    }
    static inline bool isRed(Node *node) {
        return !isBlack(node);
    }
    void replaceNodeByChild(Node *node);
    void removeCase1(Node *node);
    void removeCase2(Node *node);
    void removeCase3(Node *node);
    void removeCase4(Node *node);
    void removeCase5(Node *node);
    void removeCase6(Node *node);

    void validateProperties();
    static void validateColors(Node *node);
    static size_t validatePathLengths(Node *node);
};

