#include <iostream>
#include <random>
#include <algorithm>
#include <vector>

#include "siga.h"
#include "sort.h"
#include "tools.h"

#include "b_tree.h"
#include "rb_tree.h"
#include "avl_tree.h"

std::vector<int> gerarVetor(int tamanho) {

    std::vector<int> Vetor(tamanho);
    for (int i = 1; i <= tamanho; i++) {
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
    Perf::PerformanceTimer tempOrd;
    Perf::PerformanceTimer tempAle;

    std::vector<int>randomVector(max);
    std::vector<int>ordenedVector(max);

    NoRB<int>* no_rb;
    RBTree<int> rb;
    RBTree<int> rb2;

    ordenedVector = gerarVetor(max);
    randomVector = ordenedVector;
    std::shuffle(randomVector.begin(), randomVector.end(), rng); // Embaralha os números 

    tempOrd.start();
    for(int i = 0; i<max; i++){
        rb2.inserir(ordenedVector[i]); // ordenado
    }
    tempOrd.stop();

    tempAle.start();
    for(int i = 0; i<max; i++){
        rb.inserir(randomVector[i]); // aleatorio
    }
    tempAle.stop();

    cout<<"Numero de comparacoes para " << max <<" valores                   : ";
    no_rb = rb.buscar(NumRand(max));
    cout <<rb.getComp()<< endl;

    cout<<"Numero de rotações com inserção aleatoria com " << max <<" valores: ";
    cout <<rb.getRota()<< endl;

    cout<<"Numero de rotações com inserção ordenada com " << max <<" valores : ";
    cout <<rb2.getRota()<< endl;
    
    cout <<"Tempo decorrido da inserção aleatoria"<<" com "<< max <<": " << tempAle.elapsed_time() << " segundos." << std::endl;
    cout <<"Tempo decorrido da inserção ordenada"<<" com "<< max <<" : " << tempOrd.elapsed_time() << " segundos." << std::endl;

    if(max!=1000000){
        cout<<"------------------------------------------------------------------------------"<<endl;
    }

    rb.deleteArvoreRB();
    rb2.deleteArvoreRB();
}

void constroiAVL(int max){
    std::random_device rd;
    std::mt19937 rng(rd());
    Perf::PerformanceTimer tempOrd;
    Perf::PerformanceTimer tempAle;

    std::vector<int>randomVector(max);
    std::vector<int>ordenedVector(max);

    NoAVL<int>* no_avl;
    ArvoreAVL<int> avl;    // aleatorio
    ArvoreAVL<int> avl2;   // ordenado 

    ordenedVector = gerarVetor(max);
    randomVector = ordenedVector;
    std::shuffle(randomVector.begin(), randomVector.end(), rng); // Embaralha os números 

     tempOrd.start();
    for(int i = 0; i<max; i++){
        avl2.inserir(ordenedVector[i]); // ordenado
    }
    tempOrd.stop();

    tempAle.start();
    for(int i = 0; i<max; i++){
        avl.inserir(randomVector[i]); // aleatorio
    }
    tempAle.stop();

    cout<<"Numero de comparacoes para " << max <<" valores                   : ";
    no_avl = avl.buscar(NumRand(max));
    cout <<avl.getComp()<< endl;

    cout<<"Numero de rotações com inserção aleatoria com " << max <<" valores: ";
    cout <<avl.getRota()<< endl;

    cout<<"Numero de rotações com inserção ordenada com " << max <<" valores : ";
    cout <<avl2.getRota()<< endl;

    cout <<"Tempo decorrido da inserção aleatoria"<<" com "<< max <<": " << tempAle.elapsed_time() << " segundos." << std::endl;
    cout <<"Tempo decorrido da inserção ordenada"<<" com "<< max <<" : " << tempOrd.elapsed_time() << " segundos." << std::endl;
    
    if(max!=1000000){
        cout<<"------------------------------------------------------------------------------"<<endl;
    }
    avl.deleteArvoreAVL();
    avl2.deleteArvoreAVL();
}

void constroiB(int max, int ordem){
    std::random_device rd;
    std::mt19937 rng(rd());
    
    Perf::PerformanceTimer tempOrd;
    Perf::PerformanceTimer tempAle;

    std::vector<int>randomVector(max);
    std::vector<int>ordenedVector(max);


    ArvoreB<int> b(ordem);
    ArvoreB<int> b2(ordem);

    ordenedVector = gerarVetor(max);
    randomVector = ordenedVector;
    std::shuffle(randomVector.begin(), randomVector.end(), rng); // Embaralha os números 

    tempOrd.start();
    for(int i = 0; i<max; i++){
        b.inserir(ordenedVector[i]); // insere
    }
    tempOrd.stop();

    tempAle.start();
    for(int i = 0; i<max; i++){
        b2.inserir(randomVector[i]); // aleatorio
    }
    tempAle.stop();

    cout<<"Numero de comparacoes para " << max <<" valores e ordem "<<ordem <<"       : ";
    bool no_b = b.buscar(NumRand(max));
    cout<<b.getComp()<<endl;

    cout <<"Tempo decorrido da inserção aleatoria"<<" com "<< max <<" e ordem "<<ordem<<": " << tempAle.elapsed_time() << " segundos." << std::endl;
    cout <<"Tempo decorrido da inserção ordenada"<<" com "<< max <<" e ordem "<<ordem<<" : " << tempOrd.elapsed_time() << " segundos." << std::endl;

    if(max!=1000000 && ordem == 16){
        cout<<"------------------------------------------------------------------------------"<<endl;
    }

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
  
    cout<<endl<<"=============================================================================="<<endl;
    cout<<"                           Arvore RED-BLACK:" << endl;
    
    constroiRB(100);
    constroiRB(1000);
    constroiRB(10000);
    constroiRB(100000);
    constroiRB(1000000);

    cout<<"=============================================================================="<<endl;
    cout<<"                           Arvore AVL:" << endl;


    constroiAVL(100);
    constroiAVL(1000);
    constroiAVL(10000);
    constroiAVL(100000);
    constroiAVL(1000000);

    cout<<"=============================================================================="<<endl;

   cout<<endl<<"=============================================================================="<<endl;
    cout<<"                           Arvore B:" << endl;
    
   
    constroiB(100, 2); constroiB(100, 4); constroiB(100, 8); constroiB(100, 16);
    constroiB(1000, 2); constroiB(1000, 4); constroiB(1000, 8); constroiB(1000, 16);
    constroiB(10000, 2); constroiB(10000, 4); constroiB(10000, 8); constroiB(10000, 16);
    constroiB(100000, 2); constroiB(100000, 4); constroiB(100000, 8); constroiB(100000, 16);
    constroiB(1000000, 2); constroiB(1000000, 4); constroiB(1000000, 8); constroiB(1000000, 16);

    cout<<"=============================================================================="<<endl;

    return 0;

}