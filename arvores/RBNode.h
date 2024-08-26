#ifndef RBNODE_H
#define RBNODE_H

#define RED false
#define BLACK true

#include <iostream>

template <typename Word, typename Frequency>
struct Node
{
    Word word;
    Frequency freq;
    bool color;
    Node *parent;
    Node *left;
    Node *right;

    Node(int key, bool color, Node *parent, Node *left, Node *right)
    {
        this->key = key;
        this->color = color;
        this->parent = parent;
        this->left = left;
        this->right = right;
    }
};

#endif