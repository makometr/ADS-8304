#ifndef LAB2_EXPRESSION_H_
#define LAB2_EXPRESSION_H_

#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <variant>
#include <stack>

constexpr bool DEBUG = true;

namespace lab2
{
    enum OperationType {NONE, ADDITION, SUBTRACTION, MULTIPLICATION, DIVISION};  
}

namespace std
{
    // overload std::to_string for two useful cases
    std::string to_string(const std::string& string)
    {
        return string;
    }
    
    std::string to_string(lab2::OperationType operationType)
    {
        if(operationType == lab2::OperationType::ADDITION)
            return "+";
        if(operationType == lab2::OperationType::SUBTRACTION)
            return "-";
        if(operationType == lab2::OperationType::MULTIPLICATION)
            return "*";
        if(operationType == lab2::OperationType::DIVISION)
            return "/";
        return "?";
    }
}

// TrivariateHierarchicalList class was designed to store either a value of one 
// out of three possible types or a pointer to a sublist  
template<class T, class U, class V>
class TrivariateHierarchicalList
{
protected:
    // Node inner class was designed to act as a single node of the 
    // TrivariateHierarchicalList class
    class Node
    {
    public:
        Node()
        {
            this->content_ = nullptr;
        }
    
        ~Node()
        {
            if(std::holds_alternative<Node*>(content_))
                delete std::get<Node*>(content_);
            delete this->next_;
        }
        
        Node* next()
        {
            return this->next_;
        }
        
        void setNext(Node* const next)
        {
            this->next_ = next;
        }
        
        const std::variant<T, U, V, Node*>& content()
        {
            return this->content_;
        }
        
        void setContent(const T& content)
        {
            this->content_ = content;
        }
        
        void setContent(const U& content)
        {
            this->content_ = content;
        }
        
        void setContent(const V& content)
        {
            this->content_ = content;
        }
        
        void setContent(Node* const content)
        {
            this->content_ = content;
        }

        std::string represent()
        {
            std::string representation = "(";
            auto current = this;
            while(current != nullptr)
            {
                if(std::holds_alternative<Node*>(current->content_) &&
                   std::get<Node*>(current->content()) != nullptr)
                    representation += 
                        std::get<Node*>(current->content_)->represent();
                else if(std::holds_alternative<T>(current->content_))
                    representation +=
                        std::to_string(std::get<T>(current->content_));
                else if(std::holds_alternative<U>(current->content_))
                    representation +=
                        std::to_string(std::get<U>(current->content_));
                else if(std::holds_alternative<V>(current->content_))
                    representation +=
                        std::to_string(std::get<V>(current->content_));
                if(current->next_ != nullptr)
                    representation += ' ';
                current = current->next_;
            }
            return representation + ')';
        }
        
    private:
        std::variant<T, U, V, Node*> content_;
        Node *next_ = nullptr;
    };
    
    // Iterator inner class was designed to facilitate iteration through a
    // hierarchical list
    class Iterator
    {
    public:
        Iterator(Node *node=nullptr)
        {
            this->current = node;
            this->previousNodeCountStack.push(0);
            this->normalizePosition();
        }
        
        Iterator &operator++()
        {
            if(this->current == nullptr)
                return *this;
            this->current = this->current->next();
            previousNodeCountStack.top() += 1;
            this->normalizePosition();
            return *this;
        }
        
        Iterator  operator++(int)
        {
            auto old = *this;
            ++(*this);
            return old;
        }
        
        Node &operator* ()
        {
            return *(this->current); 
        }
        
        Node *operator-> ()
        {
            return &**this;
        }
        
        bool operator== (const Iterator& that)
        {
            return this->current == that.current && 
                   this->nodeStack == that.nodeStack;
        }
        
        bool operator!= (const Iterator& that)
        {
            return this->current != that.current || 
                   this->nodeStack != that.nodeStack;
        }
        
        size_t getPreviousNodeCount()
        {
            return this->previousNodeCountStack.top();
        }
        
    private:
        std::stack<Node*> nodeStack;
        std::stack<size_t> previousNodeCountStack;
        Node* current = nullptr;
        
        // ensure that this->current holds a pointer to an atomic node
        void normalizePosition()
        {
            while(this->current == nullptr && this->nodeStack.size() > 0 ||
                  this->current != nullptr && 
                  std::holds_alternative<Node*>(this->current->content()) &&
                  std::get<Node*>(this->current->content()) != nullptr)
            {
                while(this->current == nullptr && this->nodeStack.size() > 0)
                {
                    this->current = this->nodeStack.top()->next();
                    this->nodeStack.pop();
                    this->previousNodeCountStack.pop();
                }
                while(std::holds_alternative<Node*>(this->current->content()) &&
                      std::get<Node*>(this->current->content()) != nullptr)
                {
                    this->nodeStack.push(this->current);
                    previousNodeCountStack.top() += 1;
                    this->previousNodeCountStack.push(0);
                    this->current = std::get<Node*>(current->content());
                }
            }
        }
    };
    
    Node* head()
    {
        return this->head_;
    }
    
private:
    Node* head_ = nullptr;

public:
    TrivariateHierarchicalList()
    {
        this->head_ = new Node();
    }

    ~TrivariateHierarchicalList()
    {
        delete this->head_;
    }

    std::string represent()
    {
        return this->head_->represent();
    }
        
    Iterator begin()
    {
        return Iterator(this->head_);
    }
        
    Iterator end()
    {
        return Iterator();
    }


};

namespace lab2
{   
    template<class T>
    T stoT(std::string);
    template<>
    short stoT<short>(std::string str){return std::stoi(str);}
    template<>
    int stoT<int>(std::string str){return std::stoi(str);}
    template<>
    long stoT<long>(std::string str){return std::stol(str);}
    template<>
    long long stoT<long long>(std::string str){return std::stoll(str);}
    template<>
    unsigned short stoT<unsigned short>(std::string str){return std::stoi(str);}
    template<>
    unsigned int stoT<unsigned int>(std::string str){return std::stoul(str);}
    template<>
    unsigned long stoT<unsigned long>(std::string str){return std::stoul(str);}
    template<>
    unsigned long long stoT<unsigned long long>(std::string str){return std::stoull(str);}
    template<>
    float stoT<float>(std::string str){return std::stof(str);}
    template<>
    double stoT<double>(std::string str){return std::stod(str);}
    template<>
    long double stoT<long double>(std::string str){return std::stold(str);}
}

template<class T>
class Expression
: public TrivariateHierarchicalList<T, std::string, lab2::OperationType>
{
    typedef typename \
        TrivariateHierarchicalList<T, std::string, lab2::OperationType>::Node \
        ExpressionNode;
public:
    Expression(const std::string &expression) 
    : TrivariateHierarchicalList<T, std::string, lab2::OperationType>()
    {
        std::regex regex("^\\s*");
        auto expression_ = regex_replace(expression, std::regex("^\\s*"), "");
        expression_ = regex_replace(expression_, std::regex("\\s*$"), "");
        expression_ = regex_replace(expression_, std::regex("\\s+"), " ");
        if(DEBUG)
        {
            std::cout << "Acquired string: \"" << 
                 expression_ << "\"" << std::endl;
            std::cout << "Acquired string length: " << 
                 expression_.length() << std::endl;
        }
        if(expression_.length() == 0 || regex_match(expression_, 
                                                    std::regex("^\\s*$")))
        {
            this->parsingErrors.push_back("The provided expression is empty");
        }
        else
        {
            this->parse(this->head(), expression_.begin(), expression_.end());
        }
    }

    bool isCorrect()
    {
        std::stack<std::variant<T,bool>> execution_stack;
        executionErrors.resize(0);
        this->checkNodes(execution_stack);
        if(execution_stack.size() > 1)
            this->executionErrors.push_back(std::string("There ") + 
                 (execution_stack.size() > 2 ? "are " : "is ") + 
                 std::to_string(execution_stack.size() - 1) + 
                 " unused operands left.");
        if(this->parsingErrors.size() > 0 || this->executionErrors.size() > 0)
            return false;
        return true;
    }

    std::string getErrors()
    {   
        if(this->parsingErrors.size() == 0 && 
           !(this->executionErrors.size() > 0 || this->isCorrect()))
            return("There are no errors found.\n");
            
        auto total_length = 0;
        for(auto error : this->parsingErrors)
            total_length += error.length() + 1;
        for(auto error : this->executionErrors)
            total_length += error.length() + 1;
            
        std::string result;
        for(auto error : this->parsingErrors)
            result += error + "\n";
        for(auto error : this->executionErrors)
            result += error + "\n";
        return "Errors:\n" + result;
    }

private:
    std::vector<std::string> parsingErrors{};
    std::vector<std::string> executionErrors{};

    std::string::const_iterator parse(ExpressionNode *node,
                                      std::string::const_iterator current,
                                      std::string::const_iterator end)
    {
        static size_t depth = 0;
        depth += 1;
        if(DEBUG)
        {
            std::cout << std::string(depth - 1, ' ') << 
                 "|~~~~~~~~~~~" << std::endl;
            std::cout << std::string(depth - 1, ' ') << 
                 "| the function \"parse\" was called" << std::endl;
            std::cout << std::string(depth - 1, ' ') << 
                 "| depth: " << depth << std::endl;
        }

        auto currentNode = node;

        while(current != end && *current == ' ')
        {
            current += 1;
        }

        if(current != end && *current == '(')
        { 
            if(depth == 1 && DEBUG)
                std::cout << std::string(depth - 1, ' ') << 
                     "| the token \"(\" was acquired: " << std::endl;
            current += 1;
            while(current != end)
            {
                while(current != end && *current == ' ')
                {
                    current += 1;
                }
                if(current == end)
                {
                    this->parsingErrors.push_back("Expression ended unexpectedly");
                    return end;
                }

                if(*current == '(')
                {
                    if(DEBUG)
                    {
                        std::cout << std::string(depth - 1, ' ') << 
                             "| the token \"(\" was acquired: " << std::endl;
                    }
                    currentNode->setContent(new ExpressionNode());
                    current = parse(
                        std::get<ExpressionNode*>(currentNode->content()), 
                        current, end);
                }
                
                else if(*current == ')')
                {
                    if(DEBUG)
                    {
                        std::cout << std::string(depth - 1, ' ') << 
                             "| the token \")\" was acquired: " << std::endl;
                    }
                    if(std::holds_alternative<ExpressionNode*>(currentNode->
                       content())&& std::get<ExpressionNode*>(currentNode->
                       content()) == nullptr)
                    {
                        this->parsingErrors.push_back("The provided"\
                             "expression contains empty parentheses");
                    }
                    current += 1;
                    break;
                }

                else if('A' <= *current && *current <= 'Z' ||
                                           *current == '_' ||
                        'a' <= *current && *current <= 'z')
                {
                    std::smatch match;
                    std::regex regex("^([_A-Za-z][_A-Za-z0-9]*)");
                    std::regex_search (current, end, match, regex);
                    currentNode->setContent(match[1]);
                    if(DEBUG)
                    {
                        std::cout << std::string(depth - 1, ' ') << 
                             "| the token  \"" << 
                             std::get<std::string>(currentNode->content()) << 
                             "\" was acquired." << std::endl;
                    }
                    current += match[1].length();
                }

                else if('0' <= *current && *current <= '9')
                {
                    std::smatch match;
                    std::regex regex("^([0-9]+(\\.[0-9]+)?)");
                    std::regex_search (current, end, match, regex);
                    currentNode->setContent(lab2::stoT<T>(match[1]));
                    if(DEBUG)
                    {
                        std::cout << std::string(depth - 1, ' ') << 
                             "| the token  \"" << 
                             std::get<T>(currentNode->content()) << 
                             "\" was acquired." << std::endl;
                    }
                    current += match[1].length();
                }

                else if(*current == '+')
                {
                    currentNode->setContent(lab2::OperationType::ADDITION);
                    current += 1;
                    if(DEBUG)
                    {
                        std::cout << std::string(depth - 1, ' ') << 
                             "| the token  \"+\" was acquired." << std::endl;
                    }
                }

                else if(*current == '-')
                {
                    currentNode->setContent(lab2::OperationType::SUBTRACTION);
                    current += 1;
                    if(DEBUG)
                    {
                        std::cout << std::string(depth - 1, ' ') << 
                             "| the token  \"+\" was acquired." << std::endl;
                    }
                }

                else if(*current == '*')
                {
                    currentNode->setContent(lab2::OperationType::MULTIPLICATION);
                    current += 1;
                    if(DEBUG)
                    {
                        std::cout << std::string(depth - 1, ' ') << 
                             "| the token  \"*\" was acquired." << std::endl;
                    }
                }

                else if(*current == '/')
                {
                    currentNode->setContent(lab2::OperationType::DIVISION);
                    current += 1;
                    if(DEBUG)
                    {
                        std::cout << std::string(depth - 1, ' ') << 
                             "| the token  \"/\" was acquired." << std::endl;
                    }
                }
                
                else
                {
                    this->parsingErrors.push_back("Unexpected symbol: " +
                                                   std::to_string(int(*current)));
                }

                if(current != end && *current != ')')
                {
                    currentNode->setNext(new ExpressionNode());
                    currentNode = currentNode->next();
                }
            }
        }
        else
        {
            this->parsingErrors.push_back("The symbol \"(\" is abscent when necessary");
        }
        depth -= 1;
        if(depth == 0)
        {
            if(current != end)
            {
                this->parsingErrors.push_back("The string contains the "\
                "following characters after the last closing bracket:\n\t\"" +
                std::string(current, end) + "\"");
            }
        }
        if(DEBUG)
        {
            std::cout << "|~~~~~~~~~~~" << std::endl;
            if(depth > 0)
                std::cout << std::string(depth - 1, ' ') << "| depth: " << 
                     depth << std::endl;
        }
        return current;
    }

    void checkNodes(std::stack<std::variant<T,bool>>& execution_stack)
    {
        size_t termCount = 1;
        for(auto current = this->begin(), end = this->end(); 
            current != end; termCount += 1, ++current)
        {
            if(std::holds_alternative<T>(current->content()))
            {
                execution_stack.push(std::get<T>(current->content()));
                if(DEBUG)
                {
                    std::cout << "~~~~~~" << std::endl;
                    std::cout << "Term " + std::to_string(termCount) + 
                         ", the value is " 
                         << std::get<T>(current->content()) 
                         << std::endl;
                }
            }
            else if(std::holds_alternative<std::string>(current->content()))
            {
                execution_stack.push(true);
                if(DEBUG)
                {
                    std::cout << "~~~~~~" << std::endl;
                    std::cout << "Term " + std::to_string(termCount) + 
                         ", the value is undecidable" << std::endl;
                }
            }
            else if(std::holds_alternative<lab2::OperationType>(current->content()))
            {
                auto previousNodeCount = current.getPreviousNodeCount();
                auto operationType = std::get<lab2::OperationType>(current->content());
                if(DEBUG)
                {
                    std::cout << "~~~~~~" << std::endl;
                    std::cout << "Term " + std::to_string(termCount) + 
                         ", the operation is \"" << 
                         std::to_string(operationType) + "\""
                         << std::endl;
                }
                if(previousNodeCount == 0)
                {
                    this->executionErrors.push_back("Term " 
                         + std::to_string(termCount) + ": The operation \"" + 
                         std::to_string(operationType) +
                         "\" has too few (0) arguments.");
                }
                else if(previousNodeCount > 2)
                {
                    this->executionErrors.push_back("Term " 
                         + std::to_string(termCount) + ": The operation \"" + 
                         std::to_string (operationType) + "\" has too many (" + 
                         std::to_string(previousNodeCount) + ") arguments.");
                    while(previousNodeCount --> 0)
                    {
                        if(DEBUG)
                        {
                            std::cout << "Term " + std::to_string(termCount) + 
                                 ", the operand " + 
                                 std::to_string(previousNodeCount + 1) +
                                 " is removed from the stack" << std::endl;
                        }
                        execution_stack.pop();
                    }
                    execution_stack.push(true);
                    if(DEBUG)
                    {
                        std::cout << "Term " + std::to_string(termCount) + 
                             ", the result is meaningless" << std::endl;
                    }
                }
                else if(previousNodeCount == 1)
                {
                    if(operationType == lab2::OperationType::SUBTRACTION)
                    {
                        if(std::holds_alternative<T>(execution_stack.top()))
                        {
                            auto operand = std::get<T>(execution_stack.top());
                            if(DEBUG)
                            {
                                std::cout << "Term " 
                                     + std::to_string(termCount) + 
                                     ", the operand is " << operand 
                                     << std::endl;
                            }
                            execution_stack.pop();
                            execution_stack.push(-operand);
                        }
                        else
                        {
                            if(DEBUG)
                            {
                                std::cout << "Term " 
                                     + std::to_string(termCount) + 
                                     ", the operand is undecidable" 
                                     << std::endl;
                            }
                            execution_stack.pop();
                            execution_stack.push(true);
                        }
                    }
                    else
                    {
                        this->executionErrors.push_back("Term " 
                              + std::to_string(termCount) +
                              ": The operation \"" +     
                              std::to_string(operationType) +
                              "\" has too few (1) arguments.");
                        execution_stack.pop();
                        if(DEBUG)
                        {
                            std::cout << "Term " + std::to_string(termCount) + 
                                 ", the operand " + 
                                 std::to_string(previousNodeCount + 1) +
                                 " is removed from the stack" << std::endl;
                        }
                        execution_stack.push(true);
                        if(DEBUG)
                        {
                            std::cout << "Term " + std::to_string(termCount) + 
                                 ", the result is meaningless"  << std::endl;
                        }
                    }
                }
                else if(previousNodeCount == 2)
                {
                    // stack stores the operands in reverse order
                    std::variant<T,bool> operand2 = execution_stack.top();
                    execution_stack.pop();
                    std::variant<T,bool> operand1 = execution_stack.top();
                    execution_stack.pop();
                    if(DEBUG)
                    {
                        std::cout << "Term " + std::to_string(termCount) + 
                             ", the operand 1 is " + (
                             std::holds_alternative<bool>(operand1) ? 
                             "undecidable" : 
                             std::to_string(std::get<T>(operand1)))
                             << std::endl;
                        std::cout << "Term " + std::to_string(termCount) + 
                             ", the operand 2 is " + (
                             std::holds_alternative<bool>(operand2) ? 
                             "undecidable" : 
                             std::to_string(std::get<T>(operand2)))
                             << std::endl;
                    }
                    if(std::holds_alternative<T>(operand2) && 
                       operationType == lab2::OperationType::DIVISION &&
                       std::get<T>(operand2) == 0)
                    {
                        this->executionErrors.push_back("Term " 
                             + std::to_string(termCount) +
                             ": Division by 0 encountered.");
                        execution_stack.push(true);
                        if(DEBUG)
                        {
                            std::cout << "Term " + std::to_string(termCount) + 
                                 ", the result is meaningless" << std::endl;
                        }
                    }
                    else if(std::holds_alternative<bool>(operand1) || 
                            std::holds_alternative<bool>(operand2))
                    {
                        execution_stack.push(true);
                        if(DEBUG)
                        {
                            std::cout << "Term " + std::to_string(termCount) + 
                                 ", the result is undecidable" << std::endl;
                        }
                    }
                    else
                    {
                        T result;
                        if(operationType == lab2::OperationType::ADDITION)
                        {
                            result = std::get<T>(operand1) + 
                                     std::get<T>(operand2);
                        }
                        if(operationType == lab2::OperationType::SUBTRACTION)
                        {
                            result = std::get<T>(operand1) -
                                     std::get<T>(operand2);
                        }
                        if(operationType == lab2::OperationType::MULTIPLICATION)
                        {
                            result = std::get<T>(operand1) * 
                                     std::get<T>(operand2);
                        }
                        if(operationType == lab2::OperationType::DIVISION)
                        {
                            result = std::get<T>(operand1) / 
                                     std::get<T>(operand2);
                        }
                        execution_stack.push(result);
                        if(DEBUG)
                        {
                            std::cout << "Term " + std::to_string(termCount) + 
                                 ", the result is " + 
                                 std::to_string(result) << std::endl;
                        }
                    }
                }
                if(current->next() != nullptr)
                {
                    while(current->next() != nullptr)
                    {   
                        termCount += 1;
                        ++current;
                        this->executionErrors.push_back("Term " + 
                             std::to_string(termCount) + 
                             " comes after an operator, and thus is ignored");
                        if(DEBUG)
                        {
                            std::cout << "~~~~~~" << std::endl;
                            std::cout << "Term " + std::to_string(termCount) + 
                                 ", the value is ignored" << std::endl;
                        }
                    }
                }
            }
        }
        if(DEBUG)
            std::cout << "~~~~~~" << std::endl;
    }
};

#endif  // LAB2_EXPRESSION_H_
