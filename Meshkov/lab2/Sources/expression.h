#pragma once

#include <string>
#include <memory>
#include <variant>
#include <exception>

class Expression {
public:
    /* "*after" will be changed to the next position after the expression. */
    void load(const std::string &exprStr, std::string::size_type *after = nullptr);

    bool isEmpty() const;

    std::string toString() const;

    class ComplexPowerException : public std::exception {
    };
    /* Differentiates by "variable".
     * May throw ComplexPowerException.
     */
    void derive(const std::string &variable);

private:
    enum class Operation {
        ADDITION,
        SUBTRACTION,
        MULTIPLICATION,
        POW,
        EXP,
    };

    class Node;
    std::shared_ptr<Node> m_head;

    /* "pos" will be changed to the next position after the chunk. */
    std::string readNextChunk(const std::string &exprStr, std::string::size_type &pos);

    /* The following several functions parse expressions using the recursive definitions:
     * expr ::= binary_expr | unary_expr | (trivial_operand)
     * binary_expr ::= (expr_or_trivial_operand binary_oper expr_or_trivial_operand)
     * binary_oper ::= + | - | * | ^
     * unary_expr ::= (exp expr_or_trivial_operand)
     * expr_or_trivial_operand ::= expr | trivial_operand
     * trivial_operand ::= number | variable
     */
    std::shared_ptr<Node> parseExpr(const std::string &exprStr, std::string::size_type &pos);
    std::shared_ptr<Node> parseBinaryExpr(const std::string &exprStr, std::string::size_type &pos);
    std::shared_ptr<Node> parseUnaryExpr(const std::string &exprStr, std::string::size_type &pos);
    std::shared_ptr<Node> parseExprOrTrivialOperand(const std::string &exprStr, std::string::size_type &pos);
    std::shared_ptr<Node> parseTrivialOperand(const std::string &exprStr, std::string::size_type &pos);
    std::shared_ptr<Node> parseNumber(const std::string &exprStr, std::string::size_type &pos);
    std::shared_ptr<Node> parseVariable(const std::string &exprStr, std::string::size_type &pos);
};

class Expression::Node {
public:
    Node() = default;
    Node(const Node &) = delete;
    Node &operator=(const Node &) = delete;

    static std::shared_ptr<Node> makeOperation(Operation operation);
    static std::shared_ptr<Node> makeNumber(double number);
    static std::shared_ptr<Node> makeVariable(std::string variable);
    static std::shared_ptr<Node> makeSubexpression(std::shared_ptr<Node> child);

    std::shared_ptr<Node> deepCopy(bool copySubsequent = false) const;

    void setOperation(Operation operation);
    void setNumber(double number);
    void setVariable(std::string variable);
    void setChild(std::shared_ptr<Node> child);

    enum class Type {
        OPERATION,
        NUMBER,
        VARIABLE,
        SUBEXPRESSION,
        NONE,
    };
    Node::Type getType() const;

    Operation getOperation() const;
    double getNumber() const;
    std::string getVariable() const;
    std::shared_ptr<Node> getChild() const;

    void setNext(std::shared_ptr<Node> next);
    std::shared_ptr<Node> getNext() const;

    std::string toString() const;
    bool containVariable(const std::string &variable, bool checkSubsequent = false) const;
    void derive(const std::string &variable);

private:
    Node::Type m_type = Type::NONE;
    std::variant<Operation, double, std::string, std::shared_ptr<Node>> m_value;
    std::shared_ptr<Node> m_next = nullptr;

    void deriveSubexpression(const std::string &variable);
};
