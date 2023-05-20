
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

#include "b_tree.h"

// Implemente aqui testes para inserção de arvore B
int main() {
    BTree tree;

    // Inserção de chaves
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.insert(6);
    tree.insert(12);
    tree.insert(30);

    // Percorre a árvore em ordem
    std::cout << "Árvore B percorrida em ordem:" << std::endl;
    tree.traverse();

    return 0;
}
