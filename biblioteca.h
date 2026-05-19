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

// estruturas de nó
// catálogo, histórico, fila, pilha)
typedef struct NoLista {
    Livro livro; 
    struct NoLista *prox;
} NoLista;

// nó pra busca rapida (arvore binaria)
typedef struct NoArvore {
    Livro livro;
    struct NoArvore *esq;
    struct NoArvore *dir;
} NoArvore;

// Assinatura da função
Livro* criarLivro();
void salvarLivro(Livro *livro, const char *nomeArquivo);
void carregarLivros(const char *nomeArquivo);
int verificarId(int id, const char *nomeArquivo);
int idInt(const char *str);
void limparBuffer();
void excluirLivro(int id, const char *nomeArquivo);

#endif