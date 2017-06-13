#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
const int TAM = 787;
//----------------------------------------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------------------------------------
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
    bool repetido(T pChave){
        No<T> * aux = this->prim->getProx();
        while(aux != NULL){
            if (aux->getItem() == pChave){
                return true;
            }
            aux = aux->getProx();
        }
        return false;
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

    void print();
};

template <typename T>
void Lista<T>::insere(T pItem) {
    if (!repetido(pItem)) {
        this->ult->setProx(new No<T>());
        this->ult = this->ult->getProx();
        this->ult->setItem(pItem);
        this->ult->setProx(NULL);
    }
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

template <typename T>
void Lista<T>::print() {
    No<T> *aux = this->prim->getProx();
    while (aux != NULL){
        cout << aux->getItem() << " ";
        aux = aux->getProx();
    }
}
//----------------------------------------------------------------------------------------------------------------------
template <class T>
class Hash{
private:
    Lista<T> * tabela[TAM];
public:
    Hash(){
        for (int i = 0; i < TAM; i++){
            this->tabela[i] = new Lista<T>();
        }
    }
    void insere(int);
    void remove(int);
    void busca(int);
};

template <typename T>
void Hash<T>::insere(int pChave) {
    Lista<T> *aux = tabela[pChave % TAM];
    aux->insere(pChave);
}
template <typename T>
void Hash<T>::busca(int pChave) {
    Lista<T> *aux = tabela[pChave % TAM];
    aux->print();
}
//-----------------------------------
int main() {
    Hash<int> tabela;

    ifstream arquivo;
    arquivo.open("chaves.txt");

    if (!arquivo){
        cout << "NUM PRESTOU" << endl;
    } else {
        string line;
        while (getline(arquivo, line)){
            stringstream aux(line);
            int nAux;
            aux >> nAux;
            tabela.insere(nAux);
        }
    }
    arquivo.close();

    tabela.busca(9808);

    return 0;
}