#include <iostream>
#include "AVLTree.h"

int main()
{
    AVLTree tree;

    // Teste de inserção
    std::cout << "Inserting: apple\n";
    tree.insert({"apple", 1}); // Corrigido: inserção com dois argumentos separados

    std::cout << "Inserting: banana\n";
    tree.insert({"banana", 1}); // Corrigido: inserção com dois argumentos separados

    std::cout << "Inserting: cherry\n";
    tree.insert({"cherry", 1}); // Corrigido: inserção com dois argumentos separados

    // Teste de busca
    auto result = tree.search("b");
    if (result != nullptr)
    {
        std::cout << "Found: " << result->getWord() << " with frequency " << result->getFrequency() << "\n";
    }
    else
    {
        std::cout << "Word 'banana' not found in the AVL Tree.\n";
    }

    // Teste de remoção
    std::cout << "Removing: banana\n";
    tree.remove("banana");

    result = tree.search("banana");
    if (result != nullptr)
    {
        std::cout << "Found: " << result->getWord() << " with frequency " << result->getFrequency() << "\n";
    }
    else
    {
        std::cout << "Word 'banana' not found after removal.\n";
    }

    // Removendo uma palavra que não existe
    std::cout << "Removing: orange (not present)\n";
    tree.remove("orange");

    // Inserting a word that already exists
    std::cout << "Inserting: a (already present)\n";
    tree.insert({"a", 1});

    // Teste de busca após remoção
    std::cout << "Searching for: a\n";
    result = tree.search("a");
    if (result != nullptr)
    {
        std::cout << "Found: " << result->getWord() << " with frequency " << result->getFrequency() << "\n";
    }
    else
    {
        std::cout << "Word 'apple' not found.\n";
    }

    return 0;
}
