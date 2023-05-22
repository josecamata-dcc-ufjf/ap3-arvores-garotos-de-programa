#ifndef RB_TREE_H
#define RB_TREE_H

// TODO: Implementar a árvore rubro-negra aqui e classes auxiliares (se necessário)

#include <iostream>

#include "perf.h"

template <typename T>
class RBTree;

template <typename T>
class NoRB {
private:
    T info;
    NoRB<T>* esq;
    NoRB<T>* dir;
    NoRB<T>* pai;
    bool cor; // 1 para vermelho, 0 para preto

public:
    NoRB(const T& valor) : info(valor), esq(nullptr), dir(nullptr), pai(nullptr), cor(1) {}

    T getInfo() const {
        return info;
    }

    NoRB<T>* getEsq() const {
        return esq;
    }

    NoRB<T>* getDir() const {
        return dir;
    }

    NoRB<T>* getPai() const {
        return pai;
    }

    bool getCor() const {
        return cor;
    }

    friend class RBTree<T>;
};

template <typename T>
class RBTree {
private:
    NoRB<T>* root;

    void rotacaoEsq(NoRB<T>* x) {
        NoRB<T>* y = x->dir;
        x->dir = y->esq;

        if (y->esq != nullptr)
            y->esq->pai = x;

        y->pai = x->pai;

        if (x->pai == nullptr)
            root = y;
        else if (x == x->pai->esq)
            x->pai->esq = y;
        else
            x->pai->dir = y;

        y->esq = x;
        x->pai = y;
    }

    void rotacaoDir(NoRB<T>* x) {
        NoRB<T>* y = x->esq;
        x->esq = y->dir;

        if (y->dir != nullptr)
            y->dir->pai = x;

        y->pai = x->pai;

        if (x->pai == nullptr)
            root = y;
        else if (x == x->pai->dir)
            x->pai->dir = y;
        else
            x->pai->esq = y;

        y->dir = x;
        x->pai = y;
    }

    void fixViolacao(NoRB<T>*& pt) {
        NoRB<T>* pai_pt = nullptr;
        NoRB<T>* avo_pt = nullptr;

        while ((pt != root) && (pt->cor != 0) && (pt->pai->cor == 1)) {
            pai_pt = pt->pai;
            avo_pt = pt->pai->pai;

            if (pai_pt == avo_pt->esq) {
                NoRB<T>* tio_pt = avo_pt->dir;

                if (tio_pt != nullptr && tio_pt->cor == 1) {
                    avo_pt->cor = 1;
                    pai_pt->cor = 0;
                    tio_pt->cor = 0;
                    pt = avo_pt;
                } else {
                    if (pt == pai_pt->dir) {
                        rotacaoEsq(pai_pt);
                        pt = pai_pt;
                        pai_pt = pt->pai;
                    }

                    rotacaoDir(avo_pt);
                    std::swap(pai_pt->cor, avo_pt->cor);
                    pt = pai_pt;
                }
            } else {
                NoRB<T>* tio_pt = avo_pt->esq;

                if (tio_pt != nullptr && tio_pt->cor == 1) {
                    avo_pt->cor = 1;
                    pai_pt->cor = 0;
                    tio_pt->cor = 0;
                    pt = avo_pt;
                } else {
                    if (pt == pai_pt->esq) {
                        rotacaoDir(pai_pt);
                        pt = pai_pt;
                        pai_pt = pt->pai;
                    }

                    rotacaoEsq(avo_pt);
                    std::swap(pai_pt->cor, avo_pt->cor);
                    pt = pai_pt;
                }
            }
        }

        root->cor = 0;
    }

    void removerNo(NoRB<T>*& pt, const T& valor) {
        if (pt == nullptr)
            return;

        if (valor < pt->info) {
            removerNo(pt->esq, valor);
        } else if (valor > pt->info) {
            removerNo(pt->dir, valor);
        } else {
            if (pt->esq == nullptr || pt->dir == nullptr) {
                NoRB<T>* temp = pt->esq ? pt->esq : pt->dir;

                if (temp == nullptr) {
                    temp = pt;
                    pt = nullptr;
                } else {
                    *pt = *temp;
                }

                delete temp;
            } else {
                NoRB<T>* temp = minimo(pt->dir);
                pt->info = temp->info;
                removerNo(pt->dir, temp->info);
            }
        }

        if (pt == nullptr)
            return;

        if (pt->esq == nullptr || pt->dir == nullptr) {
            if (pt->esq == nullptr) {
                NoRB<T>* filho = pt->dir;
                substituir(pt, pt->dir);
                deleteFixUp(filho);
            } else {
                NoRB<T>* filho = pt->esq;
                substituir(pt, pt->esq);
                deleteFixUp(filho);
            }

            delete pt;
            pt = nullptr;
        } else {
            NoRB<T>* sucessor = minimo(pt->dir);
            pt->info = sucessor->info;
            removerNo(pt->dir, sucessor->info);
        }
    }

    NoRB<T>* minimo(NoRB<T>* pt) {
        while (pt->esq != nullptr)
            pt = pt->esq;

        return pt;
    }

    void substituir(NoRB<T>* antigo, NoRB<T>* novo) {
        if (antigo->pai == nullptr)
            root = novo;
        else if (antigo == antigo->pai->esq)
            antigo->pai->esq = novo;
        else
            antigo->pai->dir = novo;

        if (novo != nullptr)
            novo->pai = antigo->pai;
    }

    void deleteFixUp(NoRB<T>* pt) {
        if (pt == nullptr)
            return;

        while (pt != root && pt->cor == 0) {
            if (pt == pt->pai->esq) {
                NoRB<T>* irmao = pt->pai->dir;

                if (irmao->cor == 1) {
                    irmao->cor = 0;
                    pt->pai->cor = 1;
                    rotacaoEsq(pt->pai);
                    irmao = pt->pai->dir;
                }

                if (irmao->esq->cor == 0 && irmao->dir->cor == 0) {
                    irmao->cor = 1;
                    pt = pt->pai;
                } else {
                    if (irmao->dir->cor == 0) {
                        irmao->esq->cor = 0;
                        irmao->cor = 1;
                        rotacaoDir(irmao);
                        irmao = pt->pai->dir;
                    }

                    irmao->cor = pt->pai->cor;
                    pt->pai->cor = 0;
                    irmao->dir->cor = 0;
                    rotacaoEsq(pt->pai);
                    pt = root;
                }
            } else {
                NoRB<T>* irmao = pt->pai->esq;

                if (irmao->cor == 1) {
                    irmao->cor = 0;
                    pt->pai->cor = 1;
                    rotacaoDir(pt->pai);
                    irmao = pt->pai->esq;
                }

                if (irmao->dir->cor == 0 && irmao->esq->cor == 0) {
                    irmao->cor = 1;
                    pt = pt->pai;
                } else {
                    if (irmao->esq->cor == 0) {
                        irmao->dir->cor = 0;
                        irmao->cor = 1;
                        rotacaoEsq(irmao);
                        irmao = pt->pai->esq;
                    }

                    irmao->cor = pt->pai->cor;
                    pt->pai->cor = 0;
                    irmao->esq->cor = 0;
                    rotacaoDir(pt->pai);
                    pt = root;
                }
            }
        }

        pt->cor = 0;
    }

    NoRB<T>* inserirRec(NoRB<T>* raiz, NoRB<T>* pt) {
        if (raiz == nullptr)
            return pt;

        if (pt->info < raiz->info) {
            raiz->esq = inserirRec(raiz->esq, pt);
            raiz->esq->pai = raiz;
        } else if (pt->info > raiz->info) {
            raiz->dir = inserirRec(raiz->dir, pt);
            raiz->dir->pai = raiz;
        }

        return raiz;
    }

    NoRB<T>* buscarRec(NoRB<T>* raiz, const T& valor) {
        perf.get_counter().increment_comparisons();
        if (raiz == nullptr || raiz->info == valor){
            
            return raiz;
        }
       
        perf.get_counter().increment_comparisons();
        if (valor < raiz->info){
            
            return buscarRec(raiz->esq, valor);
        }
        return buscarRec(raiz->dir, valor);
    }

public:

    Perf::Performance perf;

    unsigned int getPer(){
        return perf.get_counter().get_comparisons();
    }


    RBTree() : root(nullptr) {}

    NoRB<T>* getRoot() const {
        return root;
    }

    void inserir(const T& valor) {
        NoRB<T>* pt = new NoRB<T>(valor);

        root = inserirRec(root, pt);

        fixViolacao(pt);
    }

    void remover(const T& valor) {
        removerNo(root, valor);
    }

    NoRB<T>* buscar(const T& valor) {
        return buscarRec(root, valor);
    }
    
};

#endif /* RB_TREE_H */