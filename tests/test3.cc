#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

// Implemente aqui testes para remoção de arvore vermelho-preto

#include "rb_tree.h"

int main()
{
RBTree<int> arvore;

    arvore.inserir(5);
    arvore.inserir(3);
    arvore.inserir(7);
    arvore.inserir(1);
    arvore.inserir(4);


    std::cout << "Excluindo o valor 3..." << std::endl;
    arvore.remover(3);

    // Verificar se o valor 3 ainda está presente na árvore após a exclusão
    NoRB<int>* no3 = arvore.buscar(3);
    if (no3 != nullptr) {
        std::cout << "Teste falhou. O valor 3 ainda está presente na árvore." << std::endl;
        return -1;
    }

     NoRB<int>* resultado = arvore.buscar(3);
    if (resultado != nullptr){
        std::cout << "Valor encontrado: " << resultado->getInfo() << std::endl;
        return -1;
    }

    return 0;
}