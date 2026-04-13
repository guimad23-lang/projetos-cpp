#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class Data {
private:
    int dia;
    int mes;
    int ano;

public:
    Data(int dia, int mes, int ano) {
        this->dia = dia;
        this->mes = mes;
        this->ano = ano;
    }

    Data() {
        this->dia = 0;
        this->mes = 0;
        this->ano = 0;
    }

    void setDia(int dia) { this->dia = dia; }
    void setMes(int mes) { this->mes = mes; }
    void setAno(int ano) { this->ano = ano; }

    int getDia() { return this->dia; }
    int getMes() { return this->mes; }
    int getAno() { return this->ano; }

    string getData() {
        string sdia = to_string(this->dia);
        string smes = to_string(this->mes);
        string sano = to_string(this->ano);
        return sdia.insert(0, 2 - sdia.size(), '0') + "/" + 
               smes.insert(0, 2 - smes.size(), '0') + "/" + 
               sano;
    }

    Data* dia_seguinte() {
        int ultimoDiaDoMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        Data *d1 = new Data(this->dia, this->mes, this->ano);
        
        if (d1->ano % 4 == 0)
            ultimoDiaDoMes[1]++; 
        
        d1->dia++;
        if (d1->dia > ultimoDiaDoMes[d1->mes - 1]) {
            d1->dia = 1;
            d1->mes++;
            if (d1->mes > 12) {
                d1->mes = 1;
                d1->ano++;
            }
        }    
        return d1;
    }
};

class Contato {
private:
    string email;
    string nome;
    string telefone;
    Data dtnasc;

public:
    Contato() {}

    Contato(string nome, string email, string telefone, Data dtnasc) {
        this->nome = nome;
        this->email = email;
        this->telefone = telefone;
        this->dtnasc = dtnasc;
    }

    string getNome() { return this->nome; }
    string getEmail() { return this->email; }
    string getTelefone() { return this->telefone; }
    Data getDtnasc() { return this->dtnasc; }

    void setNome(string nome) { this->nome = nome; }
    void setEmail(string email) { this->email = email; }
    void setTelefone(string telefone) { this->telefone = telefone; }
    void setDtnasc(Data dtnasc) { this->dtnasc = dtnasc; }

    int idade() {
        time_t t = time(nullptr);
        tm* agora = localtime(&t);
        
        // tm_year conta os anos desde 1900, e tm_mon começa do 0 (janeiro)
        int anoAtual = agora->tm_year + 1900;
        int mesAtual = agora->tm_mon + 1;
        int diaAtual = agora->tm_mday;

        int idadeCalc = anoAtual - this->dtnasc.getAno();

        // Subtrai 1 da idade se a pessoa ainda não fez aniversário no ano atual
        if (mesAtual < this->dtnasc.getMes() || 
           (mesAtual == this->dtnasc.getMes() && diaAtual < this->dtnasc.getDia())) {
            idadeCalc--;
        }

        return idadeCalc;
    }
};

int main() {
    const int TAMANHO = 5;
    Contato agenda[TAMANHO];

    cout << "--- CADASTRO DE CONTATOS ---" << endl;

    for (int i = 0; i < TAMANHO; i++) {
        string nome, email, telefone;
        int dia, mes, ano;

        cout << "\nContato " << (i + 1) << ":" << endl;
        
        cout << "Nome: ";
        getline(cin, nome);
        
        cout << "E-mail: ";
        getline(cin, email);
        
        cout << "Telefone: ";
        getline(cin, telefone);
        
        cout << "Data de Nascimento (DD MM AAAA): ";
        cin >> dia >> mes >> ano;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        Data dataNasc(dia, mes, ano);
        agenda[i] = Contato(nome, email, telefone, dataNasc);
    }

    cout << "\n===============================" << endl;
    cout << "      CONTATOS CADASTRADOS       " << endl;
    cout << "===============================" << endl;

    for (int i = 0; i < TAMANHO; i++) {
        cout << "Nome:     " << agenda[i].getNome() << endl;
        cout << "E-mail:   " << agenda[i].getEmail() << endl;
        cout << "Telefone: " << agenda[i].getTelefone() << endl;
        cout << "Idade:    " << agenda[i].idade() << " anos (Nascido em " << agenda[i].getDtnasc().getData() << ")" << endl;
        cout << "-------------------------------" << endl;
    }

    return 0;
}
