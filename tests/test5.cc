
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

#include "b_tree.h"


int main()
{
    int t = 3;  
    ArvoreB<int> arvoreB(t);


    arvoreB.inserir(10);
    arvoreB.inserir(20);
    arvoreB.inserir(5);
    arvoreB.inserir(30);

    bool busca = arvoreB.buscar(10);


    if (busca == false) {
        std::cout << "O teste falhou!" << std::endl;
        return -1;
    }

    std::cout << "O teste foi bem-sucedido!" << std::endl;

    return 0;
}
