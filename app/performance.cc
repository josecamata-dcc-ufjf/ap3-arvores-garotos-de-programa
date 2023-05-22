#include <iostream>
#include <random>
#include <algorithm>
#include <vector>

#include "siga.h"
#include "sort.h"
#include "tools.h"

#include "b_tree.h"
#include "rb_tree.h"

std::vector<int> gerarVetor(int tamanho) {

    std::vector<int> Vetor(tamanho);
    for (int i = 0; i < tamanho; i++) {
        Vetor[i] = i + 1; // Preenche o vetor com os números de 1 a tamanho
    }

    return Vetor;
}


int NumRand(int TAM) {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(1, TAM);

    return dist(rng);
}

void constroiRB(int max){
    std::random_device rd;
    std::mt19937 rng(rd());

    std::vector<int>randomVector(max);
    std::vector<int>ordenedVector(max);

    NoRB<int>* no_rb;
    RBTree<int> rb;

    ordenedVector = gerarVetor(max);
    randomVector = ordenedVector;
    std::shuffle(randomVector.begin(), randomVector.end(), rng); // Embaralha os números 

    for(int i = 0; i<max; i++){
        rb.inserir(randomVector[i]); // insere
    }

    no_rb = rb.buscar(NumRand(max));
    cout <<rb.getPer()<< endl;

}


int main(int argc, const char* argv[])
{
    // TODO: 
    //      Implementar medição  de performance considerando inserção de chaves inteiras aleatórias
    //      e chaves ordenados.
    //      Use base de dados com 100, 1000, 10000, 100000, 1000000 elementos.
    //       - Para árvores AVL e Vermelho-Preto, compare o número de total rotações no processo de
    //         inserção.
    //       - Para arvore B, teste para diferentes ordem: 2, 4, 8, 16;
    //       - Verifique o número de comparações na busca tanto na arvore AVL, vermelho-preto e na arvore B
    //      Indique os resultados obtidos no arquivo REPORT.md
   
cout<<endl<<"------------------------------------------------------------------------------"<<endl;
    cout<<"                           Arvore RED-BLACK:" << endl;

    cout<<"Numero de comparacoes para cem valores         : ";
    constroiRB(100);
    cout<<"Numero de comparacoes para mil valores         : ";
    constroiRB(1000);
    cout<<"Numero de comparacoes para dez mil valores     : ";
    constroiRB(1000);
    cout<<"Numero de comparacoes para cem mil valores     : ";
    constroiRB(100000);
    cout<<"Numero de comparacoes para um milhao de valores: ";
    constroiRB(1000000);

    cout<<"------------------------------------------------------------------------------"<<endl;
    
    return 0;

}