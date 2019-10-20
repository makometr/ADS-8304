#ifndef LAB2_TRIVARIATEHIERARCHICALLIST_H_
#define LAB2_TRIVARIATEHIERARCHICALLIST_H_

#include <variant>
#include <stack>

#include "utils.h"

namespace lab2
{
    // TrivariateHierarchicalList class was designed to store either a value of
    // one out of three distinct types, or a pointer to a sublist 
    template<class T, class U, class V>
    class TrivariateHierarchicalList
    {
    protected:
        class Node;
    private:
        class Iterator;

    public:
        explicit TrivariateHierarchicalList()
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
            return Iterator(nullptr);
        }
        
    protected:
        Node* head()
        {
            return this->head_;
        }
        
    private:
        Node* head_ = nullptr;
        
    protected:
        // The nested class Node was designed to be a single node of a 
        // trivariate hierarchical list
        class Node
        {
        public:
            explicit Node()
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
                            lab2::to_string(std::get<T>(current->content_));
                    else if(std::holds_alternative<U>(current->content_))
                        representation +=
                            lab2::to_string(std::get<U>(current->content_));
                    else if(std::holds_alternative<V>(current->content_))
                        representation +=
                            lab2::to_string(std::get<V>(current->content_));
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
        
    private:
        // The nested class Iterator was designed to facilitate iteration
        // through a hierarchical list using explicit stack manipulations
        class Iterator
        {
        public:
            using difference_type = std::ptrdiff_t;
            using value_type = Node;
            using pointer = Node*;
            using reference = Node&;
            using iterator_category = std::forward_iterator_tag;
            
            explicit Iterator(Node *node)
            {
                this->current = node;
                this->previousNodeCountStack.push(0);
                this->normalizePosition();
            }
            
            Iterator& operator++()
            {
                if(this->current == nullptr)
                    return *this;
                this->current = this->current->next();
                previousNodeCountStack.top() += 1;
                this->normalizePosition();
                return *this;
            }
            
            Iterator operator++(int)
            {
                auto old = *this;
                ++(*this);
                return old;
            }
            
            reference operator *()
            {
                return *(this->current); 
            }
            
            pointer operator ->()
            {
                return &**this;
            }
            
            bool operator ==(const Iterator& that)
            {
                return this->current == that.current && 
                       this->nodeStack == that.nodeStack;
            }
            
            bool operator !=(const Iterator& that)
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
            
            // ensures that this->current holds a pointer to an atomic node,
            // or is equal to nullptr if there is no atomic nodes left
            void normalizePosition()
            {
                while((this->current == nullptr && this->nodeStack.size() > 0) ||
                      (this->current != nullptr && 
                      std::holds_alternative<Node*>(this->current->content()) &&
                      std::get<Node*>(this->current->content()) != nullptr))
                {
                    while(this->current == nullptr && this->nodeStack.size() > 0)
                    {
                        this->current = this->nodeStack.top()->next();
                        this->nodeStack.pop();
                        this->previousNodeCountStack.pop();
                    }
                    while(this->current != nullptr &&
                          std::holds_alternative<Node*>(this->current->content()) &&
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
    };
}
#endif  // LAB2_TRIVARIATEHIERARCHICALLIST_H_
