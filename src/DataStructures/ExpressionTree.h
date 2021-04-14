//
// Created by eduardo218 on 4/13/21.
//

#ifndef C__SERVER_EXPRESSIONTREE_H
#define C__SERVER_EXPRESSIONTREE_H

// C++ program for expression tree
#include<bits/stdc++.h>
#include <ostream>
#include "Stack.h"

using namespace std;

// An expression tree node
template<typename T>
class TreeNode {
    char value;
public:
    friend ostream &operator<<(ostream &os, const TreeNode &node) {
        os << "value: " << node.value << " left: " << node.left << " right: " << node.right;
        return os;
    }

    char getValue() const {
        return value;
    }

    void setValue(char value) {
        TreeNode::value = value;
    }

    TreeNode<T> *getLeft() const {
        return left;
    }

    void setLeft(TreeNode<T> *left) {
        TreeNode::left = left;
    }

    TreeNode<T> *getRight() const {
        return right;
    }

    void setRight(TreeNode<T> *right) {
        TreeNode::right = right;
    }


private:
    TreeNode<T> *left, *right;
};

template<typename T>
class ExpresionTree {
private:
    LinkedList<char> *operators = new LinkedList<char>();
    TreeNode<T> *root;
public:
    bool isOperator(char c) {
        return c == '+';
    }

    void inorder(TreeNode<T> *t) {
        if (t) {
            inorder(t->getLeft());
            printf("%c ", t->getValue());
            inorder(t->getRight());
        }
    }

    void inorder() {
        this->inorder(this->root);
    }

    friend ostream &operator<<(ostream &os, const ExpresionTree &tree) {
        os << "root: " << tree.root;
        return os;
    }

    void create(const string &expression) {
        auto *stack = new Stack<TreeNode<T> *>();
        for (char c : expression) {
            auto *node = new TreeNode<T>();
            if (isOperator(c)) {
                node->setValue(c);
                TreeNode<T> *leftChild, *rightChild;

                node->setLeft(stack->peek());
                stack->pop();
                node->setRight(stack->peek());
                stack->pop();

                stack->push(node);
                stack->show();
            } else {
                node->setValue(c);
                stack->push(node);
            }
        }
        this->root = stack->peek();
    }

};

#endif //C__SERVER_EXPRESSIONTREE_H
