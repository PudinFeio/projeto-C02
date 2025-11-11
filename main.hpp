// BIBLIOTECAS //
#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <cstdlib>

using namespace std;

// CORES //
#define TXT_VERMELHO "\033[31m"
#define TXT_BRANCO "\033[0m"
#define TXT_VERDE "\033[32m"
#define TXT_AMARELO "\033[33m"

// GLOBAIS //
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
