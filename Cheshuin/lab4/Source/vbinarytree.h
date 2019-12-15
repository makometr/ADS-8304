#ifndef VBINARYTREE_H
#define VBINARYTREE_H
#include <stack>

template<typename T>
class VBinaryTree
{
private:
    struct Node
    {
        int parent_ = -1;
        int left_ = -1;
        int right_ = -1;
        bool isEmpty = true;
        T value_;
    };

private:
    Node* memory_ = nullptr;
    int maxSize_ = 10;
    int size_ = 1;

    std::stack<unsigned> freePoses_;
    int curPos_ = 0;
public:
    VBinaryTree();
    ~VBinaryTree();
    VBinaryTree(const VBinaryTree<T>& BT);
    VBinaryTree<T>& operator=(VBinaryTree<T>& BT);

    void setValue(T value);
    T getValue() const;
    size_t size() const;

    int toLeft();
    int toRight();
    int toParent();
    void toPos(int pos);

    int left() const;
    int right() const;
    int current() const;
    int parent() const;
    bool isEmpty() const;

    int addLeft();
    int addRight();
};
template<typename T>
VBinaryTree<T>::VBinaryTree()
{
    curPos_ = 0;
    memory_ = new Node[maxSize_];

    for(int i = 9; i > 0; i--)
    {
        freePoses_.push(i);
    }
}

template<typename T>
VBinaryTree<T>::~VBinaryTree()
{
    delete[] memory_;
}

template<typename T>
VBinaryTree<T>::VBinaryTree(const VBinaryTree<T>& BT)
{
    curPos_ = 0;
    maxSize_ = BT.maxSize_;
    memory_ = new Node[maxSize_];

    for(int i = 0; i < maxSize_; i++)
    {
        memory_[i] = BT.memory_[i];
    }

    freePoses_ = BT.freePoses_;
}

template<typename T>
VBinaryTree<T>& VBinaryTree<T>::operator=(VBinaryTree<T>& BT)
{

    curPos_ = BT.curPos_;
    maxSize_ = BT.maxSize_;

    if(memory_ != nullptr)
    {
        delete memory_;
    }
    memory_ = new Node[maxSize_];

    for(int i = 0; i < maxSize_; i++)
    {
        memory_[i] = BT.memory_[i];
    }

    freePoses_ = BT.freePoses_;

    return this;
}

template<typename T>
void VBinaryTree<T>::setValue(T value)
{
    memory_[curPos_].value_ = value;
    memory_[curPos_].isEmpty = false;
}

template<typename T>
T VBinaryTree<T>::getValue() const
{
    return memory_[curPos_].value_;
}

template<typename T>
int VBinaryTree<T>::toLeft()
{
    curPos_ = memory_[curPos_].left_;

    return curPos_;
}

template<typename T>
int VBinaryTree<T>::toRight()
{
    curPos_ = memory_[curPos_].right_;

    return curPos_;
}

template<typename T>
int VBinaryTree<T>::toParent()
{
    curPos_ = memory_[curPos_].parent_;

    return curPos_;
}

template<typename T>
void VBinaryTree<T>::toPos(int pos)
{
    curPos_ = pos;
}

template<typename T>
size_t VBinaryTree<T>::size() const
{
    return size_;
}

template<typename T>
int VBinaryTree<T>::left() const
{
    return memory_[curPos_].left_;
}

template<typename T>
int VBinaryTree<T>::right() const
{
    return memory_[curPos_].right_;
}

template<typename T>
int VBinaryTree<T>::parent() const
{
    return memory_[curPos_].parent_;
}

template<typename T>
int VBinaryTree<T>::current() const
{
    return curPos_;
}

template<typename T>
bool VBinaryTree<T>::isEmpty() const
{
    return memory_[curPos_].isEmpty;
}

template<typename T>
int VBinaryTree<T>::addLeft()
{
    size_ += 1;

    if(freePoses_.empty())
    {
        Node* buf = memory_;
        memory_ = new Node[maxSize_ * 2];

        for(int i = 0; i < maxSize_; i++)
        {
            memory_[i] = buf[i];
        }

        delete buf;

        maxSize_ = maxSize_ * 2;
        for(int i = maxSize_ * 2 - 1 ; i > maxSize_; i--)
        {
            freePoses_.push(i);
        }

        maxSize_ = maxSize_ * 2;
    }

    int buf = curPos_;
    int parent = buf;
    while(memory_[curPos_].left_ != -1)
    {
        parent = toLeft();
    }

    int newNode = freePoses_.top();
    freePoses_.pop();
    memory_[curPos_].left_ = newNode;
    memory_[newNode].parent_ = parent;

    curPos_ = buf;

    return newNode;
}

template<typename T>
int VBinaryTree<T>::addRight()
{
    size_ += 1;

    if(freePoses_.empty())
    {
        Node* buf = memory_;
        memory_ = new Node[maxSize_ * 2];

        for(int i = 0; i < maxSize_; i++)
        {
            memory_[i] = buf[i];
        }

        delete buf;

        maxSize_ = maxSize_ * 2;
        for(int i = maxSize_ * 2 - 1 ; i > maxSize_; i--)
        {
            freePoses_.push(i);
        }

        maxSize_ = maxSize_ * 2;
    }

    int buf = curPos_;
    int parent = buf;
    while(memory_[curPos_].right_ != -1)
    {
        parent = toRight();
    }

    int newNode = freePoses_.top();
    freePoses_.pop();
    memory_[curPos_].right_ = newNode;
    memory_[newNode].parent_ = parent;

    curPos_ = buf;

    return newNode;
}

#endif // VBINARYTREE_H
