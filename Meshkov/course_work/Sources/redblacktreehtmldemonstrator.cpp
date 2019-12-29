#include "redblacktreehtmldemonstrator.h"

#include "redblackdemotree.h"
#include "redblacktreedemohtmltemplate.h"

#include <fstream>
#include <iostream>

void RedBlackTreeHtmlDemonstrator::printLine(const std::string &line) {
    m_htmlContent << "\n";
    m_htmlContent << "<div class=text>" << line << "</div>\n";
}

void RedBlackTreeHtmlDemonstrator::printDivisor() {
    m_htmlContent << "<hr>\n";
}

void RedBlackTreeHtmlDemonstrator::printHeading(const std::string &heading) {
    m_htmlContent << "\n";
    m_htmlContent << "<div class=heading>" << heading << "</div>\n";
}

void RedBlackTreeHtmlDemonstrator::printTreeWithoutHolder(RedBlackDemoTreeNode *root) {
    if (root == nullptr) {
        m_htmlContent << "<div class=black-node>null</div>\n";
        return;
    }

    m_htmlContent << "<div class=tree>\n";

    m_htmlContent << "<div class=root>\n";
    m_htmlContent << std::string("<div class=\"")
                  << (root->isRed() ? "red-node" : "black-node")
                  << (m_toHighlight.count(root) != 0 ? " highlighted" : "")
                  << "\">" << root->value << "</div>\n";
    m_htmlContent << "</div>\n"; // Closing <div class=root>

    m_htmlContent << "<div class=children>\n";
    printTreeWithoutHolder(root->left);
    printTreeWithoutHolder(root->right);
    m_htmlContent << "</div>\n"; // Closing <div class=children>

    m_htmlContent << "</div>\n"; // Closing <div class=tree>
}

void RedBlackTreeHtmlDemonstrator::highlightNode(RedBlackDemoTreeNode *node) {
    m_toHighlight.insert(node);
}

void RedBlackTreeHtmlDemonstrator::highlightNodes(std::initializer_list<RedBlackDemoTreeNode *> nodes) {
    m_toHighlight.insert(nodes);
}


void RedBlackTreeHtmlDemonstrator::printTree(RedBlackDemoTreeNode *root) {
    m_htmlContent << "\n";
    m_htmlContent << "<div class=tree-holder>\n";
    printTreeWithoutHolder(root);
    m_htmlContent << "</div>\n";
    m_toHighlight.clear();
}

void RedBlackTreeHtmlDemonstrator::writeToFile(const std::string &path) const {
    std::ofstream file;
    file.open(path);
    if (file.is_open()) {
        file << redBlackTreeDemoHtmlTemplateTopPart;
        file << m_htmlContent.str();
        file << redBlackTreeDemoHtmlTemplateBottomPart;
        file.close();
    }
    else {
        std::cerr << "Error: file opening is failed." << std::endl;
    }
}
