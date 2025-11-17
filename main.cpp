// BIBLIOTECAS //
#include <iostream> // Entrada e saida de dados
#include <string>   // Tipo string
#include <fstream> // Leitura e escrita de arquivos
#include <unistd.h> // Fornece o sleep() -- biblioteca apenas para mac e linux
#include <cstdlib> // Fornece o system()
#include <filesystem> // Para iterar arquivos .wav
using namespace std;
namespace fs = std::filesystem;

// CORES UNIX//
#define TXT_VERMELHO "\033[31m"
#define TXT_BRANCO "\033[0m"
#define TXT_VERDE "\033[32m"
#define TXT_AMARELO "\033[33m"
#define TXT_AZUL "\033[34m"

// GLOBAIS //
ofstream ARQ_ESCRITA;
ifstream ARQ_LEITURA;

const string USERS_DB  = "usuarios.txt";
const int TAM_VETOR_USERS = 100;
const int MAX_NOTAS = 26;

// STRUCTS //
struct Usuarios {
    int id;
    string nome;
    string email;
    string senha;
};

// TOCAR MÚSICA //


void tocarSom(const string &arquivo){ // Toca O som via aplay
    string cmd = "aplay -q \"" + arquivo + "\" &";

    system(cmd.c_str());
}

struct Nota {
    string arquivo;
    int tempo; // milissegundos
};

// Tocar música
void tocarMusica(Nota musica[], int tamanho){
    for(int i = 0; i < tamanho; i++){
        tocarSom(musica[i].arquivo);
        usleep(musica[i].tempo * 1000); // ms → microseconds
    }
}

int carregarAcordes(const string &pasta, string arquivos[], string nomes[]){ // Carregar arquivos WAV
    int total = 0;

    for(const auto &entry : fs::directory_iterator(pasta)){
        if(entry.path().extension() == ".wav"){
            arquivos[total] = entry.path().string();
            nomes[total] = entry.path().stem().string();
            total++;
            if(total >= MAX_NOTAS) break;
        }
    }
    return total;
}

void mostrarNotas(char teclas[], string nomes[], int total){ // Mostrar notas
    cout << "\n=== Teclado de Violão ===\n";

    for(int i = 0; i < total; i++){
        cout << teclas[i] << " - " << nomes[i] << "\n";
    }
    cout << "\n0 - Voltar\n";
}

// Modo tocar notas livremente
void modoTocarNotas(string arquivos[], string nomes[], int total){
    char teclas[MAX_NOTAS];

    for(int i = 0; i < total; i++)
        teclas[i] = 'A' + i;

    system("clear");
    mostrarNotas(teclas, nomes, total);

    cout << "\nDigite letras A-Z e pressione ENTER para tocar.\n";
    cout << "Digite 0 e ENTER para voltar.\n";

    char tecla;
    while(true){
        cout << "\nNota: ";
        cin >> tecla;

        if(tecla == '0'){
            break;
        }
        tecla = toupper(tecla);

        for(int i = 0; i < total; i++){
            if(tecla == teclas[i]){
                tocarSom(arquivos[i]);
            }
        }
    }
}

void modoTocarMusica(const string& pasta){ // Músicas prontas
    Nota brilha[] = {
        {pasta+"/do.wav",275},{pasta+"/do.wav",275},
        {pasta+"/sol.wav",275},{pasta+"/sol.wav",275},
        {pasta+"/la.wav",275},{pasta+"/la.wav",275},
        {pasta+"/sol.wav",525},{pasta+"/fa.wav",275},
        {pasta+"/fa.wav",275},{pasta+"/mi.wav",275},
        {pasta+"/mi.wav",275},{pasta+"/re.wav",275},
        {pasta+"/re.wav",275},{pasta+"/do.wav",525}
    };
    int tamanho = sizeof(brilha)/sizeof(brilha[0]);

    char opc;
    do {
        cout << "\n1 - Brilha Brilha Estrelinha\n";
        cout << "0 - Voltar\n";
        cout << "Escolha: ";
        cin >> opc;

        if(opc == '1'){
            cout << "\nTocando...\n";
            tocarMusica(brilha, tamanho);
        }
    } while(opc != '0');
}

// FUNÇÕES EXISTENTES //
void limpar() {
    sleep(2);
    system("clear");
}

int pegar_ultimoID(){
    ARQ_LEITURA.open(USERS_DB, ofstream::in);

    int ultimoID = 0;
    int idTemp;
    string nome, email, senha;

    while(ARQ_LEITURA >> idTemp){
        ARQ_LEITURA.ignore();
        getline(ARQ_LEITURA, nome);
        getline(ARQ_LEITURA, email);
        getline(ARQ_LEITURA, senha);
        ultimoID = idTemp;
    }
    ARQ_LEITURA.close();
    return ultimoID + 1;
}

bool email_ja_existe(string emailProcurado){
    ARQ_LEITURA.open(USERS_DB, ofstream::in);

    int id;
    string nome, email, senha;

    while(ARQ_LEITURA >> id){
        ARQ_LEITURA.ignore();
        getline(ARQ_LEITURA, nome);
        getline(ARQ_LEITURA, email);
        getline(ARQ_LEITURA, senha);
        if(email == emailProcurado){
            ARQ_LEITURA.close();
            return true;
        }
    }
    ARQ_LEITURA.close();
    return false;
}

bool criar_conta(Usuarios users[], int &total){
    Usuarios usr;

    usr.id = pegar_ultimoID();

    system("clear");

    cout << "\n   === BEM VINDO AO MELOMIX ===   " << endl;
    cout << "\nCrie sua conta" << endl;
    cout << "Nome: " << TXT_AMARELO;
    getline(cin, usr.nome);
    cout << TXT_BRANCO;
    cout << "Email: " << TXT_AMARELO;
    getline(cin, usr.email);
    cout << TXT_BRANCO;

    if(email_ja_existe(usr.email)){
        cout << "Este email ja esta cadastrado!" << endl;
        return false;
    }

    cout << "Senha: " << TXT_AMARELO;
    getline(cin, usr.senha);
    cout << TXT_BRANCO;

    users[total] = usr;
    total++;

    ARQ_ESCRITA.open(USERS_DB, ofstream::out);
    ARQ_ESCRITA << usr.id << endl;
    ARQ_ESCRITA << usr.nome << endl;
    ARQ_ESCRITA << usr.email << endl;
    ARQ_ESCRITA << usr.senha << endl;
    ARQ_ESCRITA.close();

    return true;
}

bool fazer_login(Usuarios users[], string &nomeFile){
    string email, senha;

    system("clear");

    cout << "\n   === BEM VINDO AO MELOMIX ===   " << endl;
    cout << "\nFazendo login" << endl;
    cout << "Email: " << TXT_AMARELO;
    getline(cin, email);
    cout << TXT_BRANCO;
    cout << "Senha: " << TXT_AMARELO;
    getline(cin, senha);
    ARQ_LEITURA.open("usuarios.txt");

    int idFile;
    string emailFile, senhaFile;

    while(ARQ_LEITURA >> idFile){
        ARQ_LEITURA.ignore();
        getline(ARQ_LEITURA, nomeFile);
        getline(ARQ_LEITURA, emailFile);
        getline(ARQ_LEITURA, senhaFile);
        if(emailFile == email && senhaFile == senha){
            ARQ_LEITURA.close();
            cout << TXT_VERDE << "\nLogin efetuado com " << TXT_AZUL << "sucesso!" << TXT_BRANCO << endl;

            limpar();

            return true;
        }
    }
    ARQ_LEITURA.close();

    return false;
}

// ==================== MAIN ====================
int main(){

    bool desligar = true; 
    int escolhaLogin;
    string nomeUser;

    Usuarios users[TAM_VETOR_USERS];
    int totalUsers = 0;

    system("clear");

    const string pastaAcordes = "acordes-violao";
    string arquivos[MAX_NOTAS];
    string nomes[MAX_NOTAS];
    int totalNotas = carregarAcordes(pastaAcordes, arquivos, nomes);

    while(desligar){
        cout << "\n   === BEM VINDO AO MELOMIX ===   " << endl;
        cout << "\n1 - Fazer login" << endl;
        cout << "2 - Criar conta" << endl;
        cout << "0 - Sair" << endl;
        cout << "Escolha: " << TXT_AMARELO;
        cin >> escolhaLogin;
        cout << "\n" << TXT_BRANCO;
        cin.ignore();

        switch (escolhaLogin)
        {
        case 1:
            if(fazer_login(users, nomeUser)){
                limpar();

                cout << TXT_BRANCO "\n   === Bem vindo " << TXT_AMARELO << nomeUser << TXT_BRANCO << " ===   " << endl;

                char opcaoMusica;
                while(opcaoMusica != '0') {
                    cout << "\n=== MENU DE MÚSICA ===\n";
                    cout << "1 - Tocar notas livremente\n";
                    cout << "2 - Tocar música pronta (Brilha Brilha Estrelinha)\n";
                    cout << "0 - Voltar\n";
                    cout << "Escolha: ";
                    cin >> opcaoMusica;
                    cin.ignore();

                    switch(opcaoMusica){
                        case '1':
                            modoTocarNotas(arquivos, nomes, totalNotas);
                            break;
                        case '2':
                            modoTocarMusica(pastaAcordes);
                            break;
                        case '0':
                            break;
                        default:
                            cout << TXT_VERMELHO << "Opção inválida!" << TXT_BRANCO << endl;
                            usleep(800000);
                    }
                }

            }else{
                cout << TXT_VERMELHO << "\nFalha no login!" << TXT_BRANCO << endl;
                limpar();
            }
            break;

        case 2:
            if(criar_conta(users, totalUsers)){
                cout << TXT_VERDE << "\nConta criada com sucesso!" << TXT_BRANCO << endl;
                limpar();
            } else {
                cout << TXT_VERMELHO << "\nErro ao criar conta!" << TXT_BRANCO << endl;
                limpar();
            }
            break;

        case 0:
            cout << TXT_AMARELO <<" Saindo..." << TXT_BRANCO << endl;
            desligar = false;
            limpar();
            break;

        default:
            cout << TXT_VERMELHO <<"Opção inválida!" << TXT_BRANCO << endl;
            limpar();
            break;
        }
    }

    return 0;
}
