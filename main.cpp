// BIBLIOTECAS //
#include <iostream> // Entrada e saida de dados
#include <iomanip> // Manipulador de entrada e saída de dados
#include <string>   // Tipo string
#include <fstream> // Leitura e escrita de arquivos
#include <unistd.h> // Fornece o sleep() e outras funções para interação com o terminal
#include <cstdlib> // Permite enviar comandos para o terminal através do system()
#include <dirent.h> // Interação com diretórios
#include <cstring> // Manipulador de Strings
#include <sys/types.h> // Biblioteca C que define tipos de dados usados pelo sistema operacional Linux/mac

using namespace std;

// CORES UNIX //
#define TXT_VERMELHO "\033[31m"
#define TXT_BRANCO "\033[0m"
#define TXT_VERDE "\033[32m"
#define TXT_AMARELO "\033[33m"
#define TXT_AZUL "\033[34m"

// GLOBAIS //
ofstream ARQ_ESCRITA;
ifstream ARQ_LEITURA;

const int TAM_VETOR_USERS = 100;
const int MAX_NOTAS = 26;
const string USERS_DB  = "usuarios.txt";
string PATH;

// STRUCTS //
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

// FUNÇÕES EXISTENTES //
void limpar(int a) {
    sleep(a);
    system("clear");
}

// TOCAR MÚSICA //
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

        int total = melo.quantidade; // Armazena o total de arquivos encontrados no diretório
        int COLUNAS = (total + LINHAS - 1) / LINHAS; // calcula quantas colunas serão necessárias para distribuir os arquivos igualmente

        string *matriz = new string[LINHAS * COLUNAS]; // Cria dinamicamente uma matriz unidimensional que representará a grade de arquivos exibidos

        int index = 0;

        for (int c = 0; c < COLUNAS; c++) { // Percorre cada coluna para preencher a matriz visual com os nomes dos arquivos
            for (int l = 0; l < LINHAS; l++) {
                int pos = l * COLUNAS + c;

                if (index < total) { // Verifica se ainda há arquivos para serem listados
                    matriz[pos] = to_string(index + 1) + " - " + melo.arquivos[index];
                    index++;
                } else {
                    matriz[pos] = ""; // Insere espaço vazio caso não haja mais arquivos disponíveis para preencher a grade
                }
            }
        }

        int *largura = new int[COLUNAS]; // Vetor que armazenará a largura máxima de cada coluna para alinhar a exibição
        memset(largura, 0, sizeof(int) * COLUNAS); // inicializa o vetor de larguras com zeros

        for (int c = 0; c < COLUNAS; c++) { // Calcula a maior largura de texto em cada coluna
            int maior = 0;
            for (int l = 0; l < LINHAS; l++) { // Percorre todas as linhas da coluna atual
                int pos = l * COLUNAS + c;
                int sz = matriz[pos].size();
                if (sz > maior) maior = sz;
            }
            largura[c] = maior + 4; // adiciona espaçamento extra para manter boa separação visual
        }

        for (int l = 0; l < LINHAS; l++) { // imprime linha por linha da matriz de arquivos
            for (int c = 0; c < COLUNAS; c++) {
                int pos = l * COLUNAS + c;
                if (!matriz[pos].empty()) { // imprime apenas células com conteúdo
                    cout << left << setw(largura[c]) << matriz[pos] << right;
                }
            }
            cout << endl;
        }

        delete[] matriz; // libera memória alocada para a matriz de exibição
        delete[] largura; // libera memória alocada para o vetor de larguras

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

        string caminhoCompleto = melo.caminho + melo.arquivos[escolha - 1]; // monta o caminho completo do arquivo selecionado

        string comando = "xdg-open \"" + caminhoCompleto + "\""; // monta o comando para abrir o arquivo com o programa padrão do sistema
        system(comando.c_str()); // executa o comando que abre a melodia selecionada
    }
}

void abrir_diretorio(Melodias &dirInfo, const string &path) { // função que carrega arquivos de um diretório para a struct Melodias
    DIR *dir; // ponteiro para o diretório que será aberto
    struct dirent *entrada; // estrutura que representa cada item encontrado dentro do diretório

    dirInfo.caminho = path;
    dirInfo.quantidade = 0;

    dir = opendir(path.c_str()); // tenta abrir o diretório especificado
    if (!dir) {
        cout << "Erro ao abrir o diretorio: " << path << endl;
        return;
    }

    while ((entrada = readdir(dir)) != NULL) { // lê cada item encontrado no diretório
        const char *nome = entrada->d_name;

        if (strcmp(nome, ".") == 0 || strcmp(nome, "..") == 0)  // Ignora "." e ".."
            continue;

        if (dirInfo.quantidade < 100) { // adiciona o nome do arquivo ao vetor caso ainda haja espaço disponível
            strcpy(dirInfo.arquivos[dirInfo.quantidade], nome);
            dirInfo.quantidade++;
        } else {
            cout << "Limite de arquivos atingido!" << endl;
            break;
        }
    }

    closedir(dir); // fecha o diretório após a leitura
}

void escolha_melodia(bool &voltar, int selecao){ // gerencia a escolha de qual categoria de melodias será acessada
    Melodias toques;

    switch (selecao){

        case 1: {
            PATH = "melodias/acordes-violao/";
            abrir_diretorio(toques, PATH);
            tocar_melodia(toques);
            break;
        }

        case 2:
            PATH = "melodias/notas-piano/";
            abrir_diretorio(toques, PATH);
            tocar_melodia(toques);
            break;

        case 3:
            PATH = "melodias/musica/";
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

// CRUD //
int pegar_ultimoID(){
    ARQ_LEITURA.open(USERS_DB, ofstream::in);

    int ultimoID = 0;
    int idTemp;
    string nome, email, senha;

    while(ARQ_LEITURA >> idTemp){ // lê o ID registrado no arquivo
        ARQ_LEITURA.ignore(); // limpa o buffer para leitura de strings completas
        getline(ARQ_LEITURA, nome);
        getline(ARQ_LEITURA, email);
        getline(ARQ_LEITURA, senha);
        ultimoID = idTemp;
    }
    ARQ_LEITURA.close();
    return ultimoID + 1;
}

bool email_ja_existe(string emailProcurado){ // verifica se o email já está cadastrado no banco de usuários
    ARQ_LEITURA.open(USERS_DB, ofstream::in);

    int id;
    string nome, email, senha;

    while(ARQ_LEITURA >> id){ // lê o ID de cada usuário
        ARQ_LEITURA.ignore(); // limpa o buffer para leitura de strings completas
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

bool criar_conta(Usuarios users[], int &total){ // registra um novo usuário no sistema
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

bool fazer_login(Usuarios users[], string &nomeFile){ // valida login do usuário verificando email e senha
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

        if(emailFile == email && senhaFile == senha){ // Verifica se Email e Senha batem
            ARQ_LEITURA.close();
            cout << TXT_VERDE << "\nLogin efetuado com sucesso!" << TXT_BRANCO << endl;

            return true;
        }
    }

    ARQ_LEITURA.close();

    return false;
}

// MAIN //
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

    while(!desligar){
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
                limpar(1);
                bool voltar = false;

                while (!voltar ){
                    int selecao;
                    cout << TXT_BRANCO "\n   === Bem vindo ao MeloMix " << TXT_AMARELO << nomeUser << TXT_BRANCO << " ===   \n" << endl;
                    cout << "1 - Acordes de violão" << endl;
                    cout << "2 - Notas de piano" << endl;
                    cout << "3 - musicas" << endl;
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
                break;
            }

            break;

        case 2:
            if(criar_conta(users, totalUsers)){
                cout << TXT_VERDE << "\nConta criada com sucesso!" << TXT_BRANCO << endl;
                limpar(2);
            } else {
                cout << TXT_VERMELHO << "\nErro ao criar conta!" << TXT_BRANCO << endl;
                limpar(2);
                break;
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
