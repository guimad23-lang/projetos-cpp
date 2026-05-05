/* À partir da estrutura "Funcionario" descrita abaixo:

------------------
| Funcionario       |
|-------------------|
| - prontuario: int |
| - nome: string    |
| - salario: double |
---------------------
Elabore um programa que permita administrar uma lista de funcionários e, através de um menu, ofereça as seguintes opções:

   0. Sair
   1. Incluir
   2. Excluir
   3. Pesquisar
   4. Listar
   
OBSERVAÇÕES:

a) Não poderão ser cadastrados funcionários com mesmo prontuário;

b) A pesquisa de funcionário deverá utilizar o atributo "Prontuário" como critério e, quando encontrado, deverão ser exibidos os demais atributos;

c) A listagem dos funcionários deverá apresentar todos os seus atributos e, ao final, informar o total dos salários.

*/

#include <iostream>
#include <string>
using namespace std;

struct Lista
{
	int prontuario;
	string nome;
	double salario; 
	Lista *prox;	
};

Lista* init()
{
	return NULL;
}

int isEmpty(Lista* lista)
{
	return (lista == NULL);
}

Lista* insert(Lista* lista, int pront, string nome, double salario)
{
	Lista* novo = new Lista();
	novo->prontuario = pront;
	novo->nome = nome;
	novo->salario = salario;
	novo->prox = lista;
	return novo;
}

void print(Lista* lista)
{
	Lista* aux;
	aux = lista;
	cout << endl;
	cout << "N | Prontuario | Nome | Salario" << endl;
	cout << "-------------------------------" << endl;
	int contador = 0;
	double soma = 0;
	while(aux != NULL)
	{
		contador++;
		soma += aux->salario;
		cout << contador << " | " << aux->prontuario << " | " << aux->nome << " | " << aux->salario << endl;
		aux = aux->prox;
	}
	cout << endl;
	cout << "Folha de pagamento total: " << soma << endl;
	cout << endl;
}

Lista* find(Lista* lista, int pront)
{
	Lista* aux;
	aux = lista;
    while(aux != NULL && aux->prontuario != pront)
	{
		aux = aux->prox;
	}	
	return aux;
}

Lista* remove(Lista* lista, int pront)
{
	Lista* ant = NULL;
    Lista* aux;
    aux = lista;
    while(aux != NULL && aux->prontuario != pront)
    {
        ant = aux;
        aux = aux->prox;
    }
    if (aux == NULL)
    {
        return lista;
    }
    if (ant == NULL) // era o primeiro
    {
        lista = aux->prox;
    }
    else // estava no meio
    {
        ant->prox = aux->prox;
    }
    delete aux;
    return lista;
}

int main(int argc, char** argv)
{
	Lista *Funcionarios;
	Lista* procurado;
	Funcionarios = init();
	int p, escolha;
	string n;
	double s;
	bool prontuarioRepetido = true;
	
	do{
		cout << "-----------------------------" << endl;
		cout << "ADMINISTRACAO DE FUNCIONARIOS" << endl;
		cout << "-----------------------------" << endl;
		cout << "0. Sair" << endl;
		cout << "1. Incluir" << endl;
		cout << "2. Excluir" << endl;
		cout << "3. Pesquisar" << endl;
		cout << "4. Listar" << endl;
		
		cout << "Digite o comando: " << endl;
		cin >> escolha;
	
		switch(escolha){
			case 0: break;
			case 1: do{
						cout << "Digite o prontuario do novo funcionario: " << endl;
						cin >> p;
						procurado = find(Funcionarios, p);
						if (procurado == NULL) prontuarioRepetido = false;
						else cout << "Este prontuario ja existe. Digite um novo prontuario, por favor." << endl;	
					} while(prontuarioRepetido);
					cout << "Agora insira o nome do novo funcionario: " << endl;
					cin >> n;
					cout << "Informe o salario do novo funcionario: " << endl;
					cin >> s;
					Funcionarios = insert(Funcionarios, p, n, s);
					cout << endl;
					cout << "Funcionario registrado." << endl;
					cout << endl;
					break;
			case 2: cout << "Digite o prontuario do funcionario a ser desligado: " << endl;
					cin >> p;
					if (find(Funcionarios, p) != NULL){
						Funcionarios = remove(Funcionarios, p);
						cout << "Registro excluido com sucesso." << endl;
					} 
					else cout << "Prontuario nao encontrado. Tente novamente." << endl;
					break;
			case 3: cout << "Digite o prontuario do funcionario que deseja pesquisar: " << endl;
					cin >> p;
					procurado = find(Funcionarios, p);
					cout << endl;
					if (procurado == NULL) cout << "Funcionario nao encontrado." << endl;
					else cout << "Funcionario encontrado: " << procurado->nome << " com o salario de " << procurado->salario << endl;
					cout << endl;
					break;
			case 4: print(Funcionarios);
					break;
			default: cout << "Comando invalido." << endl; 				
		}
				
	} while(escolha != 0);
	
	return 0;
}