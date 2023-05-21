#ifndef RB_NODE_H
#define RB_NODE_H

#include <iostream>
#include <string>
using namespace std;

namespace BRtree
{

template <typename T>
class RedBlackTree;
    
template <typename T>
class No
{
    friend class RedBlackTree<T>;
    public:
        No<T>* getEsq();
        No<T>* getDir();
        No<T>* getPai();
        T      getInfo();
        int getCor(); // vermelho == 1, preto == 0
    
        void setEsq(No<T> *Esq);
        void setDir(No<T> *Dir);
        void setInfo(T key);
        void setPai(No<T> *Pai);
        void setCor(int cor);
        
    private:
        T  info;
        No<T> *esq;
        No<T> *dir;
        No<T> *pai;
        int cor;
};

template <typename T>
T No<T>::getInfo()
{
    return info;
}

template <typename T>
int No<T>::getCor()
{
    return cor;
}

template <typename T>
No<T>* No<T>::getEsq()
{
    return esq;
}

template <typename T>
No<T>* No<T>::getDir()
{
    return dir;
}

template <typename T>
No<T>* No<T>::getPai()
{
    return pai;
}

template <typename T>
void No<T>::setEsq(No<T> *esq)
{
    this->esq = esq;
}
template <typename T>
void No<T>::setDir(No<T> *dir)
{
    this->dir = dir;
}

template <typename T>
void No<T>::setPai(No<T> *pai)
{
    this->pai = pai;
}

template <typename T>
void No<T>::setInfo(T info)
{
    this->info = info;
}

template <typename T>
void No<T>::setCor(int cor)
{
    this->cor = cor;
}

}
#endif /* RB_TREE_H */