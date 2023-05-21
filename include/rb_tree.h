#ifndef RB_TREE_H
#define RB_TREE_H

// TODO: Implementar a árvore rubro-negra aqui e classes auxiliares (se necessário)

#include <iostream>

template <typename T>
class RBTree;

template <typename T>
class No {
private:
    T info;
    No<T>* esq;
    No<T>* dir;
    No<T>* pai;
    bool cor; // 1 para vermelho, 0 para preto

public:
    No(const T& valor) : info(valor), esq(nullptr), dir(nullptr), pai(nullptr), cor(1) {}

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

    bool getCor() const {
        return cor;
    }

    friend class RBTree<T>;
};

template <typename T>
class RBTree {
private:
    No<T>* root;

    void rotacaoEsq(No<T>* x) {
        No<T>* y = x->dir;
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

    void rotacaoDir(No<T>* x) {
        No<T>* y = x->esq;
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

    void fixViolacao(No<T>*& pt) {
        No<T>* pai_pt = nullptr;
        No<T>* avo_pt = nullptr;

        while ((pt != root) && (pt->cor != 0) && (pt->pai->cor == 1)) {
            pai_pt = pt->pai;
            avo_pt = pt->pai->pai;

            if (pai_pt == avo_pt->esq) {
                No<T>* tio_pt = avo_pt->dir;

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
                No<T>* tio_pt = avo_pt->esq;

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

    void removerNo(No<T>*& pt, const T& valor) {
        if (pt == nullptr)
            return;

        if (valor < pt->info) {
            removerNo(pt->esq, valor);
        } else if (valor > pt->info) {
            removerNo(pt->dir, valor);
        } else {
            if (pt->esq == nullptr || pt->dir == nullptr) {
                No<T>* temp = pt->esq ? pt->esq : pt->dir;

                if (temp == nullptr) {
                    temp = pt;
                    pt = nullptr;
                } else {
                    *pt = *temp;
                }

                delete temp;
            } else {
                No<T>* temp = minimo(pt->dir);
                pt->info = temp->info;
                removerNo(pt->dir, temp->info);
            }
        }

        if (pt == nullptr)
            return;

        if (pt->esq == nullptr || pt->dir == nullptr) {
            if (pt->esq == nullptr) {
                No<T>* filho = pt->dir;
                substituir(pt, pt->dir);
                deleteFixUp(filho);
            } else {
                No<T>* filho = pt->esq;
                substituir(pt, pt->esq);
                deleteFixUp(filho);
            }

            delete pt;
            pt = nullptr;
        } else {
            No<T>* sucessor = minimo(pt->dir);
            pt->info = sucessor->info;
            removerNo(pt->dir, sucessor->info);
        }
    }

    No<T>* minimo(No<T>* pt) {
        while (pt->esq != nullptr)
            pt = pt->esq;

        return pt;
    }

    void substituir(No<T>* antigo, No<T>* novo) {
        if (antigo->pai == nullptr)
            root = novo;
        else if (antigo == antigo->pai->esq)
            antigo->pai->esq = novo;
        else
            antigo->pai->dir = novo;

        if (novo != nullptr)
            novo->pai = antigo->pai;
    }

    void deleteFixUp(No<T>* pt) {
        if (pt == nullptr)
            return;

        while (pt != root && pt->cor == 0) {
            if (pt == pt->pai->esq) {
                No<T>* irmao = pt->pai->dir;

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
                No<T>* irmao = pt->pai->esq;

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

public:
    RBTree() : root(nullptr) {}

    No<T>* getRoot() const {
        return root;
    }

    void inserir(const T& valor) {
        No<T>* pt = new No<T>(valor);

        root = inserirRec(root, pt);

        fixViolacao(pt);
    }

    void remover(const T& valor) {
        removerNo(root, valor);
    }

    No<T>* buscar(const T& valor) {
        return buscarRec(root, valor);
    }

private:
    No<T>* inserirRec(No<T>* raiz, No<T>* pt) {
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

    No<T>* buscarRec(No<T>* raiz, const T& valor) {
        if (raiz == nullptr || raiz->info == valor)
            return raiz;

        if (valor < raiz->info)
            return buscarRec(raiz->esq, valor);

        return buscarRec(raiz->dir, valor);
    }
};

#endif /* RB_TREE_H */