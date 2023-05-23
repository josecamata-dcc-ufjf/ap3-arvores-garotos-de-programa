
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

#include "b_tree.h"


int main() {
   int t = 3;  
    ArvoreB<int> arvoreB(t);

    // Teste de inserção
    arvoreB.inserir(10);
    arvoreB.inserir(20);
    arvoreB.inserir(5);
    arvoreB.inserir(30);

    arvoreB.remover(10);


    if (arvoreB.buscar(10) != false) {
        std::cout << "A exclusão falhou!" << std::endl;
        return -1;
    }

    std::cout << "A exclusão foi bem-sucedida!" << std::endl;


    return 0;
}