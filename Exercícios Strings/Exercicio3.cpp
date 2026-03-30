#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream arquivoLeitura("nomes.txt");
    string conteudoFinal = "";
    
    if (arquivoLeitura.is_open()) {
        string linha;
        
        while (getline(arquivoLeitura, linha)) {
            if (linha.empty()) continue;
            
            size_t ultimoEspaco = linha.find_last_of(" ");
            
            if (ultimoEspaco != string::npos) 
			{
                string ultimoNome = linha.substr(ultimoEspaco + 1);
                string restoNome = linha.substr(0, ultimoEspaco);

                conteudoFinal += ultimoNome + ", " + restoNome + "\n";
            } 
			else conteudoFinal += linha + "\n";
        }
        
        arquivoLeitura.close();
        
        ofstream arquivoGravacao("nomes.txt");
        
        if (arquivoGravacao.is_open()) 
		{
            arquivoGravacao << conteudoFinal;
            arquivoGravacao.close();
            
            cout << "Sucesso! O arquivo foi atualizado." << endl;
        } 
		else cout << "Erro ao tentar gravar no arquivo." << endl;
        
    } 
	else cout << "Erro ao abrir o arquivo para leitura. Ele existe na pasta?" << endl;
    
    return 0;
}