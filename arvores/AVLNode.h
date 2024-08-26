#ifndef AVLNODE_H
#define AVLNODE_H

#include <iostream>
#include <utility> // Inclui a definição de std::pair

template <typename Word, typename Frequency>
struct AVLNode
{
    std::pair<Word, Frequency> data; // Par contendo a palavra e a frequência
    int height;
    AVLNode *left;
    AVLNode *right;

    AVLNode(Word word, Frequency freq = 1, AVLNode *left = nullptr, AVLNode *right = nullptr)
    {
        this->data = std::make_pair(word, freq);
        this->height = 1;
        this->left = left;
        this->right = right;
    }

    Word getWord() const
    {
        return data.first;
    }

    Frequency getFrequency() const
    {
        return data.second;
    }

    void setFrequency(Frequency freq)
    {
        data.second = freq;
    }
};

#endif
