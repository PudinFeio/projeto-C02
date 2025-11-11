// BIBLIOTECAS //
#include <iostream> // Entrada e saida de dados
#include <string>   // Tipo string
#include <fstream> // Leitura e escrita de arquivos
#include <unistd.h> // Fornece o sleep() -- biblioteca apenas para mac e linux
#include <cstdlib> // Fornece o system()

using namespace std;

// CORES UNIX//
#define TXT_VERMELHO "\033[31m"
#define TXT_BRANCO "\033[0m"
#define TXT_VERDE "\033[32m"
#define TXT_AMARELO "\033[33m"
#define TXT_AZUL "\033[34m"

// GLOBAIS //
const string NOME_ARQUIVO  = "usuarios.txt";
const int TAM_VETOR_USERS = 100;

// STRUCTS //
struct Usuarios {
    int id;
    string nome;
    string email;
    string senha;
};

// FUNÇÕES //
void limpar() {
    sleep(2);
    system("clear");
}
