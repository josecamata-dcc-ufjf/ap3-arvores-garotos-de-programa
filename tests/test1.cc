
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "rb_tree.h"
#include "rb_node.h"

// Implemente aqui testes para inserção de arvore vermelho-preto
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

    if(tree.busca(15)){
        return 0;
    }
    else
        return -1;
}


