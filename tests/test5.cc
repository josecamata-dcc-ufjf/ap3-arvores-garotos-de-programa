
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

#include "b_tree.h"

// Implemente aqui testes para busca de arvore B
int main()
{

    BTree tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.insert(6);
    tree.insert(12);
    tree.insert(30);

    int searchKey = 12;
    Node *searchResult = tree.search(searchKey);
    if (searchResult != nullptr){
        std::cout << "Chave " << searchKey << " encontrada!" << std::endl;

        return 0;
    }else{
        std::cout << "Chave " << searchKey << " não encontrada!" << std::endl;
    }

    return -1;
}
