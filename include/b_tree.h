#ifndef B_TREE_H
#define B_TREE_H

//TODO: Implemenatar a árvore B aqui e classes auxiliares (se necessário)

#include <iostream>

template <typename T>
class ArvoreB;

template <typename T>
class No {
private:
    T info;
    No<T>* esq;
    No<T>* dir;
    No<T>* pai;

public:
    No(T n) : info(n), esq(nullptr), dir(nullptr), pai(nullptr) {}

    T getInfo() const {
        return info;
    }

    No<T>* getEsq() const {
        return esq;
    }

    No<T>* getDir() const {
        return dir;
    }

    No<T>* getPai() const {
        return pai;
    }

    friend class ArvoreB<T>;
};

template <typename T>
class ArvoreB {
private:
    No<T>* raiz;

public:
    ArvoreB() : raiz(nullptr) {}

    No<T>* getRaiz() const {
        return raiz;
    }

    void inserir(T n) {
        if (raiz == nullptr) {
            raiz = new No<T>(n);
        } else {
            inserirNo(raiz, n);
        }
    }

    void excluir(T n) {
        excluirNo(raiz, n);
    }

    No<T>* buscar(T n) {
        return buscarNo(raiz, n);
    }

private:
    void inserirNo(No<T>* no, T n) {
        if (n < no->getInfo()) {
            if (no->getEsq() == nullptr) {
                No<T>* novoNo = new No<T>(n);
                novoNo->pai = no;
                no->esq = novoNo;
            } else {
                inserirNo(no->getEsq(), n);
            }
        } else if (n > no->getInfo()) {
            if (no->getDir() == nullptr) {
                No<T>* novoNo = new No<T>(n);
                novoNo->pai = no;
                no->dir = novoNo;
            } else {
                inserirNo(no->getDir(), n);
            }
        }
    }

    void excluirNo(No<T>* no, T n) {
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
                No<T>* sucessor = no->getDir();
                while (sucessor->getEsq() != nullptr) {
                    sucessor = sucessor->getEsq();
                }
                no->info = sucessor->getInfo();
                excluirNo(sucessor, sucessor->getInfo());
            } else {
                No<T>* filho = (no->getEsq() != nullptr) ? no->getEsq() : no->getDir();
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

    No<T>* buscarNo(No<T>* no, T n) {
        if (no == nullptr || no->getInfo() == n) {
            return no;
        }

        if (n < no->getInfo()) {
            return buscarNo(no->getEsq(), n);
        } else {
            return buscarNo(no->getDir(), n);
        }
    }
};
    

#endif /* B_TREE_H */
