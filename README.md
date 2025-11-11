# Projeto C02 — MELOMIX

**Disciplina:** Programação em C++ (C02 — 2025)  
**Autores:** Bruna Pereira de Oliveira, Cassiano Eller Vitoriano Fonseca, Marlon Robert Mota Rosa  
**Data:** 2025  

---

## Sumário

1. [Visão Geral](#1-visão-geral)  
2. [Informações do Projeto](#2-informações-do-projeto)  
3. [Integrantes e Funções](#3-integrantes-e-funções)  
4. [Resumo (Abstract)](#4-resumo-abstract)  
5. [Funcionalidades](#5-funcionalidades)  
6. [Estrutura do Projeto](#6-estrutura-do-projeto)  
7. [Compilação Linux ou Mac](#7-compilação-linux-ou-mac-indisponível-para-windows)  
8. [Requisitos Mínimos](#8-requisitos-mínimos)  
9. [Licença](#9-licença)  

---

## 1. Visão Geral

**MELOMIX** é um projeto desenvolvido para a matéria **C02 (Programação em C++) — 2025**.  
O aplicativo tem como objetivo permitir que o usuário, por meio do terminal, visualize e ouça notas musicais de instrumentos específicos, além de oferecer um sistema de **login** e **criação de contas** para acesso ao catálogo de partituras.

---

## 2. Informações do Projeto

- **Nome da aplicação:** MeloMix  
- **Tema:** Catálogo de partituras e notas musicais de instrumentos  
- **Linguagem:** C++  
- **Ambiente alvo:** Linux / macOS (compatível com ajustes para Windows)

---

## 3. Integrantes e Funções

| Integrante | Função |
|-------------|--------|
| **Bruna Pereira de Oliveira** | Desenvolvimento do sistema de login e registro de usuários |
| **Cassiano Eller Vitoriano Fonseca** | Integração dos módulos, controle de execução e implementação do sistema de saída de som |
| **Marlon Robert Mota Rosa** | Programação da leitura dos arquivos de partituras e notas dos instrumentos |

---

## 4. Resumo (Abstract)

O **MeloMix** é um aplicativo terminal feito em **C++** com o intuito de apresentar ao usuário notas musicais de diferentes instrumentos, permitindo que o som correspondente seja reproduzido.  
O programa também possui um sistema de autenticação simples com **login** e **criação de conta**, garantindo uma experiência personalizada para cada usuário.  

---

## 5. Funcionalidades

- **Criação de conta:** cadastro de novos usuários com ID gerado automaticamente.  
- **Login:** autenticação de usuários com validação de e-mail e senha.  
- **Persistência de dados:** armazenamento local em arquivo texto (`usuarios.txt`).  
- **Interface colorida:** saída colorida no terminal com códigos ANSI.  
- **Limpeza automática de tela:** pausa e limpeza de tela após ações importantes.  
- **Módulo de som (em desenvolvimento):** reprodução de notas musicais a partir de arquivos de partitura.

---

## 6. Estrutura do Projeto

```bash
├── projeto-C02/
├── main.cpp        # Código principal do programa (funções e menu)
├── main.h          # Cabeçalho com bibliotecas, definições e structs
├── usuarios.txt    # Arquivo de armazenamento de dados (gerado automaticamente)
├── output/         # Diretório opcional para o executável
└── README.md       # Documentação do projeto
```
---

## Compilação Linux ou Mac (indisponível para Windows)

- **g++ main.cpp -o MeloMix**
- **./MeloMix**
