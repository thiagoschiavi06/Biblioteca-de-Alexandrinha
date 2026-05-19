#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

typedef struct {
    int id;
    char titulo[100];
    char autor[100];
    char genero[50];
    int ano;
    int disponivel;
} Livro;

typedef struct {
    int id;
    char nome[100];
} Usuario;

typedef struct {
    int idLivro;
    int idUsuario;
    char dataR[20]; // data retirada
    char dataD[20]; // data devolução
} Emprestimo;

// Estruturas de nó (catálogo, histórico, fila, pilha)
typedef struct NoLista {
    Livro livro; 
    struct NoLista *prox;
} NoLista;

// Nó para busca rápida (árvore binária)
typedef struct NoArvore {
    Livro livro;
    struct NoArvore *esq;
    struct NoArvore *dir;
} NoArvore;

void limparBuffer();
int ehApenasNumero(const char *str);
int pedirIdValidado(const char *mensagem);

int verificarIdExiste(int id, const char *nomeArquivo);
Livro* criarLivro(int id);
void salvarLivro(Livro *livro, const char *nomeArquivo);
void carregarLivros(const char *nomeArquivo);

int buscarLivroPorId(int id, const char *nomeArquivo);
void editarLivro(int id, const char *nomeArquivo);
void excluirLivro(int id, const char *nomeArquivo);
void paraMinusculo(char *str);
int buscarLivroPorTermo(const char *termo, int categoria, const char *nomeArquivo);

#endif