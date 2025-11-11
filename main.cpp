// HEADER //
#include "main.h"

// GLOBAIS //
ofstream ARQ_ESCRITA;
ifstream ARQ_LEITURA;

// TOCAR NOTAS //

// CRUD //
int pegar_ultimoID(){
    ifstream arq(NOME_ARQUIVO);

    if(!arq.is_open()){
        return 0;
    }

    int ultimoID = 0;
    int idTemp;
    string nome, email, senha;

    while(arq >> idTemp){   // Pega os dados do usuário e armazeno o id;
        getline(arq, nome);
        getline(arq, email);
        getline(arq, senha);
        ultimoID = idTemp;
    }

    arq.close();
    return ultimoID + 1;
}

bool email_ja_existe(string emailProcurado){
    ifstream arq(NOME_ARQUIVO);

    if(!arq.is_open()){
        return false;
    }

    int id;
    string nome, email, senha;

    while(arq >> id){   // Pega todos os usuários
        getline(arq, nome);
        getline(arq, email);
        getline(arq, senha);

        if(email == emailProcurado){    // Verifica se o email existe
            arq.close();
            return true;
        }
    }

    arq.close();
    return false;
}

bool criar_conta(Usuarios users[], int &total){
    Usuarios usr;

    usr.id = pegar_ultimoID();  //Gera id automaticamente

    system("clear");

    cout << "\n   === BEM VINDO AO MELOMIX ===   " << endl;
    cout << "\nCrie sua conta" << endl;
    cout << "Nome: " << TXT_AMARELO;
    getline(cin, usr.nome);
    cout << TXT_BRANCO;
    cout << "Email: " << TXT_AMARELO;
    getline(cin, usr.email);
    cout << TXT_BRANCO;

    if(email_ja_existe(usr.email)){     // Valida se email já existe
        cout << "Este email ja esta cadastrado!" << endl;
        return false;
    }

    cout << "Senha: " << TXT_AMARELO;
    getline(cin, usr.senha);
    cout << TXT_BRANCO;

    users[total] = usr; // salvar o user no vetor na posição total;
    total++;

    // salvar no arquivo
    ARQ_ESCRITA.open("usuarios.txt", ios::app);
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

    while(ARQ_LEITURA >> idFile){   // Pega todos os usuários
        ARQ_LEITURA.ignore();
        getline(ARQ_LEITURA, nomeFile);
        getline(ARQ_LEITURA, emailFile);
        getline(ARQ_LEITURA, senhaFile);

        if(emailFile == email && senhaFile == senha){   // Verifica se o email e senha batem
            ARQ_LEITURA.close();
            cout << TXT_VERDE << "\nLogin efetuado com " << TXT_AZUL << "sucesso!" << TXT_BRANCO << endl;
            limpar();
            return true;
        }
    }

    ARQ_LEITURA.close();
    return false;
}

// FUNÇÃO MAIN //
int main(){

    bool desligar = true; // Desligar programa
    int escolhaLogin;
    string nomeUser;

    Usuarios users[TAM_VETOR_USERS];
    int totalUsers = 0;

    system("clear");

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
            if(fazer_login(users, nomeUser)){
                cout << TXT_BRANCO "\nBem vindo " << TXT_AMARELO << nomeUser << TXT_BRANCO << " !!!" << endl;
                limpar();
            }else{
                cout << TXT_VERMELHO << "\nFalha no login!" << TXT_BRANCO << endl;
                limpar();
            }

            break;

        case 2:
            if(criar_conta(users, totalUsers)){
                cout << TXT_VERDE << "\nConta criada com sucesso!" << TXT_BRANCO << endl;
                limpar();
            }
            else{
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
