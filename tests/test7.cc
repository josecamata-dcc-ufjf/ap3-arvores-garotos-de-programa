
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;


#include <iostream>
#include "avl_tree.h"

int main() {
    // Crie uma instância da árvore AVL
    ArvoreAVL<int> arvore;

    // Inserir elementos na árvore
    arvore.inserir(5);
    arvore.inserir(3);
    arvore.inserir(7);
    arvore.inserir(2);
    arvore.inserir(4);
    arvore.inserir(6);

    // Testar busca
    NoAVL<int>* no = arvore.buscar(7);
    if (no != nullptr) {
        std::cout << "Elemento encontrado: " << no->getInfo() << std::endl;
    } else {
        std::cout << "Elemento não encontrado!" << std::endl;
        return -1;
    }

    arvore.deleteArvoreAVL();
    
    return 0;
}