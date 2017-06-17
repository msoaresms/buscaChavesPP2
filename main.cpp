#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;
const int TAM = 787;
//----------------------------------------------------------------------------------------------------------------------
int tamanho(string pLinha) {
    int i = 0;
    while (pLinha[i] != '\0'){
        i++;
    }
    return i;
}

// Adiciona zeros as chaves com menos de 4 caracteres
string consertar(string pLinha){
    int tam = tamanho(pLinha);
    if (tam == 3){
        char c1 = pLinha[0];
        char c2 = pLinha[1];
        char c3 = pLinha[2];
        pLinha = "0";
        pLinha += c1;
        pLinha += c2;
        pLinha += c3;
    } else if (tam == 2){
        char c1 = pLinha[0];
        char c2 = pLinha[1];
        pLinha = "00";
        pLinha += c1;
        pLinha += c2;
    } else if (tam == 1){
        char c1 = pLinha[0];
        pLinha = "000";
        pLinha += c1;
    }
    return pLinha;
}

// Calcula o valor de hash
int valorHash(string pLinha){
    int hash = 0;
    int j = 3;
    for ( int i = 0; i < 4; i++){
        int aux = pLinha[i];
        hash = hash + (aux * pow(128, j));
        j--;
    }
    return (hash % TAM);
}

// Transforma a string em um vetor de caracteres puro para ser usado pela função atoi()
void stringParaChar(string pLinha, char * chave){
    pLinha = consertar(pLinha);
    chave[0] = pLinha[0];
    chave[1] = pLinha[1];
    chave[2] = pLinha[2];
    chave[3] = pLinha[3];
    chave[4] = '\0';
}
//----------------------------------------------------------------------------------------------------------------------
class Item{
private:
    int chave;
    string valor;
public:
    Item(){};
    Item(int pChave, string pValor){
        this->chave = pChave;
        this->valor = pValor;
    }

    int getChave() {
        return this->chave;
    }
    void setChave(int pChave) {
        this->chave = pChave;
    }
    string getValor() {
        return this->valor;
    }
    void setValor(string pValor) {
        this->valor = pValor;
    }
};
//----------------------------------------------------------------------------------------------------------------------
template <class T>
class No{
private:
    T item;
    No<T> *prox;
public:
    T getItem() {
        return this->item;
    }
    void setItem(T pItem) {
        this->item = pItem;
    }
    No<T> *getProx() {
        return this->prox;
    }
    void setProx(No<T> *pProx) {
        this->prox = pProx;
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
    bool repetido(int pChave){
        No<T> * aux = this->prim->getProx();
        while(aux != NULL){
            if (aux->getItem().getChave() == pChave){
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

    No<T> *getFrente() {
        return this->prim;
    }
    void setFrente(No<T> *pFrente) {
        this->prim = pFrente;
    }
    No<T> *getTras() {
        return this->ult;
    }
    void setTras(No<T> *pTras) {
        this->ult = pTras;
    }

    void insere(T);
    void remove(int, T *);
    No<T> * busca(int);
    Lista<T> ordena();

    void print();
};

template <typename T>
void Lista<T>::insere(T pItem) {
    if (!repetido(pItem.getChave())) {
        this->ult->setProx(new No<T>());
        this->ult = this->ult->getProx();
        this->ult->setItem(pItem);
        this->ult->setProx(NULL);
    }
}

template <typename T>
No<T> * Lista<T>::busca(int pChave) {
    No<T> *aux = this->prim->getProx();
    while (aux != NULL){
        if (aux->getItem().getChave() == pChave){
            return aux;
        }
        aux = aux->getProx();
    }
    return NULL;
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
void Lista<T>::print() {
    No<T> *aux = this->prim->getProx();
    while (aux != NULL){
        cout << aux->getItem().getValor() << " ";
        aux = aux->getProx();
    }
}

template <typename T>
Lista<T> Lista<T>::ordena(){
    Lista<T> lAux;
    while(!this->vazia()){
        T x;
        No<T> *aux1 = this->prim->getProx();
        No<T> *aux2 = this->prim->getProx();
        while (aux1 != NULL){
            if (aux1->getItem().getChave() < aux2->getItem().getChave()){
                aux2 = aux1;
            }
            aux1 = aux1->getProx();
        }
        this->remove(aux2->getItem().getChave(), &x);
        lAux.insere(x);
    }
    return lAux;
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
    void insere(Item);
    void remove(char *, T *);
    void busca(char *);
};

template <typename T>
void Hash<T>::insere(Item pItem) {
    int vHash = valorHash(pItem.getValor());
    Lista<T> *aux = tabela[vHash];
    aux->insere(pItem);
}

template <typename T>
void Hash<T>::busca(char *pChave) {
    int vHash = valorHash(pChave);
    int nAux = atoi(pChave);
    Lista<T> *aux = tabela[vHash];

    if (aux->busca(nAux) == NULL){
        printf("Chave n%co encontrada.", 198);
    } else {
        *aux = aux->ordena();
        aux->print();
    }
}

template <typename T>
void Hash<T>::remove(char *pChave,  T * pItem) {
    int vHash = valorHash(pChave);
    int nAux = atoi(pChave);
    Lista<T> *aux = tabela[vHash];

    if (aux->busca(nAux) == NULL){
        printf("Chave n%co encontrada.", 198);
    } else {
        aux->remove(nAux, pItem);
    }
}
//----------------------------------------------------------------------------------------------------------------------
int main() {
    Hash<Item> tabela;
    string entrada = "";
    char chave[5];
    string teste;
    string teste2;


    // Adiciona os valores a tabela hash
    ifstream arquivo;
    arquivo.open("chaves.txt");
    if (!arquivo){
        cout << "NUM PRESTOU" << endl;
    } else {
        string aux;
        while (arquivo >> aux){
            stringParaChar(aux, chave);
            int nAux = atoi(chave);
            Item pItem(nAux, chave);
            tabela.insere(pItem);
        }
    }
    arquivo.close();
    //----------------------------------

    getline(cin, entrada);
    stringParaChar(entrada, chave);
    tabela.busca(chave);

    return 0;
}