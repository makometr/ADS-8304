#pragma once

#include <string>
#include <sstream>
#include <set>

class RedBlackDemoTreeNode;

class RedBlackTreeHtmlDemonstrator {
public:
    void printLine(const std::string &line);
    void printDivisor();
    void printHeading(const std::string &heading);

    void highlightNode(RedBlackDemoTreeNode *node);
    void highlightNodes(std::initializer_list<RedBlackDemoTreeNode *> nodes);
    void printTree(RedBlackDemoTreeNode *root);

    void writeToFile(const std::string &path) const;
    
private:
    std::ostringstream m_htmlContent;
    std::set<RedBlackDemoTreeNode *> m_toHighlight;

    void printTreeWithoutHolder(RedBlackDemoTreeNode *root);
};
