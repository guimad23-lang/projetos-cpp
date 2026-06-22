#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// =======================================================
// ESTRUTURAS DE DADOS
// =======================================================

// Estrutura para os nós das Filas de Senhas
struct NoSenha {
    int senha;
    NoSenha* proximo;
};

// Estrutura da Fila de Senhas (usada tanto para geradas quanto para atendidas)
struct FilaSenhas {
    NoSenha* inicio;
    NoSenha* fim;
    int tamanho;
};

// Estrutura do Nó da Lista de Guichês
struct NoGuiche {
    int id;
    FilaSenhas senhasAtendidas; // Cada guichê tem sua própria fila de senhas
    NoGuiche* proximo;
};

// Estrutura da Lista de Guichês
struct ListaGuiches {
    NoGuiche* inicio;
    int tamanho;
};

// =======================================================
// FUNÇÕES PARA A FILA DE SENHAS
// =======================================================

void inicializarFila(FilaSenhas &f) {
    f.inicio = NULL;
    f.fim = NULL;
    f.tamanho = 0;
}

bool filaVazia(const FilaSenhas &f) {
    return f.inicio == NULL;
}

void enfileirar(FilaSenhas &f, int valor) {
    NoSenha* novo = new NoSenha;
    novo->senha = valor;
    novo->proximo = NULL;

    if (filaVazia(f)) {
        f.inicio = novo;
        f.fim = novo;
    } else {
        f.fim->proximo = novo;
        f.fim = novo;
    }
    f.tamanho++;
}

int desenfileirar(FilaSenhas &f) {
    if (filaVazia(f)) return -1;

    NoSenha* aux = f.inicio;
    int valor = aux->senha;

    f.inicio = f.inicio->proximo;
    if (f.inicio == NULL) {
        f.fim = NULL;
    }

    delete aux;
    f.tamanho--;
    return valor;
}

void liberarFila(FilaSenhas &f) {
    while (!filaVazia(f)) {
        desenfileirar(f);
    }
}

// Imprime a fila sem removê-la (apenas varredura)
void imprimirFila(const FilaSenhas &f) {
    NoSenha* aux = f.inicio;
    if (aux == NULL) {
        cout << "Nenhuma senha.";
    }
    while (aux != NULL) {
        // Formata os números apenas para exibição
        string s = to_string(aux->senha);
        while (s.size() < 3) s = "0" + s;
        cout << "S" << s << " ";
        aux = aux->proximo;
    }
    cout << endl;
}

// =======================================================
// FUNÇÕES PARA A LISTA DE GUICHÊS
// =======================================================

void inicializarLista(ListaGuiches &l) {
    l.inicio = NULL;
    l.tamanho = 0;
}

// Busca um guichê pelo ID e retorna o ponteiro dele
NoGuiche* buscarGuiche(ListaGuiches &l, int id) {
    NoGuiche* aux = l.inicio;
    while (aux != NULL) {
        if (aux->id == id) {
            return aux;
        }
        aux = aux->proximo;
    }
    return NULL; // Retorna nulo se não encontrar
}

bool adicionarGuiche(ListaGuiches &l, int id) {
    // Verifica se já existe um guichê com esse ID
    if (buscarGuiche(l, id) != NULL) {
        return false; 
    }

    NoGuiche* novo = new NoGuiche;
    novo->id = id;
    inicializarFila(novo->senhasAtendidas); // Inicializa a fila interna do guichê
    novo->proximo = NULL;

    // Insere no final da lista
    if (l.inicio == NULL) {
        l.inicio = novo;
    } else {
        NoGuiche* aux = l.inicio;
        while (aux->proximo != NULL) {
            aux = aux->proximo;
        }
        aux->proximo = novo;
    }
    l.tamanho++;
    return true;
}

void liberarLista(ListaGuiches &l) {
    NoGuiche* aux = l.inicio;
    while (aux != NULL) {
        NoGuiche* proximo = aux->proximo;
        liberarFila(aux->senhasAtendidas); // Libera a fila interna primeiro
        delete aux;                        // Libera o nó do guichê
        aux = proximo;
    }
    l.inicio = NULL;
    l.tamanho = 0;
}

// =======================================================
// FUNÇÕES UTILITÁRIAS
// =======================================================

string formatarSenha(int n) {
    string s = to_string(n);
    while (s.size() < 3) s = "0" + s;
    return "S" + s;
}

void separador() {
    cout << "========================================" << endl;
}

// =======================================================
// PROGRAMA PRINCIPAL
// =======================================================

int main() {
    FilaSenhas senhasGeradas;
    inicializarFila(senhasGeradas);

    ListaGuiches guichesAbertos;
    inicializarLista(guichesAbertos);

    int contadorSenhas = 0;
    int totalAtendidas = 0; // Controle geral para exibição final
    int opcao = -1;

    do {
        separador();
        cout << "        SISTEMA DE ATENDIMENTO 2.0      " << endl;
        separador();
        cout << "  Senhas aguardando  : " << senhasGeradas.tamanho << endl;
        cout << "  Guiches abertos    : " << guichesAbertos.tamanho << endl;
        separador();
        cout << "  [1] Gerar senha" << endl;
        cout << "  [2] Abrir guiche" << endl;
        cout << "  [3] Realizar atendimento" << endl;
        cout << "  [4] Listar senhas atendidas" << endl;
        cout << "  [0] Sair" << endl;
        cout << "\n  Opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1: { // Gerar senha
                contadorSenhas++;
                enfileirar(senhasGeradas, contadorSenhas);
                cout << "\n  >> Senha " << formatarSenha(contadorSenhas)
                     << " gerada com sucesso e aguardando." << endl;
                break;
            }

            case 2: { // Abrir guichê
                int idGuiche;
                cout << "\n  Digite o ID do novo guiche: ";
                cin >> idGuiche;

                if (adicionarGuiche(guichesAbertos, idGuiche)) {
                    cout << "  >> Guiche " << idGuiche << " aberto com sucesso!" << endl;
                } else {
                    cout << "  >> ERRO: Ja existe um guiche aberto com o ID " << idGuiche << "!" << endl;
                }
                break;
            }

            case 3: { // Realizar atendimento
                if (filaVazia(senhasGeradas)) {
                    cout << "\n  >> Nao ha senhas aguardando atendimento!" << endl;
                    break;
                }
                if (guichesAbertos.tamanho == 0) {
                    cout << "\n  >> Nao ha guiches abertos para realizar atendimento!" << endl;
                    break;
                }

                int idGuiche;
                cout << "\n  Digite o ID do guiche que esta chamando: ";
                cin >> idGuiche;

                NoGuiche* guicheAtual = buscarGuiche(guichesAbertos, idGuiche);

                if (guicheAtual == NULL) {
                    cout << "  >> ERRO: Guiche " << idGuiche << " nao encontrado!" << endl;
                } else {
                    // Remove da fila principal e insere na fila do guichê
                    int senhaAtual = desenfileirar(senhasGeradas);
                    enfileirar(guicheAtual->senhasAtendidas, senhaAtual);
                    totalAtendidas++;

                    cout << "  >> Guiche " << idGuiche << " chamando a senha: " 
                         << formatarSenha(senhaAtual) << endl;
                }
                break;
            }

            case 4: { // Listar senhas atendidas
                int idGuiche;
                cout << "\n  Digite o ID do guiche para listar: ";
                cin >> idGuiche;

                NoGuiche* guicheAtual = buscarGuiche(guichesAbertos, idGuiche);

                if (guicheAtual == NULL) {
                    cout << "  >> ERRO: Guiche " << idGuiche << " nao encontrado!" << endl;
                } else {
                    cout << "\n  Senhas atendidas pelo Guiche " << idGuiche << ":\n  >> ";
                    imprimirFila(guicheAtual->senhasAtendidas);
                }
                break;
            }

            case 0: { // Sair
                if (!filaVazia(senhasGeradas)) {
                    cout << "\n  >> ATENCAO: Ainda ha " << senhasGeradas.tamanho
                         << " senha(s) aguardando atendimento." << endl;
                    cout << "  >> Atenda todas antes de encerrar o sistema." << endl;
                    opcao = -1; // Impede a saída
                }
                break;
            }

            default: {
                cout << "\n  >> Opcao invalida! Tente novamente." << endl;
                break;
            }
        }
        cout << endl;

    } while (opcao != 0);

    // Encerramento
    separador();
    cout << "             SISTEMA ENCERRADO          " << endl;
    cout << "  Total geral de senhas atendidas: " << totalAtendidas << endl;
    separador();

    // Liberação de memória de todas as estruturas dinâmicas
    liberarFila(senhasGeradas);
    liberarLista(guichesAbertos);

    cout << "\n  Pressione ENTER para fechar..." << endl;
    cin.ignore();
    cin.get();

    return 0;
}
