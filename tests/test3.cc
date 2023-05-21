
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

#include "rb_tree.h"
#include "rb_node.h"

// Implemente aqui testes para remoção de arvore vermelho-preto
int main(int argc, char* argv[])
{
    BRtree::RedBlackTree<int> tree;
    

    // Inserção dos elementos na árvore
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(12);
    tree.insert(17);

    tree.imprime();
    tree.remove(10);
    tree.imprime();
    
    if(tree.busca(10))
        return -1;
    else
    return 0;
}
