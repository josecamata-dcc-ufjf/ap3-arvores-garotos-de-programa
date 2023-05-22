#ifndef B_TREE_H
#define B_TREE_H

//TODO: Implemenatar a árvore B aqui e classes auxiliares (se necessário)

#include <iostream>
#include "perf.h"

template <typename T>
class ArvoreB;

template <typename T>
class NoB {
private:
    T info;
    NoB<T>* esq;
    NoB<T>* dir;
    NoB<T>* pai;

public:
    NoB(T n) : info(n), esq(nullptr), dir(nullptr), pai(nullptr) {}

    T getInfo() const {
        return info;
    }

    NoB<T>* getEsq() const {
        return esq;
    }

    NoB<T>* getDir() const {
        return dir;
    }

    NoB<T>* getPai() const {
        return pai;
    }

    friend class ArvoreB<T>;
};

template <typename T>
class ArvoreB {
private:
    NoB<T>* raiz;

public:

    Perf::Performance perf;

    unsigned int getComp(){
        return perf.get_counter().get_comparisons();
    }

    unsigned int getRota(){
        return perf.get_counter().get_swaps();
    }

    ArvoreB() : raiz(nullptr) {}

    NoB<T>* getRaiz() const {
        return raiz;
    }

    void inserir(T n) {
        if (raiz == nullptr) {
            raiz = new NoB<T>(n);
        } else {
            inserirNo(raiz, n);
        }
    }

    void excluir(T n) {
        excluirNo(raiz, n);
    }

    NoB<T>* buscar(T n) {
        return buscarNo(raiz, n);
    }

private:
    void inserirNo(NoB<T>* no, T n) {
        if (n < no->getInfo()) {
            if (no->getEsq() == nullptr) {
                NoB<T>* novoNo = new NoB<T>(n);
                novoNo->pai = no;
                no->esq = novoNo;
            } else {
                inserirNo(no->getEsq(), n);
            }
        } else if (n > no->getInfo()) {
            if (no->getDir() == nullptr) {
                NoB<T>* novoNo = new NoB<T>(n);
                novoNo->pai = no;
                no->dir = novoNo;
            } else {
                inserirNo(no->getDir(), n);
            }
        }
    }

    void excluirNo(NoB<T>* no, T n) {
        if (no == nullptr) {
            return;
        }

        if (n < no->getInfo()) {
            excluirNo(no->getEsq(), n);
        } else if (n > no->getInfo()) {
            excluirNo(no->getDir(), n);
        } else {
            if (no->getEsq() == nullptr && no->getDir() == nullptr) {
                if (no->getPai() == nullptr) {
                    raiz = nullptr;
                } else {
                    if (no == no->getPai()->getEsq()) {
                        no->getPai()->esq = nullptr;
                    } else {
                        no->getPai()->dir = nullptr;
                    }
                }
                delete no;
            } else if (no->getEsq() != nullptr && no->getDir() != nullptr) {
                NoB<T>* sucessor = no->getDir();
                while (sucessor->getEsq() != nullptr) {
                    sucessor = sucessor->getEsq();
                }
                no->info = sucessor->getInfo();
                excluirNo(sucessor, sucessor->getInfo());
            } else {
                NoB<T>* filho = (no->getEsq() != nullptr) ? no->getEsq() : no->getDir();
                if (no->getPai() == nullptr) {
                    raiz = filho;
                } else {
                    if (no == no->getPai()->getEsq()) {
                        no->getPai()->esq = filho;
                    } else {
                        no->getPai()->dir = filho;
                    }
                }
                filho->pai = no->getPai();
                delete no;
            }
        }
    }

    NoB<T>* buscarNo(NoB<T>* no, T n) {
        perf.get_counter().increment_comparisons();
        if (no == nullptr || no->getInfo() == n) {
            return no;
        }

        perf.get_counter().increment_comparisons();
        if (n < no->getInfo()) {
            return buscarNo(no->getEsq(), n);
        } else {
            return buscarNo(no->getDir(), n);
        }
    }
};
    

#endif /* B_TREE_H */
