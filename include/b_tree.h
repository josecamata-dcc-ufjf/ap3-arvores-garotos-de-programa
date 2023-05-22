#ifndef B_TREE_H
#define B_TREE_H

//TODO: Implemenatar a árvore B aqui e classes auxiliares (se necessário)

#include <iostream>
#include <vector>
#include "perf.h"

template <typename T>
class ArvoreB;

template <typename T>
class NoB {
public:
    bool folha;
    std::vector<T> chaves;
    std::vector<NoB*> filhos;

    NoB(bool folha) : folha(folha) {}

    ~NoB() {
        for (auto* filho : filhos) {
            delete filho;
        }
    }
};

template <typename T>
class ArvoreB {
private:
    int ordem;
    NoB<T>* raiz;

public:

    Perf::Performance perf;

    unsigned int getComp(){
        return perf.get_counter().get_comparisons();
    }

    unsigned int getRota(){
        return perf.get_counter().get_swaps();
    }


    ArvoreB(int ordem) : ordem(ordem), raiz(nullptr) {}

    ~ArvoreB() {
        delete raiz;
    }

    void inserir( T chave) {
        if (raiz == nullptr) {
            raiz = new NoB<T>(true);
            raiz->chaves.push_back(chave);
        } else {
            if (raiz->chaves.size() == 2 * ordem - 1) {
                NoB<T>* novoNo = new NoB<T>(false);
                novoNo->filhos.push_back(raiz);
                dividirFilho(novoNo, 0, raiz);
                inserirNaoCheio(novoNo, chave);
                raiz = novoNo;
            } else {
                inserirNaoCheio(raiz, chave);
            }
        }
    }

    bool buscar( T chave)  {
        return buscarRecursivo(raiz, chave);
    }

    void remover( T chave) {
        if (!raiz) {
            std::cout << "A árvore está vazia!" << std::endl;
            return;
        }

        removerRecursivo(raiz, chave);

        if (raiz->chaves.empty() && !raiz->filhos.empty()) {
            NoB<T>* antigaRaiz = raiz;
            raiz = raiz->filhos[0];
            antigaRaiz->filhos.clear();
            delete antigaRaiz;
        }
    }

private:
    void inserirNaoCheio(NoB<T>* no,  T& chave) {
        int i = no->chaves.size() - 1;

        if (no->folha) {
            no->chaves.resize(no->chaves.size() + 1);
            while (i >= 0 && chave < no->chaves[i]) {
                no->chaves[i + 1] = no->chaves[i];
                i--;
            }
            no->chaves[i + 1] = chave;
        } else {
            while (i >= 0 && chave < no->chaves[i]) {
                i--;
            }

            i++;

            if (no->filhos[i]->chaves.size() == 2 * ordem - 1) {
                dividirFilho(no, i, no->filhos[i]);
                if (chave > no->chaves[i]) {
                    i++;
                }
            }

            inserirNaoCheio(no->filhos[i], chave);
        }
    }

    void dividirFilho(NoB<T>* pai, int indice, NoB<T>* filho) {
        NoB<T>* novoNo = new NoB<T>(filho->folha);
        novoNo->chaves.reserve(ordem - 1);

        for (int j = 0; j < ordem - 1; j++) {
            novoNo->chaves.push_back(filho->chaves[j + ordem]);
        }

        if (!filho->folha) {
            novoNo->filhos.reserve(ordem);
            for (int j = 0; j < ordem; j++) {
                novoNo->filhos.push_back(filho->filhos[j + ordem]);
            }
        }

        filho->chaves.resize(ordem - 1);

        if (!filho->folha) {
            filho->filhos.resize(ordem);
        }

        pai->chaves.insert(pai->chaves.begin() + indice, filho->chaves[ordem - 1]);
        pai->filhos.insert(pai->filhos.begin() + indice + 1, novoNo);
        filho->chaves.pop_back();
    }

    bool buscarRecursivo( NoB<T>* no,  T& chave)  {
        int i = 0;
        while (i < no->chaves.size() && chave > no->chaves[i]) {
            perf.get_counter().increment_comparisons();
            i++;
        }
        perf.get_counter().increment_comparisons();
        if (i < no->chaves.size() && chave == no->chaves[i]) {
            return true;
        }
        if (no->folha) {
            return false;
        }
        return buscarRecursivo(no->filhos[i], chave);
    }

    void removerRecursivo(NoB<T>* no,  T& chave) {
        int indice = 0;
        while (indice < no->chaves.size() && chave > no->chaves[indice]) {
            indice++;
        }

        if (indice < no->chaves.size() && chave == no->chaves[indice]) {
            if (no->folha) {
                no->chaves.erase(no->chaves.begin() + indice);
            } else {
                removerChaveNaoFolha(no, indice);
            }
        } else {
            if (no->folha) {
                std::cout << "A chave " << chave << " não foi encontrada na árvore!" << std::endl;
                return;
            }

            bool ultimaChave = (indice == no->chaves.size());
            NoB<T>* filho = no->filhos[indice];

            if (filho->chaves.size() < ordem) {
                preencher(filho, indice);
            }

            if (ultimaChave && indice > no->chaves.size()) {
                removerRecursivo(no->filhos[indice - 1], chave);
            } else {
                removerRecursivo(no->filhos[indice], chave);
            }
        }
    }

    void removerChaveNaoFolha(NoB<T>* no, int indice) {
        T chave = no->chaves[indice];

        if (no->filhos[indice]->chaves.size() >= ordem) {
            T predecessor = obterPredecessor(no, indice);
            no->chaves[indice] = predecessor;
            removerRecursivo(no->filhos[indice], predecessor);
        } else if (no->filhos[indice + 1]->chaves.size() >= ordem) {
            T sucessor = obterSucessor(no, indice);
            no->chaves[indice] = sucessor;
            removerRecursivo(no->filhos[indice + 1], sucessor);
        } else {
            NoB<T>* filhoEsquerda = no->filhos[indice];
            NoB<T>* filhoDireita = no->filhos[indice + 1];

            filhoEsquerda->chaves.push_back(chave);
            filhoEsquerda->filhos.reserve(filhoEsquerda->filhos.size() + filhoDireita->filhos.size() + 1);

            for ( auto& ch : filhoDireita->chaves) {
                filhoEsquerda->chaves.push_back(ch);
            }

            for ( auto& f : filhoDireita->filhos) {
                filhoEsquerda->filhos.push_back(f);
            }

            no->chaves.erase(no->chaves.begin() + indice);
            no->filhos.erase(no->filhos.begin() + indice + 1);

            delete filhoDireita;

            if (no->chaves.empty() && !no->filhos.empty()) {
                NoB<T>* antigoNo = no;
                no = filhoEsquerda;
                antigoNo->filhos.clear();
                delete antigoNo;
            }

            removerRecursivo(filhoEsquerda, chave);
        }
    }

    T obterPredecessor( NoB<T>* no, int indice)  {
        NoB<T>* atual = no->filhos[indice];
        while (!atual->folha) {
            atual = atual->filhos[atual->filhos.size() - 1];
        }
        return atual->chaves[atual->chaves.size() - 1];
    }

    T obterSucessor( NoB<T>* no, int indice)  {
        NoB<T>* atual = no->filhos[indice + 1];
        while (!atual->folha) {
            atual = atual->filhos[0];
        }
        return atual->chaves[0];
    }

    void preencher(NoB<T>* no, int indice) {
        if (indice != 0 && no->filhos[indice - 1]->chaves.size() >= ordem) {
            emprestarAnterior(no, indice);
        } else if (indice != no->chaves.size() && no->filhos[indice + 1]->chaves.size() >= ordem) {
            emprestarProximo(no, indice);
        } else {
            if (indice != no->chaves.size()) {
                fundir(no, indice);
            } else {
                fundir(no, indice - 1);
            }
        }
    }

    void emprestarAnterior(NoB<T>* no, int indice) {
        NoB<T>* filho = no->filhos[indice];
        NoB<T>* irmao = no->filhos[indice - 1];

        filho->chaves.insert(filho->chaves.begin(), no->chaves[indice - 1]);
        no->chaves[indice - 1] = irmao->chaves[irmao->chaves.size() - 1];
        irmao->chaves.pop_back();

        if (!filho->folha) {
            filho->filhos.insert(filho->filhos.begin(), irmao->filhos[irmao->filhos.size() - 1]);
            irmao->filhos.pop_back();
        }
    }

    void emprestarProximo(NoB<T>* no, int indice) {
        NoB<T>* filho = no->filhos[indice];
        NoB<T>* irmao = no->filhos[indice + 1];

        filho->chaves.push_back(no->chaves[indice]);
        no->chaves[indice] = irmao->chaves[0];
        irmao->chaves.erase(irmao->chaves.begin());

        if (!filho->folha) {
            filho->filhos.push_back(irmao->filhos[0]);
            irmao->filhos.erase(irmao->filhos.begin());
        }
    }

    void fundir(NoB<T>* no, int indice) {
        NoB<T>* filho = no->filhos[indice];
        NoB<T>* irmao = no->filhos[indice + 1];

        filho->chaves.push_back(no->chaves[indice]);
        filho->chaves.reserve(2 * ordem - 1);

        for ( auto& ch : irmao->chaves) {
            filho->chaves.push_back(ch);
        }

        if (!filho->folha) {
            filho->filhos.reserve(2 * ordem);
            for ( auto& f : irmao->filhos) {
                filho->filhos.push_back(f);
            }
        }

        no->chaves.erase(no->chaves.begin() + indice);
        no->filhos.erase(no->filhos.begin() + indice + 1);

        delete irmao;
    }
};



#endif /* B_TREE_H */
