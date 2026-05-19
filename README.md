# 📚 Sistema de Gestão de Biblioteca (Alexandrinha)

Este repositório contém a base do nosso sistema de biblioteca desenvolvido em C para a disciplina de **Estrutura de Dados**.

O projeto está organizado de forma modular para facilitar:
- trabalho em equipe
- manutenção do código
- versionamento com Git/GitHub

---

# 🛠️ Configuração do Ambiente (WSL / Linux)

## 1. Instalar o WSL

Abra o **PowerShell como Administrador** e execute:

```bash
wsl --install
```

2. Instalar o GCC (Compilador)

No terminal Ubuntu/WSL:
```bash
sudo apt update
sudo apt install build-essential
```

3. Acessar os arquivos do Windows no WSL

Use:

```bash
cd /mnt/c/Users/SEU_USUARIO/pasta_do_projeto
```

🚀 Como Compilar e Rodar
Compilar:
```bash
gcc biblioteca.c funcoes.c -o biblioteca
```

Executar:
```bash
./biblioteca
```

📂 Estrutura do Projeto

## biblioteca.h

Contém:

- definição das structs
- nós das listas
- nós das árvores
- assinaturas das funções globais


## funcoes.c

Responsável por:
- lógica do sistema
- alocação dinâmica
- cadastro de livros
- validações
- manipulação de arquivos


## biblioteca.c

Arquivo principal do sistema.

Contém:
- função main
- menu interativo
- fluxo principal do programa
- integração entre módulos

| Parte   | Responsável | Funcionalidades                                    | Status          |
| ------- | ----------- | -------------------------------------------------- | --------------- |
| Parte 1 | Thiago      | Structs, Ponteiros, Alocação Dinâmica e Validações | 🟩 Concluída     |
| Parte 2 | Davi        | Listas Encadeadas, Catálogo e Ordenação            | ⬜ Pendente      |
| Parte 3 | Gabriel     | Filas e Pilhas                                     | ⬜ Pendente      |
| Parte 4 | Henrique    | Árvores Binárias e Grafos                          | ⬜ Pendente      |
| Parte 5 | Leonardo    | Arquivos `.bin` e Complexidade                     | 🟩 Concluída     |

# 👥 Divisão de Tarefas

## Thiago
- Modelagem das structs
- Gerenciamento de ponteiros
- Validação de entradas
- Proteção contra erros do usuário

---

## Davi
- Lista encadeada do catálogo
- Ordenação por título
- Ordenação por ID

---

## Gabriel
- Fila de espera de livros
- Histórico usando pilha

---

## Henrique
- Árvores Binárias de Busca (ABB)
- Grafos para livros relacionados

---

## Leonardo
- Persistência em arquivos binários
- Documentação da complexidade assintótica

# 🚨 Regras do Grupo

## 📢 Comunicação

Sempre avisar no grupo quando:

- terminar uma função
- alterar arquivos importantes
- realizar `push`

---

## 🧹 Organização

- manter a identação do código
- comentar funções mais complexas
- manter nomes padronizados
- evitar código duplicado

---

## ⚠️ Controle do Cabeçalho

Não alterar o arquivo `biblioteca.h` sem avisar o grupo.

Mudanças no cabeçalho podem afetar o funcionamento do projeto inteiro.

---

## 🔄 Atualização

Ao finalizar sua parte:

- atualizar o `README.md`
- atualizar o status da tabela
- informar o grupo sobre as alterações realizadas

---

# 🎯 Objetivo Geral

Demonstrar a aplicação prática dos principais conceitos de:

- Estruturas de Dados
- Alocação Dinâmica
- Manipulação de Arquivos
- Organização Modular
- Complexidade de Algoritmos

através de um sistema real de gerenciamento de biblioteca desenvolvido em C.
