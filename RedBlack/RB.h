#pragma once
#include <iostream>
using namespace std;

enum RB_Type : bool { RED = 1, BLACK = 0 };

enum LR_Type : bool { LEFT = 0, RIGHT = 1};

template <typename T>
struct nodeType
{
    T info;
    nodeType<T>* link[2];
    RB_Type color;
};

template <typename T>
class BinaryTreeType
{
protected:
    nodeType<T> *root;
public:
    BinaryTreeType();
    ~BinaryTreeType();
    bool isEmpty() const;
    virtual void insert(const T& item) = 0;
    virtual void deleteNode(const T& item) = 0;
    virtual bool search(const T& item) = 0;
    void inOrderTraversal() const;
    void preOrderTraversal() const;
    void postOrderTraversal() const;
private:
    void inOrder(nodeType<T>* p) const;
    void preOrder(nodeType<T>* p) const;
    void postOrder(nodeType<T>* p) const;
    void destroy(nodeType<T>*& p);
    bool isRed(const nodeType<T>* p) const;
};

template <typename T>
class RBT : public BinaryTreeType<T>
{
public:
    void insert(const T& item);
    void deleteNode(const T& item);
    bool search(const T& item);
private:
    void deleteFromTree(nodeType<T> * &p);
};

template <typename T>
void RBT<T>::deleteNode(const T& item)
{
    nodeType<T> *curr;
    nodeType<T> *trail;
    bool found = false;

    if (root == nullptr)
        return;
    trail = curr = root;
    while (curr != nullptr)
    {
        if (curr->info == item)
        {
            found = true;
            break;
        }
        else
        {
            trail = curr;
            curr = curr->link[item > curr->info];
        }
    }
    if (found)
    {
        if (curr == root)
            deleteFromTree(root);
        else
            deleteFromTree(trail->link[trail > curr->info]);
    }
}

template<typename T>
bool RBT<T>::search(const T& item)
{
    nodeType<T> *curr = root;
    if (root == nullptr)
        return;
    curr = root;
    while (curr != nullptr)
    {
        if (curr->info == item)
            return true;
        else
            curr = curr->link[item > curr->info];
    }
    return false;
}

template <typename T>
void RBT<T>::deleteFromTree(nodeType<T> * &p)
{
    nodeType<T> *curr;
    nodeType<T> *trail;
    nodeType<T> *temp;

    if (p == nullptr)
        return;

    // if both children are null
    else if (p->link[LEFT] == nullptr && p->link[RIGHT] == nullptr)
    {
        temp = p;
        p = nullptr;
        delete temp;
    }

    // if only the left child is null
    else if (p->link[LEFT] == nullptr)
    {
        temp = p;
        p = temp->link[RIGHT];
        delete temp;
    }

    // if only the right child is null
    else if (p->link[RIGHT] == nullptr)
    {
        temp = p;
        p = temp->link[LEFT];
        delete temp;
    }

    // if neither child is null, swap with maximum value in left subtree
    else
    {
        curr = p->link[LEFT];
        trail = nullptr;
        while (curr->link[RIGHT] != nullptr)
        {
            trail = curr;
            curr = curr->link[RIGHT];
        }
        p->info = curr->info;
        // curr did not move
        if (trail == nullptr)
            p->link[LEFT] = curr->link[LEFT];
        else
            trail->link[RIGHT] = curr->link[LEFT];
        delete curr;
    }
}

template <typename T>
void RBT<T>::insert(const T& item)
{
    nodeType<T> *newNode;
    nodeType<T> *curr;
    nodeType<T> *parent;

    newNode = new nodeType<T>;
    newNode->info = item;
    newNode->link[LEFT] = nullptr;
    newNode->link[RIGHT] = nullptr;

    if (root == nullptr)
    {
        newNode->color = BLACK;
        root = newNode;
    }
    else
    {
        newNode->color = RED;
        parent = curr = root;
        while (curr != nullptr)
        {
            parent = curr;
            if (curr->info == item)
            {
                delete newNode;
                return;
            }
            curr = curr->link[item > curr->info];
        }
        parent->link[item > parent->info] = newNode;
    }
    // new node's parent is BLACK -> all's well, we're done
    if (parent->color == BLACK)
        return;

    // new node's parent is RED -> red violation
    if (parent->color == RED)
    {
        // make a plan summary of the rules and procedure
        // may need to use recursion
    }

}

template <typename T>
BinaryTreeType<T>::~BinaryTreeType()
{
    destroy(root);
}

template <typename T>
void BinaryTreeType<T>::destroy(nodeType<T> * &p)
{
    if (p == nullptr)
        return;
    destroy(p->link[LEFT]);
    destroy(p->link[RIGHT]);
    delete p;
    p = nullptr;
}

template<typename T>
bool BinaryTreeType<T>::isRed(const nodeType<T>* p) const
{
    return (p != nullptr && p->color == RED);
}

template <typename T>
void BinaryTreeType<T>::postOrderTraversal() const
{
    postOrder(root);
}

template <typename T>
void BinaryTreeType<T>::postOrder(nodeType<T> *p) const
{
    if (p != nullptr)
    {
        postOrder(p->link[LEFT]);
        postOrder(p->link[RIGHT]);
        cout << p->info << " ";
    }
}

template <typename T>
void BinaryTreeType<T>::preOrderTraversal() const
{
    preOrder(root);
}

template <typename T>
void BinaryTreeType<T>::preOrder(nodeType<T> *p) const
{
    if (p != nullptr)
    {
        cout << p->info << " ";
        preOrder(p->link[LEFT]);
        preOrder(p->link[RIGHT]);
    }
}

template <typename T>
void BinaryTreeType<T>::inOrderTraversal() const
{
    inOrder(root);
}

template <typename T>
void BinaryTreeType<T>::inOrder(nodeType<T> *p) const
{
    if (p != nullptr)
    {
        inOrder(p->link[LEFT]);
        cout << p->info << " ";
        inOrder(p->link[RIGHT]);
    }
}

template <typename T>
BinaryTreeType<T>::BinaryTreeType()
{
    root = nullptr;
}

template <typename T>
bool BinaryTreeType<T>::isEmpty() const
{
    return (root == nullptr);
}
