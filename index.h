#ifndef INDEX_H
#define INDEX_H

// BIBLIOTECAS //
#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <chrono>
#include <filesystem>
#include <windows.h>
#include <mmsystem.h>

using namespace std;
namespace fs = std::filesystem;

// GLOBAL //
#define TXT_VERMELHO "\033[31m"
#define TXT_BRANCO "\033[0m"
#define TXT_VERDE "\033[32m"
#define TXT_AMARELO "\033[33m"

// STRUCTS //
struct Usuarios {
    int id;
    string nome;
    string email;
    string senha;
};


// FUNÇÕES //
inline void limpar() {
    this_thread::sleep_for(chrono::seconds(2));
    system("clear");
}

#endif
