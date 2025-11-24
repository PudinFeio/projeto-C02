// BIBLIOTECAS //
#include <iostream> // cout, cin, endl — manipulação de entrada e saída de dados via streams
#include <iomanip>  // setw — manipulação de layout/tabulação de saída
#include <string>   // string — manipulação de strings dinâmicas
#include <fstream>  // ifstream/ofstream — leitura e escrita de arquivos
#include <unistd.h> // sleep() — pausa a execução por n segundos
#include <cstdlib>  // system() — executa comandos do shell, exit() — encerra o programa
#include <dirent.h> // DIR, struct dirent, opendir/readdir/closedir — manipulação de diretórios POSIX
#include <cstring>  // strcpy, strcmp, memset — manipulação de C-strings
#include <sys/types.h> // typedefs de tipos do sistema usados por dirent.h

using namespace std;

// CORES TERMINAL
#define TXT_VERMELHO "\033[31m"
#define TXT_BRANCO   "\033[0m"
#define TXT_VERDE    "\033[32m"
#define TXT_AMARELO  "\033[33m"
#define TXT_AZUL     "\033[34m"

// VARIÁVEIS GLOBAIS
ofstream ARQ_ESCRITA;
ifstream ARQ_LEITURA;
const int TAM_VETOR_USERS = 100;
const int MAX_NOTAS = 26;
const string USERS_DB  = "usuarios.txt";
string PATH;

// ESTRUTURAS
struct Usuarios {
    int id;
    string nome;
    string email;
    string senha;
};

struct Melodias {
    string caminho;
    char arquivos[100][256];
    int quantidade;
};

// FUNÇÕES UTILITÁRIAS
void limpar(int a) {
    sleep(a);
    system("clear");
}

// TOCAR MÚSICA
void tocar_melodia(Melodias melo) {
    int escolha;
    bool voltar = false;
    const int LINHAS = 8;

    while (!voltar) {
        limpar(1);

        if (melo.quantidade == 0) {
            cout << "Nenhum arquivo encontrado!" << endl;
            return;
        }

        cout << "\n   === Digite um dos números para reproduzir a melodia ===   \n\n";

        int total = melo.quantidade;
        int COLUNAS = (total + LINHAS - 1) / LINHAS;

        string matriz[LINHAS * COLUNAS];

        int index = 0;
        for (int c = 0; c < COLUNAS; c++) { // adicioando musicas no array
            for (int l = 0; l < LINHAS; l++) {
                int pos = l * COLUNAS + c;
                if (index < total) {
                    matriz[pos] = to_string(index + 1) + " - " + melo.arquivos[index];
                    index++;
                } else {
                    matriz[pos] = "";
                }
            }
        }

        int largura[COLUNAS];
        memset(largura, 0, sizeof(largura)); //zera todos os bytes do array

        for (int c = 0; c < COLUNAS; c++) { // ajusta a exibição de acordo com a maior string
            int maior = 0;
            for (int l = 0; l < LINHAS; l++) {
                int pos = l * COLUNAS + c;
                int sz = matriz[pos].size(); 
                if (sz > maior) maior = sz;
            }
            largura[c] = maior + 4;
        }
           
        for (int l = 0; l < LINHAS; l++) { // largura de campo; left/right alinham à esquerda/direita
            for (int c = 0; c < COLUNAS; c++) {
                int pos = l * COLUNAS + c;
                if (!matriz[pos].empty()) {
                    cout << left << setw(largura[c]) << matriz[pos] << right; 
                }
            }
            cout << endl;
        }

        cout << "\n0 - Voltar" << endl;
        cout << "Escolha: " << TXT_AMARELO;
        cin >> escolha;
        cout << TXT_BRANCO;

        if (escolha < 0 || escolha > melo.quantidade) {
            cout << TXT_VERMELHO << "\nOpção inválida!" << TXT_BRANCO << endl;
            limpar(2);
            return;
        }

        if (escolha == 0) {
            voltar = true;
            limpar(1);
            return;
        }

        string caminhoCompleto = melo.caminho + melo.arquivos[escolha - 1];
        string comando = "xdg-open \"" + caminhoCompleto + "\"";
        system(comando.c_str());
    }
}

// ABRIR DIRETÓRIO
void abrir_diretorio(Melodias &dirInfo, const string &path) {
    DIR *dir;
    struct dirent *entrada;

    dirInfo.caminho = path;
    dirInfo.quantidade = 0;

    dir = opendir(path.c_str());
    if (!dir) {
        cout << "Erro ao abrir o diretorio: " << path << endl;
        return;
    }

    while ((entrada = readdir(dir)) != NULL) { //retorna cada item do diretório
        const char *nome = entrada->d_name; // pega o nome do arquivo
        if (strcmp(nome, ".") == 0 || strcmp(nome, "..") == 0)
            continue; 

        if (dirInfo.quantidade < 100) {
            strcpy(dirInfo.arquivos[dirInfo.quantidade], nome);
            dirInfo.quantidade++;
        } else {
            cout << "Limite de arquivos atingido!" << endl;
            break;
        }
    }

    closedir(dir);
}

// ESCOLHA DE MELODIA
void escolha_melodia(bool &voltar, int selecao) {
    Melodias toques;

    switch (selecao){
        case 1:
            PATH = "melodias/acordes-violao/";
            abrir_diretorio(toques, PATH);
            tocar_melodia(toques);
            break;
        case 2:
            PATH = "melodias/notas-piano/";
            abrir_diretorio(toques, PATH);
            tocar_melodia(toques);
            break;
        case 0:
            voltar = true;
            break;
        default:
            cout << TXT_VERMELHO << "Opção inválida!" << TXT_BRANCO << endl;
            limpar(2);
    }
}

// FUNÇÕES CRUD DE USUÁRIOS
int pegar_ultimoID(){
    ARQ_LEITURA.open(USERS_DB, ofstream::in); // open() do fstream abre arquivo para leitura

    int ultimoID = 0;
    int idTemp;
    string nome, email, senha;

    while(ARQ_LEITURA >> idTemp){ // >> lê valor do arquivo para idTemp
        ARQ_LEITURA.ignore();     // ignore() descarta o '\n' após leitura do int
        getline(ARQ_LEITURA, nome);  // getline() do iostream lê linha inteira
        getline(ARQ_LEITURA, email);
        getline(ARQ_LEITURA, senha);
        ultimoID = idTemp;
    }
    ARQ_LEITURA.close(); // fecha arquivo
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

    system("clear"); // limpa terminal

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

    ARQ_ESCRITA.open(USERS_DB, ofstream::out | ofstream::app); // abre arquivo em append
    ARQ_ESCRITA << usr.id << endl;    // << do fstream escreve dados no arquivo
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

    ARQ_LEITURA.open(USERS_DB);

    int idFile;
    string emailFile, senhaFile;

    while(ARQ_LEITURA >> idFile){
        ARQ_LEITURA.ignore();
        getline(ARQ_LEITURA, nomeFile);
        getline(ARQ_LEITURA, emailFile);
        getline(ARQ_LEITURA, senhaFile);

        if(emailFile == email && senhaFile == senha){
            ARQ_LEITURA.close();
            cout << TXT_VERDE << "\nLogin efetuado com sucesso!" << TXT_BRANCO << endl;
            return true;
        }
    }

    ARQ_LEITURA.close();
    return false;
}

// MAIN
int main(){
    bool desligar = false; 
    int escolhaLogin;
    string nomeUser;
    Usuarios users[TAM_VETOR_USERS];
    int totalUsers = 0;

    system("clear"); // limpa terminal

    while(!desligar){
        cout << "\n   === BEM VINDO AO MELOMIX ===   " << endl;
        cout << "\n1 - Fazer login" << endl;
        cout << "2 - Criar conta" << endl;
        cout << "0 - Sair" << endl;
        cout << "Escolha: " << TXT_AMARELO;
        cin >> escolhaLogin;
        cout << "\n" << TXT_BRANCO;
        cin.ignore(); // descarta '\n' do buffer de entrada

        switch (escolhaLogin){
            case 1:
                if(fazer_login(users, nomeUser)){
                    limpar(1);
                    bool voltar = false;
                    while (!voltar ){
                        int selecao;
                        cout << TXT_BRANCO "\n   === Bem vindo ao MeloMix " << TXT_AMARELO << nomeUser << TXT_BRANCO << " ===   \n" << endl;
                        cout << "1 - Acordes de violão" << endl;
                        cout << "2 - Notas de piano" << endl;
                        cout << "0 - Voltar " << TXT_AMARELO << endl;
                        cout << TXT_BRANCO << "Escolha: " << TXT_AMARELO;
                        cin >> selecao;
                        cout << "\n" << TXT_BRANCO;
                        cin.ignore();

                        if(selecao < 1){
                            limpar(1);
                            break;
                        }
                        escolha_melodia(voltar, selecao);
                    }
                } else {
                    cout << TXT_VERMELHO << "\nFalha no login!" << TXT_BRANCO << endl;
                    limpar(2);
                }
                break;
            case 2:
                if(criar_conta(users, totalUsers)){
                    cout << TXT_VERDE << "\nConta criada com sucesso!" << TXT_BRANCO << endl;
                    limpar(2);
                } else {
                    cout << TXT_VERMELHO << "\nErro ao criar conta!" << TXT_BRANCO << endl;
                    limpar(2);
                }
                break;
            case 0:
                cout << TXT_AMARELO <<" Saindo..." << TXT_BRANCO << endl;
                desligar = true;
                limpar(1);
                break;
            default:
                cout << TXT_VERMELHO <<"Opção inválida!" << TXT_BRANCO << endl;
                limpar(2);
                break;
        }
    }

    return 0;
}
