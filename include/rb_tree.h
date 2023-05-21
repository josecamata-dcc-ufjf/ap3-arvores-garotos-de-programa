#ifndef RB_TREE_H
#define RB_TREE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "rb_node.h"

using namespace std;

// TODO: Implementar a árvore rubro-negra aqui e classes auxiliares (se necessário)

namespace BRtree{

template <typename T>
class RedBlackTree{ 
    public:
        RedBlackTree();
        ~RedBlackTree();

        void insert(T info);
        void remove(T value);
        bool busca(T value);
        No<T>* minimo(No<T>* raiz);
        No<T>* maximo(No<T>* raiz);
        int sucessor(No<T>* x);
        int predecessor(No<T>* x);
        void rotacaoDir(No<T>* x);
        void rotacaoEsq(No<T>* x);
        T   get_root_value(){ return root->getInfo();};
        void imprime();

    private:
        void limpa(No<T> *node);
        void auxInsert(No<T>* k);   
        //void auxDelete(No<T>* x);
        bool auxBusca(No<T>* node, int key);
        void removerNo(No<T>* pt, T value);
        void auxImprime(No<T>* root, string indent, bool last);
        void deleteFixUp(No<T>* pt);
        void substituir(No<T>* antigo, No<T>* novo);

        // Ponteiro para o no raiz da arvore
        No<T>* root;
        
};

// Cria um RedBlackTree vazia
template <typename T>
RedBlackTree<T>::RedBlackTree(): root(nullptr)
{ }

//deleta
template <typename T>
RedBlackTree<T>::~RedBlackTree()
{
    limpa(root);
    root = nullptr;
}

//limpa
template <typename T>
void RedBlackTree<T>::limpa(No<T> *node)
{
    if (node == nullptr)
    {
        return;
    }
    limpa(node->esq);
    limpa(node->dir);
    delete node;
}

template <typename T>
void RedBlackTree<T>::imprime() {
	    if (root) {
    		auxImprime(this->root, "", true);
	    }
	}

template <typename T>
void RedBlackTree<T>::auxImprime(No<T>* root, string indent, bool last) {
		// print the tree structure on the screen
	   	if (root != NULL) 
        {
		   cout<<indent;
		   if (last) {
		      cout<<"R----";
		      indent += "     ";
		   } else {
		      cout<<"L----";
		      indent += "|    ";
		   }
            
           string sColor = root->cor?"RED":"BLACK";
		   cout<<root->info<<"("<<sColor<<")"<<endl;
		   auxImprime(root->esq, indent, false);
		   auxImprime(root->dir, indent, true);
		}
		// cout<<root->left->data<<endl;
	}

template <typename T>
void RedBlackTree<T>::insert(T info) {
    // cria no
    No<T>* node = new No<T>();
    node->pai = nullptr;
    node->info = info;
    node->esq = NULL;
    node->dir = NULL;
    node->cor = 1; // vermelho

    No<T>* y = nullptr;
    No<T>* x = this->root;

    while (x != NULL) {
        y = x;
        if (node->info < x->info) {
            x = x->esq;
        } else {
            x = x->dir;
        }
    }

    
    node->pai = y;
    if(y == nullptr) 
    {
        root = node;
    } 
    else if(node->info < y->info)
    {
        y->esq = node;
    }
    else 
    {
        y->dir = node;
    }

    // se for Raiz
    if (node->pai == nullptr){
        node->cor = 0;
        return;
    }

    //se avo e null
    if (node->pai->pai == nullptr) {
        return;
    }

    auxInsert(node);
}

template <typename T>
void RedBlackTree<T>::auxInsert(No<T>* k){
    No<T>* u;
    while (k->pai->cor == 1) {
        if(k->pai == k->pai->pai->dir) 
        {
            u = k->pai->pai->esq; //se for tio
            if(u->cor == 1) 
            {
                u->cor = 0;
                k->pai->cor = 0;
                k->pai->pai->cor = 1;
                k = k->pai->pai;
            } 
            else 
            {
                if(k == k->pai->esq) 
                {
                    k = k->pai;
                    rotacaoDir(k);
                }
                k->pai->cor = 0;
                k->pai->pai->cor = 1;
                rotacaoEsq(k->pai->pai);
            }
        } 
        else 
        {
            u = k->pai->pai->dir;

            if(u->cor == 1) 
            {
                u->cor = 0;
                k->pai->cor = 0;
                k->pai->pai->cor = 1;
                k = k->pai->pai;	
            } 
            else 
            {
                if(k == k->pai->dir) 
                {
                    k = k->pai;
                    rotacaoEsq(k);
                }
                k->pai->cor = 0;
                k->pai->pai->cor = 1;
                rotacaoDir(k->pai->pai);
            }
        }
        if(k == root) 
        {
            break;
        }
    }
    root->cor = 0;
}

template <typename T>
void RedBlackTree<T>::remove( T value) {
    removerNo(root, value);
}


template <typename T>
void RedBlackTree<T>::removerNo(No<T>* pt, T value) {
        if (pt == nullptr)
            return;

        if (value < pt->info) {
            removerNo(pt->esq, value);
        } else if (value > pt->info) {
            removerNo(pt->dir, value);
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

template <typename T>
void RedBlackTree<T>::deleteFixUp(No<T>* pt) {
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
            } else 
            {
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

template <typename T>
void RedBlackTree<T>::substituir(No<T>* antigo, No<T>* novo) {
        if (antigo->pai == nullptr)
            root = novo;
        else if (antigo == antigo->pai->esq)
            antigo->pai->esq = novo;
        else
            antigo->pai->dir = novo;

        if (novo != nullptr)
            novo->pai = antigo->pai;
    }



/*
template <typename T>
void RedBlackTree<T>::auxDelete(No<T>* x) {
    No<T>* s;
    while (x != root && x->cor == 0) {
        if (x == x->pai->esq) {
            s = x->pai->dir;
            if(s->cor == 1) 
            {
                s->cor = 0;
                x->pai->cor = 1;
                rotacaoEsq(x->pai);
                s = x->pai->dir;
            }

            if (s->esq->cor == 0 && s->dir->cor == 0) 
            {
                s->cor = 1;
                x = x->pai;
            } else {
                if(s->dir->cor == 0) 
                {
                    s->esq->cor = 0;
                    s->cor = 1;
                    rotacaoDir(s);
                    s = x->pai->dir;
                } 

                s->cor = x->pai->cor;
                x->pai->cor = 0;
                s->dir->cor = 0;
                rotacaoEsq(x->pai);
                x = root;
            }
        } else {
            s = x->pai->esq;
            if(s->cor == 1) 
            {
                s->cor = 0;
                x->pai->cor = 1;
                rotacaoDir(x->pai);
                s = x->pai->esq;
            }

            if(s->dir->cor == 0 && s->dir->cor == 0) 
            {
                s->cor = 1;
                x = x->pai;
            } 
            else 
            {
                if(s->esq->cor == 0) 
                {
                    s->dir->cor = 0;
                    s->cor = 1;
                    rotacaoEsq(s);
                    s = x->pai->esq;
                }
                s->cor = x->pai->cor;
                x->pai->cor = 0;
                s->esq->cor = 0;
                rotacaoDir(x->pai);
                x = root;
            }
        } 
    }
    x->cor = 0;
}
*/

template <typename T>
bool RedBlackTree<T>::busca(T value) {
    return auxBusca(this->root, value);
}

template <typename T>
bool RedBlackTree<T>::auxBusca(No<T>* node, int value) {
		if(node == NULL || value == node->info) 
        {
			return true;
		}
		if(value < node->getInfo()) 
        {
			return auxBusca(node->esq, value);
		} 
		return auxBusca(node->dir, value);
	}

template <typename T>
No<T>* RedBlackTree<T>::minimo(No<T>* raiz) {
    No<T>* node = raiz;
    while(node->esq != NULL) 
    {
        node = node->esq;
    }
    return node;
}

template <typename T>
No<T>* RedBlackTree<T>::maximo(No<T>* raiz) {
    No<T> node = raiz;
    while(node->dir != NULL) 
    {
        node = node->dir;
    }
    return node;
}

template <typename T>
int RedBlackTree<T>::sucessor(No<T>* x) {
    if(x->dir != NULL) 
    {
        return minimo(x->dir);
    }

    No<T>* y = x->pai;
    while(y != NULL && x == y->dir) 
    {
        x = y;
        y = y->pai;
    }
    return y->getInfo();
}

template <typename T>
int RedBlackTree<T>::predecessor(No<T>* x) {
    if(x->esq != NULL) 
    {
        return maximo(x->esq);
    }

    No<T>* y = x->pai;
    while(y != NULL && x == y->esq) 
    {
        x = y;
        y = y->pai;
    }

    return y->getInfo();
}

template <typename T>
void RedBlackTree<T>::rotacaoDir(No<T>* x) {
    No<T>* y = x->esq;
    x->esq = y->dir;
    if(y->dir != NULL) 
    {
        y->dir->pai = x;
    }
    y->pai = x->pai;
    if(x->pai == nullptr) 
    {
        this->root = y;
    } 
    else if(x == x->pai->dir) 
    {
        x->pai->dir = y;
    } 
    else
    {
        x->pai->esq = y;
    }
    y->dir = x;
    x->pai = y;
}

template <typename T>
void RedBlackTree<T>::rotacaoEsq(No<T>* x) {
    No<T>* y = x->dir;
    x->dir = y->esq;
    if(y->esq != NULL) 
    {
        y->esq->pai = x;
    }
    y->pai = x->pai;
    if(x->pai == nullptr)
    {
        this->root = y;
    } 
    else if(x == x->pai->esq) 
    {
        x->pai->esq = y;
    } 
    else 
    {
        x->pai->dir = y;
    }
    y->esq = x;
    x->pai = y;
}



}

#endif /* RB_TREE_H */
