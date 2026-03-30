#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

int main() {
    ifstream arquivoLeitura("nomes.txt");
    string conteudoFinal = ""; 
    
    if (arquivoLeitura.is_open()) {
        string linha;
        
        while (getline(arquivoLeitura, linha)) 
		{
            
			size_t ultimoEspaco = linha.find_last_of(" ");
            
			string ultimoNome = linha.substr(ultimoEspaco + 1);
			string restoNome = linha.substr(0, ultimoEspaco);
                
            string ultimoNomeMaiusculo = "";
			for (size_t i = 0; i < ultimoNome.size(); i++) ultimoNomeMaiusculo += toupper(ultimoNome[i]);
                
			size_t primeiroEspaco = restoNome.find_first_of(" ");
                
			string nomeFormatado = ultimoNomeMaiusculo + ", ";
                
			if (primeiroEspaco != string::npos) 
			{
                    string primeiroNome = restoNome.substr(0, primeiroEspaco);
					nomeFormatado += primeiroNome + " ";

                    
					for (size_t i = primeiroEspaco + 1; i < restoNome.size(); i++) 
					{
						if (restoNome[i] != ' ' && restoNome[i-1] == ' ') 
						{
						nomeFormatado += toupper(restoNome[i]);
						nomeFormatado += ". ";
						}
					}
                    
					if (nomeFormatado[nomeFormatado.size() - 1] == ' ') nomeFormatado = nomeFormatado.substr(0, nomeFormatado.size() - 1);
            		else nomeFormatado += restoNome;
			   
					conteudoFinal += nomeFormatado + "\n";    
			}
        
		arquivoLeitura.close();
        
        ofstream arquivoGravacao("nomes.txt");
        if (arquivoGravacao.is_open()) 
		{
            arquivoGravacao << conteudoFinal;
            arquivoGravacao.close();
            cout << "Sucesso! Nomes formatados para citacao bibliografica." << endl;
        } 
		else cout << "Erro ao tentar atualizar o arquivo." << endl;
     
		}
	}   
	else cout << "Erro ao abrir o arquivo 'nomes.txt'." << endl;
    
    return 0;
}