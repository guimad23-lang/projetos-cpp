#include <iostream>
#include <iomanip>

using namespace std;

const int FILEIRAS = 15;
const int POLTRONAS_POR_FILEIRA = 40;

int main() {

    bool teatro[FILEIRAS][POLTRONAS_POR_FILEIRA] = {false};
    int opcao;

    do {
        cout << "===================================\n";
        cout << "         CONTROLE DO TEATRO        \n";
        cout << "===================================\n";
        cout << "0. Finalizar\n";
        cout << "1. Reservar poltrona\n";
        cout << "2. Mapa de ocupacao\n";
        cout << "3. Faturamento\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 0:
                cout << "\nEncerrando.\n";
                break;

            case 1: { 
                int fileira, poltrona;
                cout << "\nInforme a fileira (1 a 15): ";
                cin >> fileira;
                cout << "Informe a poltrona (1 a 40): ";
                cin >> poltrona;

                if (fileira < 1 || fileira > FILEIRAS || poltrona < 1 || poltrona > POLTRONAS_POR_FILEIRA) {
                    cout << "-> ERRO: Fileira ou poltrona invalida! Tente novamente.\n";
                } else {
                    int indiceFileira = fileira - 1;
                    int indicePoltrona = poltrona - 1;

                    if (teatro[indiceFileira][indicePoltrona]) {
                        cout << "-> AVISO: Este lugar ja se encontra ocupado!\n";
                    } else {
                        teatro[indiceFileira][indicePoltrona] = true;
                        cout << "-> SUCESSO: Poltrona reservada com exito!\n";
                    }
                }
                break;
            }

            case 2: {
                cout << "\n--- MAPA DE OCUPACAO ---\n";
                
                for (int i = 0; i < FILEIRAS; i++) {
                    cout << "F" << setw(2) << i + 1 << ": ";
                    
                    for (int j = 0; j < POLTRONAS_POR_FILEIRA; j++) {
                        if (teatro[i][j]) {
                            cout << "#";
                        } else {
                            cout << ".";
                        }
                    }
                    cout << "\n";
                }
                cout << "\nLegenda: '.' lugar vago | '#' lugar ocupado\n";
                break;
            }

            case 3: {
                int qtdeOcupados = 0;
                double bilheteria = 0.0;

                for (int i = 0; i < FILEIRAS; i++) {
                    for (int j = 0; j < POLTRONAS_POR_FILEIRA; j++) {
                        if (teatro[i][j]) {
                            qtdeOcupados++;
                            
                            if (i >= 0 && i <= 4) {
                                bilheteria += 50.00;
                            } else if (i >= 5 && i <= 9) {
                                bilheteria += 30.00;
                            } else {
                                bilheteria += 15.00;
                            }
                        }
                    }
                }

                cout << "\n--- FATURAMENTO ---\n";
                cout << "Qtde de lugares ocupados:\t" << qtdeOcupados << "\n";
                cout << fixed << setprecision(2); 
                cout << "Valor da bilheteria:\t\tR$ " << bilheteria << "\n";
                break;
            }

            default:
                cout << "\n-> Opcao invalida! Escolha um numero de 0 a 3.\n";
        }

    } while (opcao != 0);

    return 0;
}