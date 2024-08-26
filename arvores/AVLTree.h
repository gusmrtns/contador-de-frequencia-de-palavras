#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <cstring>
#include "AVLNode.h"

class AVLTree
{
private:
    AVLNode<std::string, int> *m_root;

public:
    AVLTree();
    ~AVLTree();
    void insert(std::string word);
    void remove(std::string word);
    AVLNode<std::string, int> *search(std::string word);

private:
    int compare(const std::string &str) const;
    void clear(AVLNode<std::string, int> *node);
    int height(AVLNode<std::string, int> *node);
    int balance(AVLNode<std::string, int> *node);
    AVLNode<std::string, int> *right_rotate(AVLNode<std::string, int> *node);
    AVLNode<std::string, int> *left_rotate(AVLNode<std::string, int> *node);
    AVLNode<std::string, int> *double_right_rotate(AVLNode<std::string, int> *node);
    AVLNode<std::string, int> *double_left_rotate(AVLNode<std::string, int> *node);
    AVLNode<std::string, int> *insert(AVLNode<std::string, int> *node, std::string word, int freq = 1);
    AVLNode<std::string, int> *fixup_insert(AVLNode<std::string, int> *node, std::string word);
    AVLNode<std::string, int> *remove(AVLNode<std::string, int> *node, std::string word);
    AVLNode<std::string, int> *remove_successor(AVLNode<std::string, int> *root, AVLNode<std::string, int> *node);
    AVLNode<std::string, int> *fixup_remove(AVLNode<std::string, int> *node);
};

// Funções públicas
AVLTree::AVLTree()
{
    m_root = nullptr;
}

AVLTree::~AVLTree()
{
    clear(m_root);
}

void AVLTree::insert(std::string word)
{
    std::cout << "Inserting: " << word << std::endl;
    m_root = insert(m_root, word);
}

void AVLTree::remove(std::string word)
{
    std::cout << "Removing: " << word << std::endl;
    m_root = remove(m_root, word);
}

AVLNode<std::string, int> *AVLTree::search(std::string word)
{
    AVLNode<std::string, int> *node = m_root;
    while (node != nullptr)
    {
        if (word < node->getWord())
        {
            node = node->left;
        }
        else if (word > node->getWord())
        {
            node = node->right;
        }
        else
        {
            return node;
        }
    }
    return nullptr;
}

// Funções privadas

void AVLTree::clear(AVLNode<std::string, int> *node)
{
    if (node != nullptr)
    {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

int AVLTree::height(AVLNode<std::string, int> *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return node->height;
}

int AVLTree::balance(AVLNode<std::string, int> *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return height(node->left) - height(node->right);
}

AVLNode<std::string, int> *AVLTree::right_rotate(AVLNode<std::string, int> *node)
{
    std::cout << "Performing right rotation on node with word: " << node->getWord() << std::endl;
    AVLNode<std::string, int> *new_root = node->left;
    node->left = new_root->right;
    new_root->right = node;

    node->height = 1 + std::max(height(node->left), height(node->right));
    new_root->height = 1 + std::max(height(new_root->left), height(new_root->right));

    return new_root;
}

AVLNode<std::string, int> *AVLTree::left_rotate(AVLNode<std::string, int> *node)
{
    std::cout << "Performing left rotation on node with word: " << node->getWord() << std::endl;
    AVLNode<std::string, int> *new_root = node->right;
    node->right = new_root->left;
    new_root->left = node;

    node->height = 1 + std::max(height(node->left), height(node->right));
    new_root->height = 1 + std::max(height(new_root->left), height(new_root->right));

    return new_root;
}

AVLNode<std::string, int> *AVLTree::double_right_rotate(AVLNode<std::string, int> *node)
{
    std::cout << "Performing double right rotation on node with word: " << node->getWord() << std::endl;
    node->left = left_rotate(node->left);
    return right_rotate(node);
}

AVLNode<std::string, int> *AVLTree::double_left_rotate(AVLNode<std::string, int> *node)
{
    std::cout << "Performing double left rotation on node with word: " << node->getWord() << std::endl;
    node->right = right_rotate(node->right);
    return left_rotate(node);
}

AVLNode<std::string, int> *AVLTree::insert(AVLNode<std::string, int> *node, std::string word, int freq)
{
    if (node == nullptr)
    {
        std::cout << "Inserting new node with word: " << word << std::endl;
        return new AVLNode<std::string, int>(word, freq);
    }

    // Usar operadores nativos de comparação de std::string
    if (word < node->getWord())
    {
        std::cout << "Going left from node with word: " << node->getWord() << std::endl;
        node->left = insert(node->left, word, freq);
    }
    else if (word > node->getWord())
    {
        std::cout << "Going right from node with word: " << node->getWord() << std::endl;
        node->right = insert(node->right, word, freq);
    }
    else
    {
        std::cout << "Incrementing frequency of node with word: " << node->getWord() << std::endl;
        node->setFrequency(node->getFrequency() + 1);
        return node;
    }

    node = fixup_insert(node, word);

    return node;
}

AVLNode<std::string, int> *AVLTree::fixup_insert(AVLNode<std::string, int> *node, std::string word)
{
    if (node == nullptr)
        return node;

    // Atualiza a altura deste node ancestral de node
    node->height = 1 + std::max(height(node->left), height(node->right));

    // Calcula o fator de balanceamento de node
    int bal = balance(node);
    std::cout << "Balancing node with word: " << node->getWord() << ", balance factor: " << bal << std::endl;

    // Verificar se `node->left` e `node->right` não são nullptr antes de acessar
    // Caso 1(a): rotação a direita
    if (bal < -1 && node->left != nullptr && word < node->left->getWord())
    {
        std::cout << "Right rotation needed at node with word: " << node->getWord() << std::endl;
        return right_rotate(node);
    }

    // Caso 1(b): rotação dupla a direita
    if (bal < -1 && node->left != nullptr && word > node->left->getWord())
    {
        std::cout << "Double right rotation needed at node with word: " << node->getWord() << std::endl;
        return double_right_rotate(node);
    }

    // Caso 2(a): rotação a esquerda
    if (bal > 1 && node->right != nullptr && word > node->right->getWord())
    {
        std::cout << "Left rotation needed at node with word: " << node->getWord() << std::endl;
        return left_rotate(node);
    }

    // Caso 2(b): rotação dupla a esquerda
    if (bal > 1 && node->right != nullptr && word < node->right->getWord())
    {
        std::cout << "Double left rotation needed at node with word: " << node->getWord() << std::endl;
        return double_left_rotate(node);
    }

    return node;
}

AVLNode<std::string, int> *AVLTree::remove(AVLNode<std::string, int> *node, std::string word)
{
    if (node == nullptr)
    {
        return node;
    }

    if (strcmp(word.c_str(), node->getWord().c_str()) < 0)
    {
        node->left = remove(node->left, word);
    }
    else if (strcmp(word.c_str(), node->getWord().c_str()) > 0)
    {
        node->right = remove(node->right, word);
    }
    else
    {
        if (node->left == nullptr || node->right == nullptr)
        {
            AVLNode<std::string, int> *temp = node->left ? node->left : node->right;

            if (temp == nullptr)
            {
                temp = node;
                node = nullptr;
            }
            else
            {
                *node = *temp;
            }
            delete temp;
        }
        else
        {
            AVLNode<std::string, int> *temp = remove_successor(node->right, node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->getWord());
        }
    }

    if (node == nullptr)
    {
        return node;
    }

    node = fixup_remove(node);

    return node;
}

AVLNode<std::string, int> *AVLTree::remove_successor(AVLNode<std::string, int> *root, AVLNode<std::string, int> *node)
{
    if (node->left != nullptr)
    {
        node->left = remove_successor(root, node->left);
        return node;
    }

    root->data = node->data;
    root = fixup_remove(root);
    return node->right;
}

AVLNode<std::string, int> *AVLTree::fixup_remove(AVLNode<std::string, int> *node)
{
    if (node == nullptr)
        return node;

    node->height = 1 + std::max(height(node->left), height(node->right));

    int bal = balance(node);

    if (bal > 1 && balance(node->left) >= 0)
        return right_rotate(node);

    if (bal > 1 && balance(node->left) < 0)
        return double_right_rotate(node);

    if (bal < -1 && balance(node->right) <= 0)
        return left_rotate(node);

    if (bal < -1 && balance(node->right) > 0)
        return double_left_rotate(node);

    return node;
}

#endif // AVLTREE_H
