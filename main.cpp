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
class Chave{
private:
    int chave;
    string valor;
public:
    Chave(){};
    Chave(int pChave, string pValor){
        this->chave = pChave;
        this->valor = pValor;
    }

    int getChave() const {
        return chave;
    }
    void setChave(int chave) {
        Chave::chave = chave;
    }
    const string &getValor() const {
        return valor;
    }
    void setValor(const string &valor) {
        Chave::valor = valor;
    }
};
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
    bool busca(int);

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
bool Lista<T>::busca(int pChave) {
    No<T> *aux = this->prim->getProx();
    while (aux != NULL){
        if (aux->getItem() == pChave){
            return true;
        }
        aux = aux->getProx();
    }
    return false;
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
    void insere(char *);
    void remove(int);
    void busca(char *);
};

template <typename T>
void Hash<T>::insere(char * pChave) {
    int vHash = valorHash(pChave);
    int nAux = atoi(pChave);
    Lista<T> *aux = tabela[vHash];
    aux->insere(nAux);
}
template <typename T>
void Hash<T>::busca(char * pChave) {
    int vHash = valorHash(pChave);
    int nAux = atoi(pChave);
    Lista<T> *aux = tabela[vHash];
    if (aux->busca(nAux)){
        aux->print();
    } else {
        printf("Chave n%co encontrada.", 198);
    }
}
//----------------------------------------------------------------------------------------------------------------------
int main() {
    Hash<int> tabela;
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
            tabela.insere(chave);
        }
    }
    arquivo.close();
    //----------------------------------

    getline(cin, entrada);
    stringParaChar(entrada, chave);

    tabela.busca(chave);

    return 0;
}