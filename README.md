# Projeto C02 — MELOMIX

**Disciplina:** Algoritmos e Estrutura de Dados 1 (C02 — 2025)  
**Autores:** Cassiano Eller Vitoriano Fonseca, Marlon Robert Mota Rosa  
**Data:** 2025  

---

## Sumário

1. [Visão Geral](#1-visão-geral)  
2. [Informações do Projeto](#2-informações-do-projeto)  
3. [Integrantes e Funções](#3-integrantes-e-funções)  
4. [Resumo (Abstract)](#4-resumo-abstract)  
5. [Funcionalidades](#5-funcionalidades)  
6. [Estrutura do Projeto](#6-estrutura-do-projeto)  

---

## 1. Visão Geral

**MELOMIX** é um projeto desenvolvido para a matéria **C02 (Programação em C++) — 2025**.  
O aplicativo permite que o usuário, através do terminal, visualize e ouça notas musicais de instrumentos específicos, além de oferecer um sistema de **login** e **criação de contas** para acesso personalizado ao catálogo de partituras.

---

## 2. Informações do Projeto

- **Nome da aplicação:** MeloMix  
- **Tema:** Catálogo de partituras e notas musicais de instrumentos  
- **Linguagem:** C++  
- **Ambiente alvo:** Linux / macOS (indisponível para Windows)

---

## 3. Integrantes e Funções

| Integrante | Função |
|-------------|--------|
| **Cassiano Eller Vitoriano Fonseca** | Integração dos módulos, controle de execução e implementação do sistema de reprodução de som |
| **Marlon Robert Mota Rosa** | Programação da leitura dos arquivos de partituras e notas dos instrumentos, desenvolvimento do sistema de login e registro de usuários |

---

## 4. Resumo (Abstract)

O **MeloMix** é um aplicativo terminal feito em **C++** com o intuito de apresentar ao usuário notas musicais de diferentes instrumentos, permitindo que o som correspondente seja reproduzido.  
O programa possui autenticação simples com **login** e **criação de conta**, garantindo uma experiência personalizada para cada usuário.

---

## 5. Funcionalidades

- **Criação de conta:** cadastro de novos usuários com ID gerado automaticamente.  
- **Login:** autenticação de usuários com validação de e-mail e senha.  
- **Persistência de dados:** armazenamento local em arquivo texto (`usuarios.txt`).  
- **Interface colorida:** saída colorida no terminal com códigos ANSI.  
- **Limpeza automática de tela:** pausa e limpeza de tela após ações importantes.  
- **Reprodução de melodias:** execução de arquivos de som utilizando o comando `xdg-open` no Linux/macOS.

---

## 6. Estrutura do Projeto

```bash
├── projeto-C02/
├── main.cpp        # Código principal do programa (funções e menu)
├── usuarios.txt    # Arquivo de armazenamento de dados (gerado automaticamente)
├── melodias/       # Diretórios de melodias e partituras
│   ├── acordes-violao/
│   ├── notas-piano/
│   └── musica/
├── output/         # Diretório opcional para o executável
└── README.md       # Documentação do projeto