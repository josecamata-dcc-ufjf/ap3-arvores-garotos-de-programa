
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

#include "b_tree.h"

// Implemente aqui testes para remoção de arvore B
int main() {
     BTree tree;

    // Inserindo chaves na árvore
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(60);
    tree.insert(70);
    tree.insert(80);
    tree.insert(90);

    cout << "Árvore B original: ";
    tree.traverse();
    cout << endl;

    // Removendo chaves da árvore
    cout << "Removendo a chave 30" << endl;
    tree.remove(30);
    cout << "Árvore B após remoção: ";
    tree.traverse();
    cout << endl;

    cout << "Removendo a chave 50" << endl;
    tree.remove(50);
    cout << "Árvore B após remoção: ";
    tree.traverse();
    cout << endl;

    cout << "Removendo a chave 70" << endl;
    tree.remove(70);
    cout << "Árvore B após remoção: ";
    tree.traverse();
    cout << endl;

    return 0;
}