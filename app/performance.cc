#include <iostream>
#include <random>
#include <algorithm>
#include <vector>

#include "siga.h"
#include "sort.h"
#include "tools.h"

#include "b_tree.h"
#include "rb_tree.h"

#include <random>

int nRandom(int max) {
    // Crie um gerador de números aleatórios usando uma semente
    std::random_device rd;
    std::mt19937 rng(rd());

    // Crie uma distribuição de números uniformemente distribuídos no intervalo [min, max]
    std::uniform_int_distribution<int> uni(1, max);

    // Gere um número aleatório usando o gerador e a distribuição
    return uni(rng);
}

std::vector<int> gerarVetorAleatorios(int tamanho) {
    std::random_device rd;
    std::mt19937 rng(rd());

    std::vector<int> Vetor(tamanho);
    for (int i = 0; i < tamanho; i++) {
        Vetor[i] = i + 1; // Preenche o vetor com os números de 1 a tamanho
    }

    std::shuffle(Vetor.begin(), Vetor.end(), rng); // Embaralha os números

    return Vetor;
}

void inserir(RBTree<int> rb, vector<int> vetor, int TAM){
    for(int i = 0; i<TAM; i++){
        rb.inserir(vetor[i]); // insere
    }
}

int NumRand(int TAM) {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(1, TAM);

    return dist(rng);
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

    ArvoreB<int> b;
    RBTree<int> rb;

    int TAM = 100;

    for(int i = 0; i<TAM; i++){
        b.inserir(nRandom(100));
    }




    No<int>* no = b.buscar(7);
    //Arvore-B
    cout<<endl<<"------------------------------------------------------------------------------"<<endl;
    cout<<"                           Arvore B:" << endl;
    cout<<"Numero de comparacoes: "<<b.getPer();

    //Arvore-Black-Red
    cout<<endl<<"------------------------------------------------------------------------------"<<endl;
    cout<<"                           Arvore RED-BLACK:" << endl;
    std::vector<int> vetor; 
    NoRB<int>* no_rb;
    
    // 100
    vetor = gerarVetorAleatorios(100);
    inserir(rb, vetor, 100);
    no_rb = rb.buscar(NumRand(100));
    cout<<"Numero de comparacoes para cem valores         : "<<rb.getPer()<< endl;
    
    // mil
    vetor = gerarVetorAleatorios(1000);
    inserir(rb, vetor, 1000);
    no_rb = rb.buscar(NumRand(1000));
    cout<<"Numero de comparacoes para mil valores         : "<<rb.getPer()<< endl;

    // 10 mil
    vetor = gerarVetorAleatorios(10000); 
    inserir(rb, vetor, 10000);
    no_rb = rb.buscar(NumRand(10000));
    cout<<"Numero de comparacoes para dez mil valores     : "<<rb.getPer()<< endl;

    // cem mil
    vetor = gerarVetorAleatorios(100000); 
    inserir(rb, vetor, 100000);
    no_rb = rb.buscar(NumRand(100000));
    cout<<"Numero de comparacoes para cem mil valores     : "<<rb.getPer()<< endl;

    // um milhao
    vetor = gerarVetorAleatorios(1000000); 
    inserir(rb, vetor, 1000000);
    no_rb = rb.buscar(NumRand(1000000));
    cout<<"Numero de comparacoes para um milhao de valores: "<<rb.getPer()<< endl;

    cout<<"------------------------------------------------------------------------------"<<endl;

    
    return 0;

}

