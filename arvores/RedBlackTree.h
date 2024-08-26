#ifndef RBTREE_H
#define RBTREE_H
#include <iostream>
#include "RBNode.h"

class RedBlackTree
{
private:
    Node *m_root;
    Node *m_nil;

public:
    RedBlackTree();
    ~RedBlackTree();
    void insert(int value);
    void remove(int value);
    Node *minimum(Node *n);

private:
    void insert_fixup(Node *novo);
    void left_rotate(Node *novo);
    void right_rotate(Node *novo);
    void RB_delete(Node *toDelete);
    void RB_delete_fixup(Node *x);
};

RedBlackTree::RedBlackTree()
{
    m_nil = new Node(0, BLACK, nullptr, nullptr, nullptr);
    m_nil->left = m_nil;
    m_nil->right = m_nil;
    m_nil->parent = m_nil;
    m_root = m_nil;
}

RedBlackTree::~RedBlackTree()
{
    delete m_nil;
}

void RedBlackTree::insert(int value)
{
    Node *atual = m_root;
    Node *pai_do_atual = m_nil;
    while (atual != m_nil)
    {
        pai_do_atual = atual;
        if (value < atual->key)
        {
            atual = atual->left;
        }
        else if (value > atual->key)
        {
            atual = atual->right;
        }
        else
        {
            return;
        }
    }

    Node *novo = new Node(value, RED, pai_do_atual, m_nil, m_nil);

    if (pai_do_atual == m_nil)
    {
        m_root = novo;
    }
    else if (value < pai_do_atual->key)
    {
        pai_do_atual->left = novo;
    }
    else
    {
        pai_do_atual->right = novo;
    }
    insert_fixup(novo);
}

void RedBlackTree::insert_fixup(Node *novo)
{
    // enquanto o pai do novo nó for vermelho
    while (novo->parent->color == RED)
    {
        // se o pai do novo nó for filho esquerdo
        if (novo->parent == novo->parent->parent->left)
        {
            // tio do novo nó está à direita
            Node *tio = novo->parent->parent->right;
            // se o tio do novo nó for vermelho
            if (tio->color == RED)
            {
                novo->parent->color = BLACK;       // caso 1
                tio->color = BLACK;                // caso 1
                novo->parent->parent->color = RED; // caso 1
                novo = novo->parent->parent;
            }
            else
            {
                // se o novo nó for filho direito
                if (novo == novo->parent->right)
                {
                    novo = novo->parent; // caso 2
                    // rotaciona à esquerda
                    left_rotate(novo);
                }
                novo->parent->color = BLACK;       // caso 3
                novo->parent->parent->color = RED; // caso 3
                // rotaciona à direita
                right_rotate(novo->parent->parent);
            }
        }
        else
        {
            // tio do novo nó está à esquerda
            Node *tio = novo->parent->parent->left;
            // se o tio do novo nó for vermelho
            if (tio->color == RED)
            {
                novo->parent->color = BLACK;       // caso 1
                tio->color = BLACK;                // caso 1
                novo->parent->parent->color = RED; // caso 1
                novo = novo->parent->parent;
            }
            else
            {
                // se o novo nó for filho esquerdo
                if (novo == novo->parent->left)
                {
                    novo = novo->parent; // caso 2
                    // rotaciona à direita
                    right_rotate(novo);
                }
                novo->parent->color = BLACK;       // caso 3
                novo->parent->parent->color = RED; // caso 3
                // rotaciona à esquerda
                left_rotate(novo->parent->parent);
            }
        }
    }
    m_root->color = BLACK;
}

void RedBlackTree::remove(int value)
{
    Node *atual = m_root;
    while (atual != m_nil && atual->key != value)
    {
        if (value < atual->key)
        {
            atual = atual->left;
        }
        else if (value > atual->key)
        {
            atual = atual->right;
        }
    }
    if (atual != m_nil)
    {
        RB_delete(atual);
    }
}

void RedBlackTree::RB_delete(Node *toDelete)
{
    Node *y;                                                 // nó que será removido
    Node *x;                                                 // nó que substituirá y
    if (toDelete->left == m_nil || toDelete->right == m_nil) // se toDelete tem no máximo um filho
        y = toDelete;                                        // y é o próprio toDelete
    else                                                     // se toDelete tem dois filhos
        y = minimum(toDelete->right);                        // y é o sucessor de toDelete

    if (y->left != m_nil) // se y tem um filho à esquerda
        x = y->left;      // x é o filho à esquerda de y
    else
        x = y->right; // x é o filho à direita de y

    x->parent = y->parent; // o pai de x é o pai de y

    if (y->parent == m_nil)        // se y é a raiz
        m_root = x;                // x é a nova raiz
    else if (y == y->parent->left) // se y é filho esquerdo
        y->parent->left = x;       // x é o novo filho esquerdo
    else
        y->parent->right = x; // x é o novo filho direito

    if (y != toDelete)          // se y é diferente de toDelete
        toDelete->key = y->key; // copia a chave de y para toDelete

    if (y->color == BLACK)  // se a cor de y é preta
        RB_delete_fixup(x); // chama o método de correção
    delete y;               // libera a memória de y
}

void RedBlackTree::RB_delete_fixup(Node *x)
{
    while (x != m_root && x->color == BLACK)
    {
        if (x == x->parent->left)
        {
            Node *w = x->parent->right;
            if (w->color == RED)
            {
                w->color = BLACK;       // caso 1
                x->parent->color = RED; // caso 1
                left_rotate(x->parent); // caso 1
                w = x->parent->right;   // caso 1
            }
            if (w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED; // caso 2
                x = x->parent;  // caso 2
            }
            else
            {
                if (w->right->color == BLACK)
                {
                    w->left->color = BLACK; // caso 3
                    w->color = RED;         // caso 3
                    right_rotate(w);        // caso 3
                    w = x->parent->right;   // caso 3
                }
                w->color = x->parent->color; // caso 4
                x->parent->color = BLACK;    // caso 4
                w->right->color = BLACK;     // caso 4
                left_rotate(x->parent);      // caso 4
                x = m_root;                  // caso 4
            }
        }
        else
        {
            Node *w = x->parent->left;
            if (w->color == RED)
            {
                w->color = BLACK;        // caso 1
                x->parent->color = RED;  // caso 1
                right_rotate(x->parent); // caso 1
                w = x->parent->left;     // caso 1
            }
            if (w->right->color == BLACK && w->left->color == BLACK)
            {
                w->color = RED; // caso 2
                x = x->parent;  // caso 2
            }
            else
            {
                if (w->left->color == BLACK)
                {
                    w->right->color = BLACK; // caso 3
                    w->color = RED;          // caso 3
                    left_rotate(w);          // caso 3
                    w = x->parent->left;     // caso 3
                }
                w->color = x->parent->color; // caso 4
                x->parent->color = BLACK;    // caso 4
                w->left->color = BLACK;      // caso 4
                right_rotate(x->parent);     // caso 4
                x = m_root;                  // caso 4
            }
        }
    }
}

void RedBlackTree::left_rotate(Node *novo)
{
    Node *y = novo->right;
    novo->right = y->left;
    if (y->left != m_nil)
    {
        y->left->parent = novo;
    }
    y->parent = novo->parent;
    if (novo->parent == m_nil)
    {
        m_root = y;
    }
    else if (novo == novo->parent->left)
    {
        novo->parent->left = y;
    }
    else
    {
        novo->parent->right = y;
    }
    y->left = novo;
    novo->parent = y;
}

void RedBlackTree::right_rotate(Node *novo)
{
    Node *y = novo->left;
    novo->left = y->right;
    if (y->right != m_nil)
    {
        y->right->parent = novo;
    }
    y->parent = novo->parent;
    if (novo->parent == m_nil)
    {
        m_root = y;
    }
    else if (novo == novo->parent->right)
    {
        novo->parent->right = y;
    }
    else
    {
        novo->parent->left = y;
    }
    y->right = novo;
    novo->parent = y;
}

Node *RedBlackTree::minimum(Node *n)
{
    while (n->left != m_nil)
    {
        n = n->left;
    }
    return n;
}

#endif
