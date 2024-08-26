#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include "AVLTree.h"       // Implementação da árvore AVL
#include "RedBlackTree.h"  // Implementação da árvore Rubro-Negra
#include "HashTable.h"     // Implementação da tabela hash com encadeamento exterior
#include "OpenAddressingHashTable.h" // Implementação da tabela hash com endereçamento aberto

void processFile(const std::string& filename, AVLTree& avl, RedBlackTree& rb, HashTable& hashChain, OpenAddressingHashTable& hashOpen) {
    std::ifstream file(filename);
    std::string word;
    while (file >> word) {
        // Remove pontuações e converte para minúsculas
        word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);

        // Inserir nas estruturas de dados
        avl.insert(word);
        rb.insert(word);
        hashChain.insert(word);
        hashOpen.insert(word);
    }
}

int main() {
    AVLTree avl;
    RedBlackTree rb;
    HashTable hashChain(1024); // Tamanho da tabela hash
    OpenAddressingHashTable hashOpen(1024); // Tamanho da tabela hash

    std::string filename = "texto.txt";
    processFile(filename, avl, rb, hashChain, hashOpen);

    // Imprimir as palavras e suas frequências em ordem alfabética
    std::cout << "AVL Tree:" << std::endl;
    avl.printInOrder();

    std::cout << "Red-Black Tree:" << std::endl;
    rb.printInOrder();

    std::cout << "Hash Table (Encadeamento Exterior):" << std::endl;
    hashChain.printSorted();

    std::cout << "Hash Table (Endereçamento Aberto):" << std::endl;
    hashOpen.printSorted();

    return 0;
}
