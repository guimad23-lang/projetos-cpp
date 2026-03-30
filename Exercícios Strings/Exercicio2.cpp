#include <iostream>
#include <string>

using namespace std;

int main() {
    
	string mensagem, textoLimpo;

    cout << "Digite a mensagem para verificacao de palindromo: ";
    getline(cin, mensagem);

    for (int i = 0; i < mensagem.size(); i++) {
        if (mensagem[i] != ' ') {
            textoLimpo += mensagem[i]; 
        }
    }

    bool verificaPalindromo = true;
    
    for (int i = 0; i < textoLimpo.size() / 2; i++) {
        if (textoLimpo[i] != textoLimpo[textoLimpo.size() - 1 - i]) {
            verificaPalindromo = false; 
            break; 
        }
    }
    
    cout << "Texto tratado: " << textoLimpo << endl;
    if (verificaPalindromo) cout << "A MENSAGEM CONFIGURA UM PALINDROMO!" << endl;
    else cout << "Nao eh um palindromo." << endl;

    return 0;
}