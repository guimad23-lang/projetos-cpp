#include <iostream>
#include <limits>

using namespace std;

class PilhaVetor {
private:
    int elementos[30];
    int topo;
public:
    PilhaVetor() {
        topo = -1;
    }
    void empilhar(int valor) {
        if (topo < 29) elementos[++topo] = valor;                 
    }
    int desempilhar() {
        if (!vazia()) return elementos[topo--];
        return -1;
    }
    int espiar() {
        if (!vazia()) return elementos[topo];
        return -1;
    }
    bool vazia(){ 
        return topo == -1;
    }
};

struct No {
    int valor;
    No* proximo;
};

class PilhaLista {
private:
    No* topo;
public:
    PilhaLista() { 
        topo = nullptr; 
    }
    void empilhar(int valor) {
        No* novoNo = new No();
        novoNo->valor = valor;
        novoNo->proximo = topo;
        topo = novoNo;
    }
    int desempilhar() {
        if (!vazia()) {
            int valor = topo->valor;
            No* temp = topo;
            topo = topo->proximo;
            delete temp;
            return valor;
        }
        return -1;
    }
    int espiar() {
        if (!vazia()) { return topo->valor; }
        return -1;
    }
    bool vazia() {
        return topo == nullptr;
    }
};

int main() {
    PilhaVetor pilhaPares;
    PilhaLista pilhaImpares;
    const int QUANTIDADE = 30;
    int numeroAtual;
    int numeroAnterior = numeric_limits<int>::min();

    cout << "=== ENTRADA DE DADOS ===" << endl;
    cout << "Digite " << QUANTIDADE << " numeros inteiros em ordem crescente." << endl;
    for (int i = 0; i < QUANTIDADE; i++) {
        cout << "Digite o " << i + 1 << "o numero: ";
        cin >> numeroAtual;
        while (numeroAtual <= numeroAnterior && i > 0) {
            cout << "Erro! O numero deve ser maior que o anterior (" << numeroAnterior << ").\n";
            cout << "Digite novamente o " << i + 1 << "o numero: ";
            cin >> numeroAtual;
        }
        numeroAnterior = numeroAtual;
        if (numeroAtual % 2 == 0) pilhaPares.empilhar(numeroAtual);
        else pilhaImpares.empilhar(numeroAtual);
    }

    cout << "\n=== SAIDA DE DADOS (ORDEM DECRESCENTE) ===" << endl;

    while (!pilhaPares.vazia() || !pilhaImpares.vazia()) {
        if (pilhaPares.vazia()) cout << pilhaImpares.desempilhar() << " ";
        else if (pilhaImpares.vazia()) cout << pilhaPares.desempilhar() << " ";
        else {
            if (pilhaPares.espiar() > pilhaImpares.espiar()) {
                cout << pilhaPares.desempilhar() << " ";
            } 
            else cout << pilhaImpares.desempilhar() << " ";
        }
    }
    cout << endl;
    return 0;
}
