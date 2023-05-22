#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "rb_tree.h"

int main() {
    RBTree<int> arvore;

    // Inserção de valores na árvore
    arvore.inserir(10);
    arvore.inserir(20);
    arvore.inserir(30);
    arvore.inserir(40);
    arvore.inserir(50);

    // Teste de busca
    NoRB<int>* resultado = arvore.buscar(30);
    if (resultado != nullptr){
        std::cout << "Valor encontrado: " << resultado->getInfo() << std::endl;
        return 0;
    }


    arvore.deleteArvoreAVL();
    return -1;
}