// BIBLIOTECAS //
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// GLOBAL //
ofstream ARQ_ESCRITA;
ifstream ARQ_LEITURA;
const int TAM_VETOR_USERS = 100;


// STRUCTS //
struct Usuarios{
    int id;
    string nome;
    string email;
    string senha;

};


// FUNÇÕES //
void ciarConta(Usuarios users){
    ARQ_ESCRITA.open("usuarios.txt", ofstream::out);


   
}

// FUNÇÃO MAIN //
int main(){

    bool desligar = true; // desligar programa
    int escolhaLogin;

    Usuarios users[TAM_VETOR_USERS];

    while(desligar == true){
        cin >> escolhaLogin;

        switch (escolhaLogin)
        {
        case 1: // Fazer login
                
            break;

        case 2: // Criar conta
            
        break;

        case 0: // sair
            desligar = false;
            break;
        
        default:
            cout << "opção invalida!" << endl;
            break;
        }
    }

    return 0;
}