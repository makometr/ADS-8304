#ifndef LAB2_EXPRESSION_H_
#define LAB2_EXPRESSION_H_

#include <iostream>
#include <vector>
#include <regex>

#include "trivariatehierarchicallist.h"

constexpr bool DEBUG = true;

namespace lab2
{
    template<class T>
    class Expression
    : public lab2::TrivariateHierarchicalList<T, std::string, lab2::OperationType>
    {
        typedef typename \
            lab2::TrivariateHierarchicalList<T, std::string, lab2::OperationType>::Node \
            ExpressionNode;

    public:
        Expression(const std::string &expression) 
        : lab2::TrivariateHierarchicalList<T, std::string, lab2::OperationType>()
        {
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
            std::stack<std::variant<T,bool>> executionStack;
            executionErrors.resize(0);
            this->checkNodes(executionStack);
            if(executionStack.size() > 1)
                this->executionErrors.push_back(std::string("There ") + 
                     (executionStack.size() > 2 ? "are " : "is ") + 
                     lab2::to_string(executionStack.size() - 1) + 
                     " unused operand" + (executionStack.size() > 2 ? "s " : 
                     " ") +  "left");
            if(this->parsingErrors.size() > 0 || this->executionErrors.size() > 0)
                return false;
            return true;
        }

        std::string getErrors()
        {   
            bool expressionIsCorrect = this->parsingErrors.size() == 0 && 
                 !(this->executionErrors.size() > 0 || this->isCorrect());
            if(expressionIsCorrect)
                return("There are no errors found.\n");
                
            auto totalLength = 0;
            for(auto error : this->parsingErrors)
                totalLength += error.length() + 1;
            for(auto error : this->executionErrors)
                totalLength += error.length() + 1;
                
            std::string result;
            result.reserve(totalLength + 9);
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
            
            // ensure that the (sub)expression being parsed starts with "("
            if(current != end && *current == '(')
            { 
                if(depth == 1 && DEBUG)
                    std::cout << std::string(depth - 1, ' ') << 
                         "| the token \"(\" was acquired: " << std::endl;
                current += 1;
                while(current != end)
                {
                    // skip spaces
                    while(current != end && *current == ' ')
                    {
                        current += 1;
                    }
                    
                    if(current == end)
                    {
                        this->parsingErrors.push_back("(Sub)expression ended unexpectedly");
                        return end;
                    }

                    // get "(" => parse subexpression
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
                    
                    // get ")" => stop parsing (sub)expression
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
                            this->parsingErrors.push_back("The provided "\
                                 "expression contains empty parentheses");
                        }
                        current += 1;
                        break;
                    }

                    // get a variable
                    else if(('A' <= *current && *current <= 'Z') ||
                                                *current == '_' ||
                            ('a' <= *current && *current <= 'z'))
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
                                 "\" was acquired" << std::endl;
                        }
                        current += match[1].length();
                    }
                    
                    // get a number
                    // fractions of the pattern ".[0-9]+" are not supported
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
                                 "\" was acquired" << std::endl;
                        }
                        current += match[1].length();
                    }
                    
                    // get an operator
                    else if(*current == '+' || *current == '-' || *current == '*' || 
                            *current == '/')
                    {
                        if(*current == '+')
                            currentNode->setContent(lab2::OperationType::ADDITION);
                        else if(*current == '-')
                            currentNode->setContent(lab2::OperationType::SUBTRACTION);
                        else if(*current == '*')
                            currentNode->setContent(lab2::OperationType::MULTIPLICATION);
                        else if(*current == '/')
                            currentNode->setContent(lab2::OperationType::DIVISION);
                        current += 1;
                        if(DEBUG)
                        {
                            std::cout << std::string(depth - 1, ' ') << 
                                 "| the token  \"" << lab2::to_string(std::get<\
                                 lab2::OperationType>(currentNode->content())) << 
                                 "\" was acquired" << std::endl;
                        }
                    }
                    
                    // ignore other symbols
                    else
                    {
                        this->parsingErrors.push_back("Unexpected symbol: \"" +
                                                       std::string(1, *current) 
                                                       + "\"");
                        current += 1;
                        continue;
                    }

                    if(current != end && *current != ')')
                    {
                        currentNode->setNext(new ExpressionNode());
                        currentNode = currentNode->next();
                    }
                }
                // ensure that all parentheses are closed
                if(*(current - 1) != ')')
                {
                    this->parsingErrors.push_back("(Sub)expression ended unexpectedly");
                }
            }
            else
            {
                this->parsingErrors.push_back("The symbol \"(\" is abscent"
                     "where it is required");
            }
            
            depth -= 1;
            if(depth == 0)
            {
                // report a presence of a character after the last closing bracket
                if(current != end)
                {
                    auto unexpectedSymbols = std::string(current, end);
                    this->parsingErrors.push_back(std::string("The string ") +
                         "contains the following unexpected character" + 
                         (unexpectedSymbols.length() > 2 ? "s " : " ") + 
                         "at the end:\n\t\"" + unexpectedSymbols + "\"");
                }
            }
            if(DEBUG)
            {
                std::cout << std::string(depth, ' ') << "|~~~~~~~~~~~" << std::endl;
                if(depth > 0)
                    std::cout << std::string(depth - 1, ' ') << "| depth: " << 
                         depth << std::endl;
            }
            return current;
        }

        // tries to compute the value of the stored expression in order to find
        // all cases of division by 0
        // "bool" represents an undecidable variable
        void checkNodes(std::stack<std::variant<T,bool>>& executionStack)
        {
            size_t termCount = 1;
            for(auto current = this->begin(), end = this->end(); 
                current != end; termCount += 1, ++current)
            {
                // push a number onto the stack
                if(std::holds_alternative<T>(current->content()))
                {
                    executionStack.push(std::get<T>(current->content()));
                    if(DEBUG)
                    {
                        std::cout << "~~~~~~" << std::endl;
                        std::cout << "Term " + lab2::to_string(termCount) + 
                             ", the value is " 
                             << std::get<T>(current->content()) 
                             << std::endl;
                    }
                }
                // push an unknown value onto the stack
                else if(std::holds_alternative<std::string>(current->content()))
                {
                    executionStack.push(true);
                    if(DEBUG)
                    {
                        std::cout << "~~~~~~" << std::endl;
                        std::cout << "Term " + lab2::to_string(termCount) + 
                             ", the value is undecidable" << std::endl;
                    }
                }
                // execute an operation
                else if(std::holds_alternative<lab2::OperationType>(current->content()))
                {
                    auto previousNodeCount = current.getPreviousNodeCount();
                    auto operationType = std::get<lab2::OperationType>(current->content());
                    if(DEBUG)
                    {
                        std::cout << "~~~~~~" << std::endl;
                        std::cout << "Term " + lab2::to_string(termCount) + 
                             ", the operation is \"" << 
                             lab2::to_string(operationType) + "\""
                             << std::endl;
                    }
                    // if the operation is called as niladic, report an error
                    if(previousNodeCount == 0)
                    {
                        this->executionErrors.push_back("Term " 
                             + lab2::to_string(termCount) + ": The operation \"" + 
                             lab2::to_string(operationType) +
                             "\" has too few (0) arguments");
                    }
                    // if the operation is called as ternary or ..., report an error
                    else if(previousNodeCount > 2)
                    {
                        this->executionErrors.push_back("Term " 
                             + lab2::to_string(termCount) + ": The operation \"" + 
                             lab2::to_string (operationType) + "\" has too many (" + 
                             lab2::to_string(previousNodeCount) + ") arguments");
                        // remove all its arguments from the stack
                        while(previousNodeCount --> 0 && executionStack.size() > 0)
                        {
                            if(DEBUG)
                            {
                                std::cout << "Term " + lab2::to_string(termCount) + 
                                     ", the operand " + 
                                     lab2::to_string(previousNodeCount + 1) +
                                     " is removed from the stack" << std::endl;
                            }
                            executionStack.pop();
                        }
                        // overflows it back to 0 in a case of an overflow
                        previousNodeCount += 1; 
                        if(previousNodeCount == 1)
                        {
                            this->executionErrors.push_back("Term " + 
                                 lab2::to_string(termCount) + 
                                 ": an empty operand was encountered during " +
                                 "execution");
                            if(DEBUG)
                            {
                                std::cout << "Term " +
                                     lab2::to_string(termCount) + 
                                     ": an empty operand was encountered during " +
                                     "execution" << std::endl;
                            }
                        }
                        else if(previousNodeCount > 0)
                        {
                            this->executionErrors.push_back("Term " + 
                                 lab2::to_string(termCount) + 
                                 ": " + lab2::to_string(previousNodeCount) + 
                                 " empty operands were encountered during " +
                                 "execution");
                            if(DEBUG)
                            {
                                std::cout << "Term " +
                                     lab2::to_string(termCount) + 
                                 ": " + lab2::to_string(previousNodeCount) + 
                                 " empty operands were encountered during " +
                                 "execution" << std::endl;
                            }
                        }
                        
                        
                        // push an unknown value onto the stack as its result
                        executionStack.push(true);
                        if(DEBUG)
                        {
                            std::cout << "Term " + lab2::to_string(termCount) + 
                                 ", the result is meaningless" << std::endl;
                        }
                    }
                    // if the operation is called as unary, ...
                    else if(previousNodeCount == 1)
                    {
                        if(executionStack.size() == 0)
                        {
                            this->executionErrors.push_back("Term " + 
                                 lab2::to_string(termCount) + 
                                 ": an empty operand was encountered during " +
                                 "execution");
                            if(DEBUG)
                            {
                                std::cout << "Term " +
                                     lab2::to_string(termCount) + 
                                     ": an empty operand was encountered during " +
                                     "execution" << std::endl;
                            }
                            return;
                        }
                        
                        // if it is "-", try to execute it
                        if(operationType == lab2::OperationType::SUBTRACTION)
                        {
                            if(std::holds_alternative<T>(executionStack.top()))
                            {
                                auto operand = std::get<T>(executionStack.top());

                                if(DEBUG)
                                {
                                    std::cout << "Term " 
                                         + lab2::to_string(termCount) + 
                                         ", the operand is " << operand 
                                         << std::endl;
                                }
                                executionStack.pop();
                                executionStack.push(-operand);
                            }
                            else
                            {
                                if(DEBUG)
                                {
                                    std::cout << "Term " 
                                         + lab2::to_string(termCount) + 
                                         ", the operand is undecidable" 
                                         << std::endl;
                                }
                                executionStack.pop();
                                executionStack.push(true);
                            }
                        }
                        // if it is not "-", report an error
                        else
                        {
                            this->executionErrors.push_back("Term " 
                                  + lab2::to_string(termCount) +
                                  ": The operation \"" +     
                                  lab2::to_string(operationType) +
                                  "\" has too few (1) arguments");
                            executionStack.pop();
                            if(DEBUG)
                            {
                                std::cout << "Term " + lab2::to_string(termCount) + 
                                     ", the operand " + 
                                     lab2::to_string(previousNodeCount + 1) +
                                     " is removed from the stack" << std::endl;
                            }
                            executionStack.push(true);
                            if(DEBUG)
                            {
                                std::cout << "Term " + lab2::to_string(termCount) + 
                                     ", the result is meaningless"  << std::endl;
                            }
                        }
                    }
                    // if the operation is called as binary, ...
                    else if(previousNodeCount == 2)
                    {
                        // retrieve the operands in reverse order
                        std::variant<T,bool> operand1, operand2;
                        if(executionStack.size() >= 2)
                        {
                            operand2 = executionStack.top();
                            executionStack.pop();
                            operand1 = executionStack.top();
                            executionStack.pop();
                        }
                        else if(executionStack.size() == 1)
                        {
                            this->executionErrors.push_back("Term " + 
                                 lab2::to_string(termCount) + 
                                 ": an empty operand was encountered during " +
                                 "execution");
                            if(DEBUG)
                            {
                                std::cout << "Term " +
                                     lab2::to_string(termCount) + 
                                     ": an empty operand was encountered during " +
                                     "execution" << std::endl;
                            }
                            return;
                        }
                        else
                        {
                            this->executionErrors.push_back("Term " +
                                 lab2::to_string(termCount) + 
                                 ": 2 empty operands were encountered during " +
                                 "execution");
                            if(DEBUG)
                            {
                                std::cout << "Term " +
                                     lab2::to_string(termCount) + 
                                     ": 2 empty operands were encountered during " +
                                     "execution" << std::endl;
                            }
                            return;
                        }
                        
                        if(DEBUG)
                        {
                            std::cout << "Term " + lab2::to_string(termCount) + 
                                 ", the operand 1 is " + (
                                 std::holds_alternative<bool>(operand1) ? 
                                 "undecidable" : 
                                 lab2::to_string(std::get<T>(operand1)))
                                 << std::endl;
                            std::cout << "Term " + lab2::to_string(termCount) + 
                                 ", the operand 2 is " + (
                                 std::holds_alternative<bool>(operand2) ? 
                                 "undecidable" : 
                                 lab2::to_string(std::get<T>(operand2)))
                                 << std::endl;
                        }
                        // check for division by 0
                        if(std::holds_alternative<T>(operand2) && 
                           operationType == lab2::OperationType::DIVISION &&
                           std::get<T>(operand2) == 0)
                        {
                            this->executionErrors.push_back("Term " 
                                 + lab2::to_string(termCount) +
                                 ": Division by 0 encountered");
                            executionStack.push(true);
                            if(DEBUG)
                            {
                                std::cout << "Term " + lab2::to_string(termCount) + 
                                     ", the result is meaningless" << std::endl;
                            }
                        }
                        // check for undecidable operands
                        else if(std::holds_alternative<bool>(operand1) || 
                                std::holds_alternative<bool>(operand2))
                        {
                            executionStack.push(true);
                            if(DEBUG)
                            {
                                std::cout << "Term " + lab2::to_string(termCount) + 
                                     ", the result is undecidable" << std::endl;
                            }
                        }
                        // if neither division by 0 nor undecidable operands were
                        // encountered, execute the operation and save its result
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
                            executionStack.push(result);
                            if(DEBUG)
                            {
                                std::cout << "Term " + lab2::to_string(termCount) + 
                                     ", the result is " + 
                                     lab2::to_string(result) << std::endl;
                            }
                        }
                    }
                    // ignore operands that oppear after an operator
                    if(current->next() != nullptr)
                    {
                        while(current->next() != nullptr)
                        {   
                            termCount += 1;
                            ++current;
                            this->executionErrors.push_back("Term " + 
                                 lab2::to_string(termCount) + 
                                 " comes after an operator, and thus is ignored");
                            if(DEBUG)
                            {
                                std::cout << "~~~~~~" << std::endl;
                                std::cout << "Term " + lab2::to_string(termCount) + 
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
}

#endif  // LAB2_EXPRESSION_H_
