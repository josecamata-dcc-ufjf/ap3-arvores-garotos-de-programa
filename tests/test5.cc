
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

#include "b_tree.h"

// Implemente aqui testes para busca de arvore B
int main()
{
    ArvoreB<int> arvore;

    arvore.inserir(5);
    arvore.inserir(3);
    arvore.inserir(7);
    arvore.inserir(1);
    arvore.inserir(4);

    std::cout << "Raiz: " << arvore.getRaiz()->getInfo() << std::endl;

    No<int>* no7 = arvore.buscar(7);
    if (no7 != nullptr) {
        std::cout << "Pai do 7: " << no7->getPai()->getInfo() << std::endl;
        return 0;
    }

    return -1;
}
