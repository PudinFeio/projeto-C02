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
ofstream ARQ_ESCRITA;
ifstream ARQ_LEITURA;

const string USERS_DB  = "usuarios.txt";
const string VIOLAO_DIRETORIO = "melodias/acordes-violao";
const int TAM_VETOR_USERS = 100;
const int MAX_NOTAS = 26;
string PATH;


// STRUCTS //
struct Usuarios {
    int id;
    string nome;
    string email;
    string senha;
};

string command = "xdg-open \"" + PATH + "\"";

// TOCAR MÚSICA //
void escolha_melodia(bool &voltar, int selecao){
    

    if(selecao == 1){
        PATH = "/home/eller/Projects/projeto-C02/acordes-violao/";
        cout  << "oi" << endl;

    }
    else if(selecao == 2){
        PATH = "/home/eller/Projects/projeto-C02/notas-piano/";

    }
    else if(selecao == 3){
        PATH = "/home/eller/Projects/projeto-C02/musicas/";

    }
    else{
        voltar = true;  
        cout << TXT_VERMELHO <<"Opção inválida!" << TXT_BRANCO << endl;
    }
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

//  MAIN //
int main(){

    bool desligar = false; 
    int escolhaLogin;
    string nomeUser;

    Usuarios users[TAM_VETOR_USERS];
    int totalUsers = 0;

    system("clear");

    const string pastaAcordes = "acordes-violao";
    string arquivos[MAX_NOTAS];
    string nomes[MAX_NOTAS];

    while(desligar != true){
        cout << "\n   === BEM VINDO AO MELOMIX ===   " << endl;
        cout << "\n1 - Fazer login" << endl;
        cout << "2 - Criar conta" << endl;
        cout << "0 - Sair" << endl;
        cout << "Escolha: " << TXT_AMARELO;
        cin >> escolhaLogin;
        cout << "\n" << TXT_BRANCO;
        cin.ignore();

        switch (escolhaLogin){

        case 1:
            if(fazer_login(users, nomeUser)){
                limpar();

                bool voltar = false;

                while (voltar != true ){
                    int selecao;
                    cout << TXT_BRANCO "\n   === Bem vindo " << TXT_AMARELO << nomeUser << TXT_BRANCO << " ===   " << endl;
                    cout << "1 - Acordes de violão" << endl;
                    cout << "2 - Notas de piano" << endl;
                    cout << "3 - musicas : " << endl;
                    cout << "0 - Sair: " << TXT_AMARELO << endl;
                    cin >> selecao;
                    cout << "\n" << TXT_BRANCO;
                    cin.ignore();

                    escolha_melodia(voltar, selecao);
                  
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
