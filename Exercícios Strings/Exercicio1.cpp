#include <iostream>
#include <windows.h>
#include <locale.h> 

using namespace std;

void gotoxy ( short x, short y )
{
  COORD coord = {x, y};
  SetConsoleCursorPosition ( GetStdHandle ( STD_OUTPUT_HANDLE ), coord );
}

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "");
	string mensagem;
	cout << "Digite a mensagem a ser exibida: ";
	getline(cin, mensagem);
	system("cls");

    int colunaInicial = (120 - mensagem.size()) / 2;
    
    gotoxy(colunaInicial, 5);
    cout << mensagem;
    Sleep(2000);
    
	for (int i = 0; i < mensagem.size(); i++) {
    	gotoxy(colunaInicial+i, 5);
    	cout << " ";
    	gotoxy(colunaInicial+i, 20);
        cout << mensagem.at(i);;
        Sleep(400);
    }
    
	return 0;
}
