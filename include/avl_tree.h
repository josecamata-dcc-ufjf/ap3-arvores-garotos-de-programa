#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>

#include "perf.h"
#include "../src/perf.cc"

template <typename T>
class ArvoreAVL;

template <typename T>
class NoAVL {
private:
    T info;
    NoAVL<T>* pai;
    NoAVL<T>* esq;
    NoAVL<T>* dir;
    int altura;

public:
    NoAVL(T valor) : info(valor), pai(nullptr), esq(nullptr), dir(nullptr), altura(1) {}

    // Getters e Setters
    NoAVL<T>* getPai() { return pai; }
    NoAVL<T>* getEsq() { return esq; }
    NoAVL<T>* getDir() { return dir; }
    T getInfo() { return info; }
    int getAltura() { return altura; }

    void setPai(NoAVL<T>* novoPai) { pai = novoPai; }
    void setEsq(NoAVL<T>* novoEsq) { esq = novoEsq; }
    void setDir(NoAVL<T>* novoDir) { dir = novoDir; }
    void setInfo(T novaInfo) { info = novaInfo; }
    void setAltura(int novaAltura) { altura = novaAltura; }

    friend class ArvoreAVL<T>;
};

template <typename T>
class ArvoreAVL {
private:
    NoAVL<T>* raiz;

    // Funções auxiliares
    int altura(NoAVL<T>* no) {
        if (no == nullptr)
            return 0;
        return no->getAltura();
    }

    int fatorBalanceamento(NoAVL<T>* no) {
        if (no == nullptr)
            return 0;
        return altura(no->getEsq()) - altura(no->getDir());
    }

    void atualizarAltura(NoAVL<T>* no) {
        int alturaEsq = altura(no->getEsq());
        int alturaDir = altura(no->getDir());
        no->setAltura(1 + std::max(alturaEsq, alturaDir));
    }

    NoAVL<T>* rotacaoEsquerda(NoAVL<T>* no) {
        perf.get_counter().increment_swaps();
        NoAVL<T>* novoNo = no->getDir();
        no->setDir(novoNo->getEsq());
        if (novoNo->getEsq() != nullptr)
            novoNo->getEsq()->setPai(no);
        novoNo->setPai(no->getPai());
        if (no->getPai() == nullptr)
            raiz = novoNo;
        else if (no == no->getPai()->getEsq())
            no->getPai()->setEsq(novoNo);
        else
            no->getPai()->setDir(novoNo);
        novoNo->setEsq(no);
        no->setPai(novoNo);
        atualizarAltura(no);
        atualizarAltura(novoNo);
        return novoNo;
    }

    NoAVL<T>* rotacaoDireita(NoAVL<T>* no) {
        perf.get_counter().increment_swaps();
        NoAVL<T>* novoNo = no->getEsq();
        no->setEsq(novoNo->getDir());
        if (novoNo->getDir() != nullptr)
            novoNo->getDir()->setPai(no);
        novoNo->setPai(no->getPai());
        if (no->getPai() == nullptr)
            raiz = novoNo;
        else if (no == no->getPai()->getDir())
            no->getPai()->setDir(novoNo);
        else
            no->getPai()->setEsq(novoNo);
        novoNo->setDir(no);
        no->setPai(novoNo);
        atualizarAltura(no);
        atualizarAltura(novoNo);
        return novoNo;
    }

    NoAVL<T>* balancear(NoAVL<T>* no) {
        atualizarAltura(no);
        int fb = fatorBalanceamento(no);
        if (fb > 1) {
            if (fatorBalanceamento(no->getEsq()) < 0)
                no->setEsq(rotacaoEsquerda(no->getEsq()));
            return rotacaoDireita(no);
        }
        if (fb < -1) {
            if (fatorBalanceamento(no->getDir()) > 0)
                no->setDir(rotacaoDireita(no->getDir()));
            return rotacaoEsquerda(no);
        }
        return no;
    }

    NoAVL<T>* inserirRecursivo(NoAVL<T>* no, const T& valor) {
        if (no == nullptr)
            return new NoAVL<T>(valor);

        if (valor < no->getInfo()) {
            NoAVL<T>* novoEsq = inserirRecursivo(no->getEsq(), valor);
            no->setEsq(novoEsq);
            novoEsq->setPai(no);
        } else {
            NoAVL<T>* novoDir = inserirRecursivo(no->getDir(), valor);
            no->setDir(novoDir);
            novoDir->setPai(no);
        }

        return balancear(no);
    }

    NoAVL<T>* removerRecursivo(NoAVL<T>* no, const T& valor) {
        if (no == nullptr)
            return no;

        if (valor < no->getInfo()) {
            NoAVL<T>* novoEsq = removerRecursivo(no->getEsq(), valor);
            no->setEsq(novoEsq);
            if (novoEsq != nullptr)
                novoEsq->setPai(no);
        } else if (valor > no->getInfo()) {
            NoAVL<T>* novoDir = removerRecursivo(no->getDir(), valor);
            no->setDir(novoDir);
            if (novoDir != nullptr)
                novoDir->setPai(no);
        } else {
            if (no->getEsq() == nullptr && no->getDir() == nullptr) {
                delete no;
                return nullptr;
            } else if (no->getEsq() == nullptr) {
                NoAVL<T>* filhoDir = no->getDir();
                filhoDir->setPai(no->getPai());
                delete no;
                return filhoDir;
            } else if (no->getDir() == nullptr) {
                NoAVL<T>* filhoEsq = no->getEsq();
                filhoEsq->setPai(no->getPai());
                delete no;
                return filhoEsq;
            } else {
                NoAVL<T>* sucessor = encontrarMinimo(no->getDir());
                no->setInfo(sucessor->getInfo());
                NoAVL<T>* novoDir = removerRecursivo(no->getDir(), sucessor->getInfo());
                no->setDir(novoDir);
                if (novoDir != nullptr)
                    novoDir->setPai(no);
            }
        }

        return balancear(no);
    }

    NoAVL<T>* encontrarMinimo(NoAVL<T>* no) {
        if (no->getEsq() == nullptr)
            return no;
        return encontrarMinimo(no->getEsq());
    }

    NoAVL<T>* buscarRecursivo(NoAVL<T>* no, const T& valor) {
        perf.get_counter().increment_comparisons();
        if (no == nullptr || no->getInfo() == valor)
            return no;

        perf.get_counter().increment_comparisons();
        if (valor < no->getInfo())
            return buscarRecursivo(no->getEsq(), valor);

        return buscarRecursivo(no->getDir(), valor);
    }

    void limparArvore(NoAVL<T>* no) {
    if (no != nullptr) {
        limparArvore(no->esq);
        limparArvore(no->dir);
        delete no;
    }
}
public:

    Perf::Performance perf;

    unsigned int getComp(){
        return perf.get_counter().get_comparisons();
    }

    unsigned int getRota(){
        return perf.get_counter().get_swaps();
    }

    ArvoreAVL() : raiz(nullptr) {}

    void inserir(const T& valor) {
        raiz = inserirRecursivo(raiz, valor);
    }

    void remover(const T& valor) {
        raiz = removerRecursivo(raiz, valor);
    }

    NoAVL<T>* buscar(const T& valor) {
        return buscarRecursivo(raiz, valor);
    }


    
    void deleteArvoreAVL(){
        limparArvore(raiz);
    }

};



#endif