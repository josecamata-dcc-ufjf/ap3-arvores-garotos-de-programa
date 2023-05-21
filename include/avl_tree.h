#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>

template<typename T>
class ArvoreAVL;

template<typename T>
class No {
private:
    T info;
    No<T>* esquerda;
    No<T>* direita;
    No<T>* pai;

public:
    No(T valor) : info(valor), esquerda(nullptr), direita(nullptr), pai(nullptr) {}

    T getInfo() const {
        return info;
    }

    No<T>* getEsquerda() const {
        return esquerda;
    }

    No<T>* getDireita() const {
        return direita;
    }

    No<T>* getPai() const {
        return pai;
    }

    friend class ArvoreAVL<T>;
};

template<typename T>
class ArvoreAVL {
private:
    No<T>* raiz;

    // Métodos auxiliares
    int altura(No<T>* no) const {
        if (no == nullptr)
            return -1;
        return 1 + std::max(altura(no->getEsquerda()), altura(no->getDireita()));
    }

    int fatorBalanceamento(No<T>* no) const {
        if (no == nullptr)
            return 0;
        return altura(no->getEsquerda()) - altura(no->getDireita());
    }

    No<T>* rotacaoEsquerda(No<T>* no) {
        No<T>* novaRaiz = no->getDireita();
        no->direita = novaRaiz->getEsquerda();
        if (novaRaiz->getEsquerda() != nullptr)
            novaRaiz->getEsquerda()->pai = no;
        novaRaiz->esquerda = no;
        novaRaiz->pai = no->getPai();
        no->pai = novaRaiz;
        if (novaRaiz->getPai() != nullptr) {
            if (novaRaiz->getPai()->getEsquerda() == no)
                novaRaiz->getPai()->esquerda = novaRaiz;
            else
                novaRaiz->getPai()->direita = novaRaiz;
        }
        no = novaRaiz;
        return no;
    }

    No<T>* rotacaoDireita(No<T>* no) {
        No<T>* novaRaiz = no->getEsquerda();
        no->esquerda = novaRaiz->getDireita();
        if (novaRaiz->getDireita() != nullptr)
            novaRaiz->getDireita()->pai = no;
        novaRaiz->direita = no;
        novaRaiz->pai = no->getPai();
        no->pai = novaRaiz;
        if (novaRaiz->getPai() != nullptr) {
            if (novaRaiz->getPai()->getEsquerda() == no)
                novaRaiz->getPai()->esquerda = novaRaiz;
            else
                novaRaiz->getPai()->direita = novaRaiz;
        }
        no = novaRaiz;
        return no;
    }

    void balancearArvore(No<T>* no) {
        while (no != nullptr) {
            int fb = fatorBalanceamento(no);
            if (fb > 1) {
                if (fatorBalanceamento(no->getEsquerda()) < 0)
                    no->esquerda = rotacaoEsquerda(no->getEsquerda());
                no = rotacaoDireita(no);
            } else if (fb < -1) {
                if (fatorBalanceamento(no->getDireita()) > 0)
                    no->direita = rotacaoDireita(no->getDireita());
                no = rotacaoEsquerda(no);
            }
            no = no->getPai();
        }
    }

    No<T>* inserirNo(No<T>* no, T valor) {
        if (no == nullptr)
            return new No<T>(valor);
        if (valor < no->getInfo()) {
            No<T>* novoNo = inserirNo(no->getEsquerda(), valor);
            no->esquerda = novoNo;
            novoNo->pai = no;
        } else if (valor > no->getInfo()) {
            No<T>* novoNo = inserirNo(no->getDireita(), valor);
            no->direita = novoNo;
            novoNo->pai = no;
        }
        balancearArvore(no);
        return no;
    }

    No<T>* buscarNo(No<T>* no, T valor) const {
        if (no == nullptr || no->getInfo() == valor)
            return no;
        if (valor < no->getInfo())
            return buscarNo(no->getEsquerda(), valor);
        return buscarNo(no->getDireita(), valor);
    }

    No<T>* encontrarNoMinimo(No<T>* no) const {
        if (no == nullptr)
            return nullptr;
        while (no->getEsquerda() != nullptr)
            no = no->getEsquerda();
        return no;
    }

    No<T>* removerNo(No<T>* no, T valor) {
        if (no == nullptr)
            return no;
        if (valor < no->getInfo()) {
            no->esquerda = removerNo(no->getEsquerda(), valor);
        } else if (valor > no->getInfo()) {
            no->direita = removerNo(no->getDireita(), valor);
        } else {
            if (no->getEsquerda() == nullptr) {
                No<T>* temp = no->getDireita();
                if (temp != nullptr)
                    temp->pai = no->getPai();
                delete no;
                return temp;
            } else if (no->getDireita() == nullptr) {
                No<T>* temp = no->getEsquerda();
                if (temp != nullptr)
                    temp->pai = no->getPai();
                delete no;
                return temp;
            }
            No<T>* temp = encontrarNoMinimo(no->getDireita());
            no->info = temp->getInfo();
            no->direita = removerNo(no->getDireita(), temp->getInfo());
        }
        balancearArvore(no);
        return no;
    }

public:
    ArvoreAVL() : raiz(nullptr) {}

    No<T>* getRaiz() const {
        return raiz;
    }

    void inserir(T valor) {
        raiz = inserirNo(raiz, valor);
    }

    No<T>* buscar(T valor) const {
        return buscarNo(raiz, valor);
    }

    void remover(T valor) {
        raiz = removerNo(raiz, valor);
    }
};

#endif