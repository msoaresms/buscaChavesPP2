#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

template <class T>
class No{
private:
    T item;
    No<T> *prox;
public:
    const T &getItem() const {
        return item;
    }
    void setItem(const T &item) {
        this->item = item;
    }
    No<T> *getProx() const {
        return prox;
    }
    void setProx(No<T> *prox) {
        this->prox = prox;
    }
};

template <class T>
class Lista{
private:
    No<T> *prim, *ult;
    bool vazia(){
        return (this->prim == this->ult);
    }
    No<T> *predecessor(No<T> *no){
        No<T> *aux = this->prim;
        while (aux->getProx() != no){
            aux = aux->getProx();
        }
        return aux;
    }
public:
    Lista(){
        this->prim = new No<T>();
        this->prim->setProx(NULL);
        this->ult = this->prim;
    }

    No<T> *getFrente() const {
        return prim;
    }
    void setFrente(No<T> *frente) {
        Lista::prim = frente;
    }
    No<T> *getTras() const {
        return ult;
    }
    void setTras(No<T> *tras) {
        Lista::ult = tras;
    }

    void insere(T);
    void remove(int, T *);
    No<T> *busca(int);
};

template <class T>
class Hash{
private:
    Lista<T> * tabela[15];
public:
    Hash(){
        for (int i = 0; i < 15; i++){
            this->tabela[i] = new Lista<T>();
        }
    }
    void insere(int);
    void remove();
    void busca();
};

template <typename T>
void Hash<T>::insere(int pChave) {
    Lista<T> *aux = tabela[pChave % 15];
    aux->insere(pChave);
}

template <typename T>
void Lista<T>::insere(T pItem) {
    this->ult->setProx(new No<T>());
    this->ult = this->ult->getProx();
    this->ult->setItem(pItem);
    this->ult->setProx(NULL);
}

template <typename T>
void Lista<T>::remove(int pChave, T *x) {
    if (!this->vazia()) {
        No<T> *aux = this->busca(pChave);
        if (aux != NULL){
            *x = aux->getItem();
            No<T> *p = this->predecessor(aux);
            p->setProx(aux->getProx());
            delete aux;
            if (p->getProx() == NULL){
                this->ult = p;
            }
        }
    }
}

template <typename T>
No<T> *Lista<T>::busca(int pChave) {
    No<T> *aux = this->prim->getProx();
    while (aux != NULL && aux->getItem().getChave() != pChave){
        aux = aux->getProx();
    }
    return aux;
}

int main() {
    //int chaves[15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    Hash<int> tabela;

    string line;
    ifstream keys;
    keys.open("chaves.txt");

    int i = 0;
    while (!keys.eof()){
        getline(keys, line);
        stringstream aux(line);
        int nAux;
        aux >> nAux;
        tabela.insere(nAux);
    }
    keys.close();



    return 0;
}