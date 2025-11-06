// BIBLIOTECAS //
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// GLOBAL //
#define TXT_VERMELHO "\033[31m"
#define TXT_BRANCO "\033[0m"
#define TXT_VERDE "\033[32m" 
#define TXT_AMARELO "\033[33m"

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


// CRUD //
int pegar_ultimoID(){
    ifstream arq("usuarios.txt");

    if(!arq.is_open()){
        return 0;
    }

    int ultimoID = 0;
    int idTemp;
    string nome, email, senha;

    while(arq >> idTemp){
        getline(arq, nome);
        getline(arq, email);
        getline(arq, senha);
        ultimoID = idTemp;
    }

    arq.close();
    return ultimoID;
}

bool email_ja_existe(string emailProcurado){
    ifstream arq("usuarios.txt");
    if(!arq.is_open()){
        return false;
    }

    int id;
    string nome, email, senha;

    while(arq >> id){
        getline(arq, nome);
        getline(arq, email);
        getline(arq, senha);

        if(email == emailProcurado){
            arq.close();
            return true;
        }
    }

    arq.close();
    return false;
}

void criar_conta(Usuarios users[], int &total){
    Usuarios usr;

    // gerar id automaticamente
    usr.id = pegar_ultimoID() + 1;

    cout << "\n   === BEM VINDO AO MELOMIX ===   " << endl;
    cout << "\nCrie sua conta" << endl;
    cout << "Nome: " << TXT_AMARELO;
    getline(cin, usr.nome);
    cout << TXT_BRANCO;
    cout << "Email: " << TXT_AMARELO;
    getline(cin, usr.email);
    cout << TXT_BRANCO;

    // valida se email já existe
    if(email_ja_existe(usr.email)){
        cout << "Este email ja esta cadastrado!" << endl;
        return;
    }

    cout << "Senha: " << TXT_AMARELO;
    getline(cin, usr.senha);
    cout << TXT_BRANCO;

    // salvar no vetor
    users[total] = usr;
    total++;

    // salvar no arquivo
    ARQ_ESCRITA.open("usuarios.txt", ios::app);
    ARQ_ESCRITA << usr.id << endl;
    ARQ_ESCRITA << usr.nome << endl;
    ARQ_ESCRITA << usr.email << endl;
    ARQ_ESCRITA << usr.senha << endl;
    ARQ_ESCRITA.close();

    cout << TXT_VERDE << "\nConta criada com sucesso!" << TXT_BRANCO << endl;
}

bool fazerLogin(Usuarios users[], int total){
    string email, senha;

    cout << "\n   === BEM VINDO AO MELOMIX ===   " << endl;
    cout << "\nFazendo login" << endl;
    cout << "Nome: " << TXT_AMARELO;
    getline(cin, email);
    cout << TXT_BRANCO;
    cout << "Email: " << TXT_AMARELO;
    getline(cin, senha);

    ARQ_LEITURA.open("usuarios.txt");

    int idFile;
    string nomeFile, emailFile, senhaFile;

    while(ARQ_LEITURA >> idFile){
        ARQ_LEITURA.ignore();
        getline(ARQ_LEITURA, nomeFile);
        getline(ARQ_LEITURA, emailFile);
        getline(ARQ_LEITURA, senhaFile);

        if(emailFile == email && senhaFile == senha){
            ARQ_LEITURA.close();
            cout << "Bem vindo " << nomeFile << " !!!" << endl;
            return true;
        }
    }

    ARQ_LEITURA.close();
    return false;
}

// FUNÇÃO MAIN //
int main(){

    bool desligar = true; // desligar programa
    int escolhaLogin;

    Usuarios users[TAM_VETOR_USERS];
    int totalUsers = 0;

    while(desligar == true){
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
            if(fazerLogin(users, totalUsers)){
                cout << TXT_VERDE << "\nLogin efetuado!" << TXT_BRANCO << endl;
            }else{
                cout << TXT_VERMELHO << "\nFalha no login!" << TXT_BRANCO << endl;
            }
            break;

        case 2:
            criar_conta(users, totalUsers);
            break;

        case 0:
            desligar = false;
            break;
        
        default:
            cout << "opção invalida!" << endl;
            break;
        }
    }

    return 0;
}
