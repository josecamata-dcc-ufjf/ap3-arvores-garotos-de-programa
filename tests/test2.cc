
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

#include "rb_tree.h"
#include "rb_node.h"

// Implemente aqui testes para busca de arvore vermelho-preto
int main(int argc, char* argv[])
{
    BRtree::RedBlackTree<int> arvore;
    

    // Inserção de valores na árvore
    arvore.insert(10);
    arvore.insert(20);
    arvore.insert(30);
    arvore.insert(40);
    arvore.insert(50);

    // Teste de busca
    if (arvore.busca(10)){
        std::cout << "Valor encontrado: "<< std::endl;
        return 0;
    }

    return -1;
}

    
    
