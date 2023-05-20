#ifndef B_TREE_H
#define B_TREE_H

//TODO: Implemenatar a árvore B aqui e classes auxiliares (se necessário)
#include <iostream>
using namespace std;

// Definição do grau mínimo da árvore B
const int MIN_DEGREE = 3;

// Definição da classe Node
class Node {
    int *keys;  // Array de chaves armazenadas no nó
    int degree; // Número de chaves atualmente no nó
    Node **children; // Array de ponteiros para filhos
    bool leaf;  // Indica se o nó é uma folha
public:
    Node(bool leaf);

    void insertNonFull(int key);
    void splitChild(int i, Node *child);
    void traverse();
    Node *search(int key);
    void remove(int key);
    int findKeyIndex(int key);
    void removeFromLeaf(int index);
    void removeFromNonLeaf(int index);
    int getPredecessor(int index);
    int getSuccessor(int index);
    void fillChild(int index);
    void borrowFromPrevious(int index);
    void borrowFromNext(int index);
    void mergeChildren(int index);
    friend class BTree;
};

// Definição da classe BTree
class BTree {
    Node *root; // Ponteiro para a raiz da árvore B
public:
    BTree();
    void traverse();
    Node* search(int key);
    void insert(int key);
    void remove(int key);
};

// Implementação dos métodos da classe Node
Node::Node(bool leaf) {
    this->leaf = leaf;
    keys = new int[2 * MIN_DEGREE - 1];
    children = new Node *[2 * MIN_DEGREE];
    degree = 0;
}

void Node::insertNonFull(int key) {
    int i = degree - 1;

    if (leaf) {
        while (i >= 0 && keys[i] > key) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = key;
        degree++;
    } else {
        while (i >= 0 && keys[i] > key)
            i--;
        if (children[i + 1]->degree == 2 * MIN_DEGREE - 1) {
            splitChild(i + 1, children[i + 1]);
            if (keys[i + 1] < key)
                i++;
        }
        children[i + 1]->insertNonFull(key);
    }
}

void Node::splitChild(int i, Node *child) {
    Node *newChild = new Node(child->leaf);
    newChild->degree = MIN_DEGREE - 1;

    for (int j = 0; j < MIN_DEGREE - 1; j++)
        newChild->keys[j] = child->keys[j + MIN_DEGREE];

    if (!child->leaf) {
        for (int j = 0; j < MIN_DEGREE; j++)
            newChild->children[j] = child->children[j + MIN_DEGREE];
    }

    child->degree = MIN_DEGREE - 1;

    for (int j = degree; j >= i + 1; j--)
        children[j + 1] = children[j];

    children[i + 1] = newChild;

    for (int j = degree - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    keys[i] = child->keys[MIN_DEGREE - 1];

    degree++;
}

void Node::traverse() {
    int i;
    for (i = 0; i < degree; i++) {
        if (!leaf)
            children[i]->traverse();
        cout << " " << keys[i];
    }

    if (!leaf)
        children[i]->traverse();
}

Node *Node::search(int key) {
    int i = 0;
    while (i < degree && key > keys[i])
        i++;

    if (keys[i] == key)
        return this;

    if (leaf)
        return nullptr;

    return children[i]->search(key);
}

// Implementação dos métodos da classe BTree
BTree::BTree() {
    root = nullptr;
}

void BTree::traverse() {
    if (root != nullptr)
        root->traverse();
}

Node* BTree::search(int key) {
    if (root == nullptr)
        return nullptr;

    return root->search(key);
}

void BTree::insert(int key) {
    if (root == nullptr) {
        root = new Node(true);
        root->keys[0] = key;
        root->degree = 1;
    } else {
        if (root->degree == 2 * MIN_DEGREE - 1) {
            Node *newRoot = new Node(false);
            newRoot->children[0] = root;
            newRoot->splitChild(0, root);
            int i = 0;
            if (newRoot->keys[0] < key)
                i++;
            newRoot->children[i]->insertNonFull(key);
            root = newRoot;
        } else {
            root->insertNonFull(key);
        }
    }
}

void Node::remove(int key) {
    int index = findKeyIndex(key);

    // A chave a ser removida está presente neste nó
    if (index < degree && keys[index] == key) {
        if (leaf) {
            // Caso 1: Remoção em um nó folha
            removeFromLeaf(index);
        } else {
            // Caso 2: Remoção em um nó não folha
            removeFromNonLeaf(index);
        }
    } else {
        if (leaf) {
            // A chave a ser removida não está presente na árvore
            cout << "A chave " << key << " não existe na árvore." << endl;
            return;
        }

        // A chave a ser removida está presente em algum nó filho
        bool isLastChild = (index == degree);
        Node *child = children[index];

        if (child->degree < MIN_DEGREE) {
            // Caso 3: O filho que contém a chave a ser removida tem menos do que MIN_DEGREE chaves
            fillChild(index);

            // Se o último filho foi fundido, então o ponteiro do filho anterior precisa ser atualizado
            if (isLastChild && index > degree)
                children[index - 1] = children[index];

            // Recursivamente remover a chave do filho atualizado
            children[index]->remove(key);
        } else {
            // Caso 4: O filho que contém a chave a ser removida tem pelo menos MIN_DEGREE chaves
            // Portanto, a remoção pode ser realizada recursivamente no filho
            children[index]->remove(key);
        }
    }
}

int Node::findKeyIndex(int key) {
    int index = 0;
    while (index < degree && keys[index] < key)
        ++index;
    return index;
}

void Node::removeFromLeaf(int index) {
    // Remover a chave do nó folha
    for (int i = index + 1; i < degree; ++i)
        keys[i - 1] = keys[i];
    --degree;
}

void Node::removeFromNonLeaf(int index) {
    int key = keys[index];

    // Caso 2a: Substituir a chave pelo maior elemento na subárvore esquerda
    if (children[index]->degree >= MIN_DEGREE) {
        int predecessor = getPredecessor(index);
        keys[index] = predecessor;
        children[index]->remove(predecessor);
    }
    // Caso 2b: Substituir a chave pelo menor elemento na subárvore direita
    else if (children[index + 1]->degree >= MIN_DEGREE) {
        int successor = getSuccessor(index);
        keys[index] = successor;
        children[index + 1]->remove(successor);
    }
    // Caso 2c: Fundir o nó filho que contém a chave a ser removida com o próximo nó filho
    else {
        mergeChildren(index);
        children[index]->remove(key);
    }
}

int Node::getPredecessor(int index) {
    Node *current = children[index];
    while (!current->leaf)
        current = current->children[current->degree];
    return current->keys[current->degree - 1];
}

int Node::getSuccessor(int index) {
    Node *current = children[index + 1];
    while (!current->leaf)
        current = current->children[0];
    return current->keys[0];
}

void Node::fillChild(int index) {
    // Se o filho anterior tem pelo menos MIN_DEGREE chaves, empreste uma chave dele
    if (index != 0 && children[index - 1]->degree >= MIN_DEGREE)
        borrowFromPrevious(index);
    // Se o próximo filho tem pelo menos MIN_DEGREE chaves, empreste uma chave dele
    else if (index != degree && children[index + 1]->degree >= MIN_DEGREE)
        borrowFromNext(index);
    // Caso contrário, fundir o filho com seu próximo irmão
    else {
        if (index != degree)
            mergeChildren(index);
        else
            mergeChildren(index - 1);
    }
}

void Node::borrowFromPrevious(int index) {
    Node *child = children[index];
    Node *sibling = children[index - 1];

    // Mover todas as chaves em child uma posição para a frente
    for (int i = child->degree - 1; i >= 0; --i)
        child->keys[i + 1] = child->keys[i];

    // Se child não é uma folha, mover todos os ponteiros de filho em uma posição para a frente
    if (!child->leaf) {
        for (int i = child->degree; i >= 0; --i)
            child->children[i + 1] = child->children[i];
    }

    // Definir a primeira chave de child como a chave do nó atual
    child->keys[0] = keys[index - 1];

    // Mover a última chave do irmão para o nó atual
    keys[index - 1] = sibling->keys[sibling->degree - 1];

    // Se sibling não é uma folha, mover o último ponteiro de filho do irmão para child
    if (!sibling->leaf)
        child->children[0] = sibling->children[sibling->degree];

    // Atualizar o grau de child e sibling
    ++child->degree;
    --sibling->degree;
}

void Node::borrowFromNext(int index) {
    Node *child = children[index];
    Node *sibling = children[index + 1];

    // Definir a última chave de child como a chave do nó atual
    child->keys[child->degree] = keys[index];

    // Se child não é uma folha, mover o primeiro ponteiro de filho do irmão para child
    if (!child->leaf)
        child->children[child->degree + 1] = sibling->children[0];

    // Mover a primeira chave do irmão para o nó atual
    keys[index] = sibling->keys[0];

    // Mover todas as chaves em sibling uma posição para trás
    for (int i = 1; i < sibling->degree; ++i)
        sibling->keys[i - 1] = sibling->keys[i];

    // Se sibling não é uma folha, mover todos os ponteiros de filho em uma posição para trás
    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->degree; ++i)
            sibling->children[i - 1] = sibling->children[i];
    }

    // Atualizar o grau de child e sibling
    ++child->degree;
    --sibling->degree;
}

void Node::mergeChildren(int index) {
    Node *child = children[index];
    Node *sibling = children[index + 1];

    // Mover a chave do nó atual para o filho junto com todas as chaves do irmão
    child->keys[MIN_DEGREE - 1] = keys[index];
    for (int i = 0; i < sibling->degree; ++i)
        child->keys[i + MIN_DEGREE] = sibling->keys[i];

    // Se child não é uma folha, mover todos os ponteiros de filho do irmão para child
    if (!child->leaf) {
        for (int i = 0; i <= sibling->degree; ++i)
            child->children[i + MIN_DEGREE] = sibling->children[i];
    }

    // Mover todas as chaves após a posição index uma posição para trás no nó atual
    for (int i = index + 1; i < degree; ++i)
        keys[i - 1] = keys[i];

    // Mover todos os ponteiros de filho após a posição index uma posição para trás no nó atual
    for (int i = index + 2; i <= degree; ++i)
        children[i - 1] = children[i];

    // Atualizar o grau de child
    child->degree += sibling->degree + 1;

    // Atualizar o grau do nó atual
    --degree;

    // Liberar memória alocada para o irmão
    delete sibling;
}

// Implementação dos métodos da classe BTree
void BTree::remove(int key) {
    if (!root) {
        cout << "A árvore está vazia." << endl;
        return;
    }

    root->remove(key);

    // Se a raiz ficar vazia após a remoção, atualize a raiz
    if (root->degree == 0) {
        Node *tmp = root;
        if (root->leaf)
            root = nullptr;
        else
            root = root->children[0];
        delete tmp;
    }


    
}

    

#endif /* B_TREE_H */
